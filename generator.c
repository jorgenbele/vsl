#include "generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>


#include "instr.h"
#include "ir.h"
#include "utils.h"

#include "node_src.h"


static const char *param_regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"
};

static const char *regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9", "%rax", "%rsp", "%rbp"
};

enum {
   REG_RDI = 0,
   REG_RSI = 1,
   REG_RDX = 2,
   REG_RCX = 3,
   REG_R8  = 4,
   REG_R9  = 5,
   REG_RAX = 6,
   REG_RSP = 7,
   REG_RBP = 8,
};

#define REG(n) regs[(i)]

/* Local variable offset. */
#define VAR_INDEX_OFFSET(saved, index) (-((saved)*sizeof(int_type)) + (index)*sizeof(int_type))

/* inline_src: Generate comments of source code in the
 *             output assembly code. */
static void inline_src(node_t *node)
{
    src_always_newline = 1;

    printf("\n\t# ");
    if (node->type == EXPRESSION) node_print_expression(node);
    else node_print_statement(node);
}

static void gen_strtable(ir_ctx_t *ctx)
{
    puts(".section .rodata");
    /* Printf format specifiers. */
    puts("\tintout: .string \"%ld \"");
    puts("\tstrout: .string \"%s \"");
    puts("\terrout: .string \"Wrong number of arguments\"");

    /* TODO: Strings. */
    for (uint64_t i = 0; i < VEC_LEN(&ctx->strings); i++)
        printf("\tglobal_string_%" PRId64 ": .string %s\n", i, VEC_GET(&ctx->strings, ir_str, i));
        //printf("\tglobal_string_%d: .string \"%s\"\n", i, VEC_GET(&ctx->strings, ir_str, i));
    assert(!VEC_ERROR(&ctx->strings));
}

static void gen_main(symbol_t *main_func)
{
    puts(".globl main");
    puts("main:");

    puts("\tpushq %rbp");
    puts("\tmovq %rsp, %rbp");

    puts("\tsubq $1, %rdi");
    printf("\tcmpq $%zu,%%rdi\n", main_func->nparms);
    puts("\tjne ABORT");
    puts("\tcmpq $0, %rdi");
    puts("\tjz SKIP_ARGS");

    puts("\tmovq %rdi, %rcx");
    printf("\taddq $%zu, %%rsi\n", sizeof(int_type)*main_func->nparms);
    puts("PARSE_ARGV:");
    puts("\tpushq %rcx");
    puts("\tpushq %rsi");

    puts("\tmovq (%rsi), %rdi");
    puts("\tmovq $0, %rsi");
    puts("\tmovq $10, %rdx");
    puts("\tcall strtol");

    /*  Now a new argument is an integer in rax */
    puts("\tpopq %rsi");
    puts("\tpopq %rcx");
    puts("\tpushq %rax");
    puts("\tsubq $8, %rsi");
    puts("\tloop PARSE_ARGV");

    /* Now the arguments are in order on stack */
    for (uint64_t arg = 0; arg < MIN(6, main_func->nparms); arg++)
        printf("\tpopq\t%s\n", param_regs[arg]);

    puts("SKIP_ARGS:");
    printf("\tcall\t_%s\n", main_func->name);

    puts("\tjmp END");
    puts("ABORT:");
    puts("\tlea errout(%rip), %rdi"); // NOTE: MODIFIED!
    puts("\tcall puts");

    puts("END:");
    puts("\tmovq %rax, %rdi");
    puts("\tcall exit");
    putchar('\n');
}

#define IS_CONST_TYPE(node_type) ((node_type) == NUMBER_DATA)

#define EMIT_LOCAL_LOCAL_INSTR(name, src_offset, dest_offset) \
    printf("%s -%" PRId64 "(%s)" ", -%" PRId64 "(%s)", (name), (src_offset), "%rbp", (dest_offset), "%rbp")

#define EMIT_NUMBER_LOCAL_INSTR(name, src_num, dest_offset) \
    printf("%s $%" PRId64 ", -%" PRId64 "(%s)", (name), (src_num), (dest_offset), "%rbp")

#define EMIT_LOCAL_REG_INSTR(name, src_offset, dest_reg) \
    printf("%s -%" PRId64 "(%s)" ", %s", (name), (src_offset), "%rbp", (dest_reg))


