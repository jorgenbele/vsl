#include "generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>


#include "instr.h"
#include "ir.h"
#include "utils.h"

#include "node_src.h"

/* Local variable offset. */
#define VAR_INDEX_OFFSET(saved, index) \
    (-((saved)*sizeof(int_type)) + (index)*sizeof(int_type))

/* inline_src: Generate comments of source code in the
 *             output assembly code. */
static void inline_src(node_t *node)
{
    src_always_newline = 1;

    printf("\n/*\n");
    if (node->type == EXPRESSION) node_print_expression(node);
    else node_print_statement(node);
    printf("\n*/\n");
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


/* PROTOTYPE. */
static void expression(ir_ctx_t *ctx, symbol_t *func, node_t *expr, size_t *stack_top);

/* funcall():
 *     Emit a function call procedure passing the first six parameters by
 *     registers and the rest by the stack.
 */
static void funcall(ir_ctx_t *ctx, symbol_t *func,
                    node_t *func_ident, node_t *arglist, size_t *stack_top)
{
    size_t stack_off = 0;

    size_t i = 0;
    /* Set parameters passed by registers. */
    for (; i < arglist->n_children && i < N_PARAM_REGS; i++) {
        uint16_t type = 0;
        expr_instr_type_s(arglist->children[i], &type);
        if (arglist->children[i]->type == EXPRESSION) {
            expression(ctx, func, arglist->children[i], stack_top);
            e_reg_reg("movq", REG_RAX, i);
        } else {
            e_mem_reg(ctx, func, "movq", arglist->children[i], type, i, stack_top, 0);
        }
    }


    /* Make sure that the stack is 16 bytes aligned. */
    if ((arglist->n_children - N_PARAM_REGS) % 2 != 0) {
        e_imm_reg("subq", 8, REG_RSP);
        stack_off += 8;
    }

    /* Push the rest of the parameters by stack. */
    for (size_t j = 0; j + i < arglist->n_children; j++) {
        uint16_t type = 0;
        const size_t child_idx = arglist->n_children - j - 1;
        node_t *child = arglist->children[child_idx];

        expr_instr_type_s(child, &type);

        if (child->type == EXPRESSION) {
            expression(ctx, func, child, stack_top);
            e0_reg("pushq", REG_RAX);
        } else {
            e0_mem(ctx, func, "pushq", child, type, stack_top, 0);
        }
        stack_off += 8;
    }

    printf("\tcall _%s\n", func_ident->data_char_ptr);

    /* Reset stack to before call */
    e_imm_reg("addq", stack_off, REG_RSP);
}

/* expression():
 *  Creates the assembly representing an expression.
 *  Saves the result in %rax.
 */
static void expression(ir_ctx_t *ctx, symbol_t *func, node_t *expr, size_t *stack_top)
{
    //inline_src(expr);

    if (!strcmp(expr->data_char_ptr, "func_call")) {
        assert(expr->n_children == 2);
        node_t *func_ident = expr->children[0];
        node_t *arglist = expr->children[1];
        funcall(ctx, func, func_ident, arglist, stack_top);
        return;
    }

    if (expr->n_children == 1) {
        node_t *left = expr->children[0];

        uint16_t t_left = 0;
        expr_instr_type_s(left, &t_left);

        /* Evaluate the expression. Results will be stored in %rax . */
        if (left->type == EXPRESSION) expression(ctx, func, left, stack_top);
        else e_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, 0);

        /* Has to be an identifier since '- <number>' const expressions valuate to the -<number>. */
        switch (*expr->data_char_ptr) {
            case '-': e0_reg("negq", REG_RAX); break;
            case '~': e0_reg("notq", REG_RAX); break;
            default: debug("EXPRESSION NOT IMPLEMENTED: [%d:%d]", expr->line, expr->col); exit(1); return;
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
        e0_reg("pushq", REG_RAX);
        (*stack_top)++;
        t_left = T_STACK;
    }
    if (right->type == EXPRESSION) {
        expression(ctx, func, right, stack_top);
        e0_reg("pushq", REG_RAX);
        (*stack_top)++;
        t_right = T_STACK;
        left_stack_offset = 1;
    }

    switch (*expr->data_char_ptr) {
        case '+':
            e_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);
            e_mem_reg(ctx, func, "addq", right, t_right, REG_RAX, stack_top, 0);
            break;

        case '-':
            e_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);
            e_mem_reg(ctx, func, "subq", right, t_right, REG_RAX, stack_top, 0);
            break;

        case '*':
            e_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);
            e_mem_reg(ctx, func, "imulq", right, t_right, REG_RAX, stack_top, 0);
            break;

        case '/':
            e_mem_reg(ctx, func, "movq", right, t_right, REG_RDI, stack_top, 0);   // right -> rdi
            e_mem_reg(ctx, func, "movq", left, t_left, REG_RAX, stack_top, left_stack_offset);     // left -> rax
            e0("cqo");
            e0_reg("idiv", REG_RDI);
            break;

        default:
            debug("EXPRESSION NOT IMPLEMENTED: [%d:%d]", expr->line, expr->col);
            exit(1);
            return;
    }

    if (t_left == T_STACK) { e_imm_reg("subq", 0x8, REG_RSP); (*stack_top)--;}
    if (t_right == T_STACK) { e_imm_reg("subq", 0x8, REG_RSP); (*stack_top)--;}
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

        printf("# CONST\n");
        e_imm_mem(ctx, func, "movq", right->data_integer, left, t_left, stack_top, 0);

    } else if (right->type == IDENTIFIER_DATA) {
        printf("# IDENT\n");
        e_mem_reg(ctx, func, "movq", right, t_right, REG_RAX, stack_top, 0);
        e_reg_mem(ctx, func, "movq", REG_RAX, left, t_left, stack_top, 0);

    } else if (right->type == EXPRESSION) {
        expression(ctx, func, right, stack_top);

        uint16_t left_t = 0;
        expr_instr_type_s(left, &left_t);
        printf("# EXPR\n");
        e_reg_mem(ctx, func, "movq", REG_RAX, left, left_t, stack_top, 0);
    }
}