enum {
   T_STACK=0x0,
   T_REG=0x1,
   T_LOCAL=0x2,
   T_GLOBAL=0x4,
   T_CONST=0x8,
   T_PARAM=0x10,
};

static void expr_instr_type_s(node_t *n, uint16_t *out)
{
    if (n->type == IDENTIFIER_DATA) {
        if (n->entry->type == SYM_GLOBAL_VAR)     *out |= T_GLOBAL;
        else if (n->entry->type == SYM_LOCAL_VAR) *out |= T_LOCAL;
        else if (n->entry->type == SYM_PARAMETER) *out |= T_PARAM;
    } else if (n->type == NUMBER_DATA)            *out |= T_CONST;
}

/* expr_instr_type: Create a representation of the instruction operand types. */
static void expr_instr_type(node_t *left, uint16_t *tl, node_t *right, uint16_t *tr) {
    expr_instr_type_s(left, tl);
    expr_instr_type_s(right, tr);
}

static void emit_instr0_reg(ir_ctx_t *ctx, symbol_t *func, const char *instr, uint8_t reg)
{
    (void) ctx; (void) func;
    printf("\t%s %s\n", instr, regs[reg]);
}

static void emit_instr_reg_reg(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               uint8_t reg_left, uint8_t reg_right) {
    (void) ctx; (void) func;
    printf("\t%s %s, %s\n", instr, regs[reg_left], regs[reg_right]);
}

static void emit_instr_param(ir_ctx_t *ctx, symbol_t *func, node_t *n, uint8_t t_n, size_t *stack_top, size_t stack_offset)
{
    switch (t_n) {
        //case T_STACK:  printf("%" PRId64 "(%%rsp)", (*stack_top - stack_offset)*sizeof(int_type)); break;
        case T_STACK:  printf("%" PRId64 "(%%rsp)", (stack_offset)*sizeof(int_type)); break;
        case T_REG:    debug("Not supported!"); exit(1); break;
        case T_PARAM:  printf("%" PRId64 "(%%rbp)", VAR_INDEX_OFFSET(VEC_LEN(func->locals), n->entry->seq)); break;
        case T_LOCAL:  printf("%" PRId64 "(%%rbp)", VAR_INDEX_OFFSET(VEC_LEN(func->locals), n->entry->seq + func->nparms)); break;
        case T_GLOBAL: printf("_%s(%%rip)", n->entry->name); break;

        case T_CONST:  printf("$%" PRIdit, n->data_integer); break;
    }
}

static void emit_instr_mem_reg(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, uint8_t t_left, uint8_t reg, size_t *stack_top, size_t stack_offset)
{
    printf("\t%s ", instr);
    emit_instr_param(ctx, func, left, t_left, stack_top, stack_offset);
    printf(", %s\n", regs[reg]);
}

static void emit_instr_reg_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, uint8_t reg,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("%s, ", regs[reg]);
    emit_instr_param(ctx, func, right, t_right, stack_top, stack_offset);
    putchar('\n');
}

static void emit_instr_imm_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, int_type imm,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("$%" PRIdit", ", imm);
    emit_instr_param(ctx, func, right, t_right, stack_top, stack_offset);
    putchar('\n');
}

static void emit_instr_imm_reg(const char *instr, int_type imm, uint8_t reg) { printf("\t%s $%" PRIdit ", %s\n", instr, imm, regs[reg]); }

/* expression:
 *  Creates the assembly representing an expression.
 *  Saves the result rax and uses the registers specified
 *  by indexes in 'regs' as temporary registers. */
static void expression(ir_ctx_t *ctx, symbol_t *func, node_t *expr, size_t *stack_top)
{
    //inline_src(expr);

    if (!strcmp(expr->data_char_ptr, "func_call")) {
        assert(expr->n_children == 2);
        node_t *func_ident = expr->children[0];
        node_t *arglist = expr->children[1];
        for (size_t i = 0; i < arglist->n_children; i++) {
            uint16_t type = 0;
            expr_instr_type_s(arglist->children[i], &type);
            emit_instr_mem_reg(ctx, func, "movq", arglist->children[i], type, i, stack_top, 0);
        }
        printf("\tcall _%s\n", func_ident->data_char_ptr);
        return;
    }

    if (expr->n_children == 1) {
        node_t *left = expr->children[0];

        uint16_t t_left = 0;
        expr_instr_type_s(left, &t_left);

        /* Evaluate the expression. Results will be stored on the stack. */
        if (left->type == EXPRESSION) expression(ctx, func, left, stack_top);
        else emit_instr_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, 0);

        /* Has to be an identifier since '- <number>' const expressions
         * evaluate to the -<number>. */
        switch (*expr->data_char_ptr) {
            case '-':
                //emit_instr_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, 0);
                emit_instr0_reg(ctx, func, "negq", REG_RAX);
                break;

            case '~':
                //emit_instr_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, 0);
                emit_instr0_reg(ctx, func, "notq", REG_RAX);
                break;

            default:
                debug("EXPRESSION NOT IMPLEMENTED: [%d:%d]", expr->line, expr->col);
                exit(1);
                return;
        }
        return;
    }

    assert(expr->n_children == 2);
    node_t *left = expr->children[0];
    node_t *right = expr->children[1];

    uint16_t t_left, t_right;
    t_left = t_right = 0;
    expr_instr_type(left, &t_left, right, &t_right);
    size_t left_stack_offset = 0;

    /* Evaluate the expression. Results will be stored on the stack. */
    if (left->type == EXPRESSION)  {
        expression(ctx, func, left, stack_top);
        puts("\tpushq %rax"); // PUSH TO STACK
        (*stack_top)++;
        t_left = T_STACK;
    }
    if (right->type == EXPRESSION) {
        expression(ctx, func, right, stack_top);
        puts("\tpushq %rax"); // PUSH TO STACK
        (*stack_top)++;
        t_right = T_STACK;
        left_stack_offset = 1;
    }

    switch (*expr->data_char_ptr) {
        case '+':
            //printf("# addq, %d\n", t_right);
            emit_instr_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);
            emit_instr_mem_reg(ctx, func, "addq", right, t_right, REG_RAX, stack_top, 0);
            break;

        case '-':
            //printf("# subq, %d\n", t_right);
            emit_instr_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);
            emit_instr_mem_reg(ctx, func, "subq", right, t_right, REG_RAX, stack_top, 0);
            break;

        case '*':
            //printf("# imulq, %d\n", t_right);
            emit_instr_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);
            emit_instr_mem_reg(ctx, func, "imulq", right, t_right, REG_RAX, stack_top, 0);
            break;

        case '/':
            //printf("# idiv, %d\n", t_right);
            puts("\txor %edx, %edx");
            emit_instr_mem_reg(ctx, func, "movq", right, t_right, REG_RDI, stack_top, 0);   // right -> rdi
            emit_instr_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);     // left -> rax
            puts("\tidiv %rdi");
            break;

        default:
            debug("EXPRESSION NOT IMPLEMENTED: [%d:%d]", expr->line, expr->col);
            exit(1);
            return;
    }

    if (t_left == T_STACK) { emit_instr_imm_reg("subq", 0x8, REG_RSP); (*stack_top)--;}
    if (t_right == T_STACK) { emit_instr_imm_reg("subq", 0x8, REG_RSP); (*stack_top)--;}
    //if (t_left == T_STACK) puts("\tsubq $8, %rsp");
    //if (t_right == T_STACK) puts("\tsubq $8, %rsp");
    return;
}

static void assignment(ir_ctx_t *ctx, symbol_t *func, node_t *left, node_t *right, size_t *stack_top)
{
    (void) ctx;
    assert(left->type == IDENTIFIER_DATA);

    uint16_t t_left, t_right;
    t_left = t_right = 0;
    expr_instr_type(left, &t_left, right, &t_right);

    /* Right can be a constant (number), identifier (variable), or expression. */
    if (IS_CONST_TYPE(right->type)) {
        /* Only supported const type. */
        assert(right->type == NUMBER_DATA);

        //printf("\t# local variable: %s [%lu] = CONST local %" PRIu64 "\n", left->entry->name, left->entry->seq, right->data_integer);
        emit_instr_imm_mem(ctx, func, "movq", right->data_integer, left, t_left, stack_top, 0);

    } else if (right->type == IDENTIFIER_DATA) {
        //puts("# IDENTIFIER_DATA");
        emit_instr_mem_reg(ctx, func, "movq", right, t_right, REG_RAX, stack_top, 0);
        emit_instr_reg_mem(ctx, func, "movq", REG_RAX, left, t_left, stack_top, 0);

    } else if (right->type == EXPRESSION) {
        //puts("# BEGIN EXPRESSION");
        expression(ctx, func, right, stack_top);
        //puts("# END EXPRESSION");

        uint16_t left_t = 0;
        expr_instr_type_s(left, &left_t);

        //printf("\t# local variable: %s [%lu] = CONST local %" PRIu64 "\n", left->entry->name, left->entry->seq, right->data_integer);
        emit_instr_reg_mem(ctx, func, "movq", REG_RAX, left, left_t, stack_top, 0);
    }
}