/* print_statement():
 *      Horribly inefficient, but I guess this is how its supposed
 *      to be done in this assignment.
 */
static void print_statement(ir_ctx_t *ctx, symbol_t *func, node_t *r, size_t *stack_top)
{

    for (size_t i = 0; i < r->n_children; i++) {
        switch (r->children[i]->type) {
            case STRING_DATA:
                puts("\tleaq strout(%rip), %rdi");
                printf("\tleaq global_string_%" PRId64 "(%%rip), %%rsi\n", r->children[i]->entry_strings_index);
                break;

            case NUMBER_DATA:
                puts("\tleaq intout(%rip), %rdi");
                //printf("\tmovq $%" PRIdit "%%rdx\n", r->children[i]->data_integer);
                e_imm_reg("movq", r->children[i]->data_integer, REG_RDX);
                break;

            case IDENTIFIER_DATA: {
                uint16_t t = 0;
                expr_instr_type_s(r->children[i], &t);
                puts("\tleaq intout(%rip), %rdi");
                e_mem_reg(ctx, func, "movq", r->children[i], t, REG_RSI, stack_top, 0);
                break;
            }
            case EXPRESSION: {
                expression(ctx, func, r->children[i], stack_top);
                puts("\tleaq intout(%rip), %rdi");
                e_reg_reg("movq", REG_RAX, REG_RSI);
                break;
            }
            default:
                debug("ILLEGAL type: %s", NODE_TO_TYPE_STRING(r->children[i]));
                exit(1);
                break;
        }

        e_reg_reg("xor", REG_RAX, REG_RAX);
        puts("\tcall printf");
    }
    e_imm_reg("movq", 10, REG_RDI);
    puts("\tcall putchar");
}

static void emit_cmp(ir_ctx_t *ctx, symbol_t *func, const char *rel_str,
                     node_t *left, node_t *right,
                     uint64_t *true_label, uint64_t *false_label, size_t *stack_top)
{
    uint16_t t_left, t_right;
    t_left = t_right = 0;
    expr_instr_type(left, &t_left, right, &t_right);
    size_t left_stack_offset = 0;

    if (left->type == EXPRESSION)  {
        expression(ctx, func, left, stack_top);
        e0_reg("pushq", REG_RAX);
        (*stack_top)++;
        t_left = T_STACK;
    }

    if (right->type == EXPRESSION)  {
        expression(ctx, func, right, stack_top);
        e0_reg("pushq", REG_RAX);
        (*stack_top)++;
        t_right = T_STACK;
        left_stack_offset = 1;
    }

    e_mem_reg(ctx, func, "movq", left, t_left, REG_RDI, stack_top, left_stack_offset);
    e_mem_reg(ctx, func, "movq", right, t_right, REG_RSI, stack_top, 0);

    /* Cleanup stack before any jump. */
    if (t_left == T_STACK) { e_imm_reg("subq", 0x8, REG_RSP); (*stack_top)--;}
    if (t_right == T_STACK) { e_imm_reg("subq", 0x8, REG_RSP); (*stack_top)--;}

    e_reg_reg("cmpq", REG_RSI, REG_RDI);

    /* Lookup table mapping relation operator with
     * the jump instruction. */
    static const char *jump_instr_map[3][2] = {
        {"jge", "jl"}, /* < = 60 */
        {"jne", "je"}, /* = = 61 */
        {"jle", "jg"}, /* < = 62 */
    };

    if (!true_label)
        e0_label(jump_instr_map[*rel_str - '<'][0], *false_label);
    else {
        e0_label(jump_instr_map[*rel_str - '<'][1], *true_label);
        if (false_label) e0_label("jmp", *false_label);
    }
}

/* prototype */
static void rec_traverse(ir_ctx_t *ctx, symbol_t *func, node_t *r, size_t *stack_top);