/* print_statement():
 *      Horribly inefficient, but I guess this is how its supposed
 *      to be done in this assignment.
 */
static void print_statement(ir_ctx_t *ctx, symbol_t *func, node_t *r, size_t *stack_top)
{

    for (size_t i = 0; i < r->n_children; i++) {
        if (r->children[i]->type == STRING_DATA) {
            puts("\tleaq strout(%rip), %rdi");
            printf("\tleaq global_string_%" PRId64 "(%%rip), %%rsi\n", r->children[i]->entry_strings_index);
        } else if (r->children[i]->type == NUMBER_DATA) {
            puts("\tleaq intout(%rip), %rdi");
            //printf("\tmovq $%" PRIdit "%%rdx\n", r->children[i]->data_integer);
            emit_instr_imm_reg("movq", r->children[i]->data_integer, REG_RDX);
        } else if (r->children[i]->type == IDENTIFIER_DATA) {
            uint16_t t = 0;
            expr_instr_type_s(r->children[i], &t);
            puts("\tleaq intout(%rip), %rdi");
            emit_instr_mem_reg(ctx, func, "movq", r->children[i], t, REG_RSI, stack_top, 0);
        } else {debug("ILLEGAL type: %s", NODE_TO_TYPE_STRING(r->children[i])); exit(1);}
        puts("\txor %rax, %rax");
        puts("\tcall printf");
    }
    puts("\tmovq $10, %rdi");
    puts("\tcall putchar");
}

static void rec_traverse(ir_ctx_t *ctx, symbol_t *func, node_t *r, size_t *stack_top)
{
    if (r->type == ASSIGNMENT_STATEMENT) {
        inline_src(r);
        assignment(ctx, func, r->children[0], r->children[1], stack_top);

    } else if (r->type == PRINT_STATEMENT) {
        inline_src(r);
        print_statement(ctx, func, r, stack_top);

    } else if (r->type == EXPRESSION) {
        expression(ctx, func, r, stack_top); // Result is stored in %rax.

    } else if (r->type == RETURN_STATEMENT) {
        inline_src(r);
        assert(r->n_children == 1);
        node_t *ret_val = r->children[0];
        if (ret_val->type == EXPRESSION) {
            //puts("\t # RETURN EXPRESSION");
            expression(ctx, func, ret_val, stack_top);
        } else {
            //puts("\t # RETURN LOCAL/GLOBAL/CONST ");
            uint16_t ret_val_type = 0;
            expr_instr_type_s(ret_val, &ret_val_type);
            emit_instr_mem_reg(ctx, func, "movq", ret_val, ret_val_type, REG_RAX, stack_top, 0);
        }

        puts("\tmovq %rbp, %rsp");
        puts("\tpopq %rbp");
        puts("\tret");
    
    } else {
        for (size_t i = 0; i < r->n_children; i++)
            rec_traverse(ctx, func, r->children[i], stack_top);
    }
}

/* gen_func(): Emits a function. Assumes that this is in the .text section.
 * 1. Emits a label: _<function_name>:
 * 2. Setup stack frame: push rsp, ...
 * 3. Generate assembly code that is equivalent with the AST.
 *
 * Function calls:
 *      1. Setup parameter registers. (rax, rdi, rsi, rdx, ...)
 *      2. Use the 'call _<function_name>' to call the functions.
 *      3. Correctly assign the return value to a variable IF the
 *         AST specifies it as such. (Stored in rax).
 *
 * Returns:
 *      1. Set rax to be the return value, restore rsp (by pop).
 *
 * */