static void if_statement(ir_ctx_t *ctx, symbol_t *func, node_t *relation,
                         node_t *true_block, node_t *else_block, size_t *stack_top)
{
    if (!else_block) {
        uint64_t false_label = ctx->label_count++;

        /* No true label since the true block is directly following this block. */
        emit_cmp(ctx, func, relation->data_char_ptr, relation->children[0],
                 relation->children[1], NULL, &false_label, stack_top);
        rec_traverse(ctx, func, true_block, stack_top);
        emit_label(false_label); /* End of if-true block. */

    } else {
        uint64_t false_label = ctx->label_count++;
        uint64_t end_if_label = ctx->label_count++;

        emit_cmp(ctx, func, relation->data_char_ptr, relation->children[0],
                 relation->children[1], NULL, &false_label, stack_top);
        rec_traverse(ctx, func, true_block, stack_top);
        e0_imm("jmp", end_if_label); /* End of if-true block, jump to end of if. */
        emit_label(false_label);
        rec_traverse(ctx, func, else_block, stack_top);
        emit_label(end_if_label); /* End of if. */
    }
}

static void while_statement(ir_ctx_t *ctx, symbol_t *func, node_t *relation,
                         node_t *while_block, size_t *stack_top)
{
    uint64_t true_label = ctx->label_count++;
    uint64_t false_label = ctx->label_count++;

    emit_label(true_label);
    emit_cmp(ctx, func, relation->data_char_ptr, relation->children[0],
             relation->children[1], NULL, &false_label, stack_top);
    rec_traverse(ctx, func, while_block, stack_top);
    e0_imm("jmp", true_label);
    emit_label(false_label);
}

static void rec_traverse(ir_ctx_t *ctx, symbol_t *func, node_t *r, size_t *stack_top)
{
    switch (r->type) {
        case ASSIGNMENT_STATEMENT:
            inline_src(r);
            assignment(ctx, func, r->children[0], r->children[1], stack_top);
            break;

        case PRINT_STATEMENT:
            inline_src(r);
            print_statement(ctx, func, r, stack_top);
            break;

        case IF_STATEMENT: {
            inline_src(r);
            node_t *else_block = NULL;
            if (r->n_children == 3) else_block = r->children[2];
            if_statement(ctx, func, r->children[0], r->children[1], else_block, stack_top);
            break;
        }

        case WHILE_STATEMENT: {
            inline_src(r);
            while_statement(ctx, func, r->children[0], r->children[1], stack_top);
            break;
        }

        case EXPRESSION: expression(ctx, func, r, stack_top); break; // Result is stored in %rax.

        case RETURN_STATEMENT: {
            inline_src(r);
            assert(r->n_children == 1);
            node_t *ret_val = r->children[0];
            if (ret_val->type == EXPRESSION) {
                expression(ctx, func, ret_val, stack_top);
            } else {
                uint16_t ret_val_type = 0;
                expr_instr_type_s(ret_val, &ret_val_type);
                e_mem_reg(ctx, func, "movq", ret_val, ret_val_type, REG_RAX, stack_top, 0);
            }

            e_reg_reg("movq", REG_RBP, REG_RSP);
            e0_reg("popq", REG_RBP);
            e0("ret");
            break;
        }

        default:
            for (size_t i = 0; i < r->n_children; i++)
                rec_traverse(ctx, func, r->children[i], stack_top);
            break;
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
    printf("\t# def %s(", func->name);
    for (size_t i = 0; i < func->nparms; i++) {
        printf("%s%s",
               VEC_GET(func->locals, symbol_t_ptr, i)->name,
               i + 1 < func->nparms ? ", " : "");
    }
    printf(")\n");

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

    /* 16 bytes aligned. */
    uint64_t locals_aligned = saved * sizeof(int_type);
    locals_aligned += locals_aligned % 16;

    /* Reserve space for variables + alignment. */
    printf("\tsubq $%" PRId64 ", %%rsp\n", locals_aligned);

    const size_t reg_params = MIN(N_PARAM_REGS, func->nparms);

    /* Save parameters passed by registers in reverse order. */
    size_t i = reg_params;
    while (i > 0) {
        symbol_t *param = VEC_GET(func->locals, symbol_t_ptr, i-1);
        printf("\tmovq %s, %" PRId64 "(%%rbp)  # saving param #%" PRId64 ", %s\n",
               param_regs[i-1], param_rsp_offset(func, param), i-1, param->name);
               //param_regs[i-1], (-reg_params+i)*8, i-1, param->name);
        assert(param->type == SYM_PARAMETER);
        i--;
    }

    /* XXXX: Necessary? */
    /* Initialize locals to 0. */
    i = saved;
    while (i > func->nparms) {
        symbol_t *local = VEC_GET(func->locals, symbol_t_ptr, i-1);
        printf("\tmovq $0, %" PRId64 "(%%rbp)  # saving local #%" PRId64 ", %s\n",
               local_rsp_offset(func, local), i-1, local->name);
               // -(i-reg_params)*8, i-1, local->name);
        assert(local->type == SYM_LOCAL_VAR);
        i--;
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