static void gen_func(ir_ctx_t *ctx, symbol_t *func)
{
    printf("_%s:\n", func->name);

    /*
     * Setup stack frame:
     * 0. Push rbp register.
     * 1. Allocate space for params and save them on the stack
     * 2. Allocate space for locals in order of their params.
     *     (FOR NOW, THIS SIMPLIFIES FUNCTION CALLS).
     * (2. ---Save param registers if needed.----)
     */

    /* Save %rbp and set %rsp.  */
    puts("\tpushq %rbp");
    puts("\tmovq %rsp, %rbp");
    assert(sizeof(int_type) == 8); // ...

    /* XXXX: Checks for when there are no params and locals? */
    /* Reserve params and locals. Params are stored at the bottom
     * values, and locals have the top. */
    uint64_t saved = VEC_LEN(func->locals);

    // 16 bytes aligned.
    uint64_t locals_aligned = saved * sizeof(int_type);
    locals_aligned += locals_aligned % 16;

    printf("\tsubq $%" PRId64 ", %%rsp\n", locals_aligned);


    /* Save the params. */
    assert(func->nparms < sizeof(regs)/sizeof(*regs));
    for (size_t i = 0; i < func->nparms; i++) {
        symbol_t *local = VEC_GET(func->locals, symbol_t_ptr, i);
        printf("\tmovq %s, %" PRId64 "(%%rbp)  # saving param #%" PRId64 ", %s\n", regs[i], VAR_INDEX_OFFSET(saved, i), i, local->name);
    }

    /* XXXX: Necessary? */
    /* Initialize locals to 0. */
    for (size_t i = func->nparms; i < saved; i++) {
        symbol_t *local = VEC_GET(func->locals, symbol_t_ptr, i);
        printf("\tmovq $0, %" PRId64 "(%%rbp)  # zeroing local #%" PRId64 ", %s\n", VAR_INDEX_OFFSET(saved, i), i, local->name);
    }

    size_t stack_top = 0;
    rec_traverse(ctx, func, func->node, &stack_top);
    assert(stack_top == 0);

    /* In case there is no end return statement. */
    node_t *func_block = func->node->children[func->node->n_children-1];
    node_t *statement_list = func_block->children[func_block->n_children-1];
    if (statement_list->children[statement_list->n_children-1]->type != RETURN_STATEMENT) {
        putchar('\n');
        puts("\txor %rax, %rax");
        puts("\tmovq %rbp, %rsp");
        puts("\tpopq %rbp");
        puts("\tret");
    }
    putchar('\n');
}

#define FOR_EACH_IN_TLHASH(tlhash_ptr, temp_var_name, statements)   \
    do {                                                            \
        size_t n_globals = tlhash_size(tlhash_ptr);                 \
        symbol_t **temp = xcalloc(n_globals, sizeof(*temp));        \
        tlhash_values(tlhash_ptr, (void **) temp);                  \
        for (size_t i = 0; i < n_globals; i++) {                    \
            symbol_t *temp_var_name = temp[i];                      \
            statements;                                             \
        }                                                           \
        free(temp);                                                 \
    } while (0)

void gen_program(ir_ctx_t *ctx)
{
    /* Generate globals. */
    gen_strtable(ctx);

    puts(".section .data");
    symbol_t *main = NULL;
    uint64_t min_main_seq = ~0;
    FOR_EACH_IN_TLHASH(&ctx->names, global,
                       /* Reserve 8 bytes (quad) for global variables. */
                       if (global->type == SYM_GLOBAL_VAR)
                           printf("\t_%s: .quad 0\n", global->name);

                       /* Save a pointer to the main function, that is,
                        * the first function. */
                       else if (global->type == SYM_FUNCTION && global->seq < min_main_seq) {
                           main = global;
                           min_main_seq = global->seq;
                       }
    );

    /* Generate main. */
    puts(".section .text");
    assert(main);
    gen_main(main);

    /* Generate functions. */
    FOR_EACH_IN_TLHASH(&ctx->names, global,
                       if (global->type == SYM_FUNCTION) {
                           debug("Generating function: %s\n", global->name);
                           gen_func(ctx, global);
                       }
    );
}