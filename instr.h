#ifndef __INSTR_H_
#define __INSTR_H_

#include <stdio.h>
#include <inttypes.h>

#include "node.h"
#include "nodetypes.h"
#include "ir.h"
#include "utils.h"

#include "node_src.h"

#define REG_LIST \
  X(REG_RDI, "%rdi", 0x0)  \
  X(REG_RSI, "%rsi", 0x1)  \
  X(REG_RDX, "%rdx", 0x2)  \
  X(REG_RCX, "%rcx", 0x3)  \
  X(REG_R8 ,  "%r8", 0x4)  \
  X(REG_R9 ,  "%r9", 0x5)  \
  X(REG_RAX, "%rax", 0x6)  \
  X(REG_RSP, "%rsp", 0x7)  \
  X(REG_RBP, "%rbp", 0x8)  \
  X(REG_R10, "%r10", 0x9)  \
  X(REG_R11, "%r11", 0xA)  \
  X(REG_RBX, "%rbx", 0xB)  \
  X(REG_R12, "%r12", 0xC)  \
  X(REG_R13, "%r13", 0xD)  \
  X(REG_R14, "%r14", 0x10) \
  X(REG_R15, "%r15", 0x11)

typedef uint64_t label_t;

#define X(name, str, value) name = value,
typedef enum reg_t {
    REG_LIST
} reg_t;
#undef X

static const char *param_regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"
};
#define N_PARAM_REGS (sizeof(param_regs)/sizeof(*param_regs))

/* Registers that can be used without restoring their value.
 * NOTE: RAX, RDI, RSI, R8 and R9 are reserved for expression and
 *       parameters. */
static const reg_t scratch_regs[] = {
 /* REG_RAX, REG_RSI, REG_RDI, REG_R8, REG_R9, */ REG_R10, REG_R11
};
#define N_SCRATCH_REGS (sizeof(scratch_regs)/sizeof(*scratch_regs))

/* Registers that can be use but the value has to be restored. */
static const reg_t saved_regs[] = {
 REG_R12, REG_R13, REG_R14, REG_R15
};
#define N_SAVED_REGS (sizeof(saved_regs)/sizeof(*saved_regs))

#define X(name, str, value) str,
static const char *regs[] = {
    REG_LIST
};
#undef X
#define N_REGS (sizeof(regs)/sizeof(*regs))

#define T_REG_TO_REG(value) value - T_IS_REG

#define X(name, str, value) T_##name = ((value) | T_IS_REG),
typedef enum oper_t {
   T_STACK  = 0x0,
   T_REG    = 0x1,
   T_LOCAL  = 0x2,
   T_GLOBAL = 0x4,
   T_CONST  = 0x8,
   T_PARAM  = 0x10,

   /*
    * The following is not used since all locals
    * and parameters are stored on the stack (when in a function).
    *
    * NOTE: Actually used in temporary expression results.
    */
   T_IS_REG = 0x100, /* Check if T_REG_... by (oper_t) val & T_IS_REG. */

   REG_LIST
} oper_t;
#undef X

/*
 * Stack frame:
 *
 * ===============================
 * | <padding>                   |
 * | stack parameters:           |
 * |    +parameter ..            |
 * |    +parameter 7             |
 * |    +parameter 6             |
 * | return adress (8 bytes)     |
 * | saved registers  (8 bytes)  |
 * ------- stack frame -----------
 * | local variables             |
 * | register parameters: (saved)|
 * |    +parameter 5             |
 * |    +parameter 4             |
 * |    +parameter ...           |
 * |    +parameter 0             |
 * | <padding>                   |
 * ===============================
 */


#include <assert.h>

/* param_rsp_offset(): Calculate the rsp offset for the given param. */
inline static int64_t param_rsp_offset(symbol_t *func, symbol_t *param)
{
    (void) func;
    int64_t offset = 0;
    assert(param->type == SYM_PARAMETER);

    if (param->seq >= N_PARAM_REGS) {
        /* Parameter seq exceeds the number of
         * parameters that fits in registers. Must therefore
         * be on the stack. */
         offset = 16 + (param->seq - N_PARAM_REGS)*8;
         goto end;
    }
    /* Parameter was passed as register and is stored after
     * the local variables. */
    offset = -param->seq*8  - (VEC_LEN(func->locals) - func->nparms)*8 - 8;

end:
    assert(offset != 0);
    return offset;
}

/* local_rsp_offset(): Calculate the rsp offset for the given local. */
inline static int64_t local_rsp_offset(symbol_t *func, symbol_t *local)
{
    int64_t offset = 0;
    assert(local->type == SYM_LOCAL_VAR);
    offset = -local->seq*8 - 8;
    assert(offset != 0);
    return offset;
}

/* instr_type(): Convert node types to instruction operand type. */
inline static oper_t instr_type(node_t *n)
{
    oper_t t = 0;
    if (n->type == IDENTIFIER_DATA) {
        if (n->entry->type == SYM_GLOBAL_VAR)     t = T_GLOBAL;
        else if (n->entry->type == SYM_LOCAL_VAR) t = T_LOCAL;
        else if (n->entry->type == SYM_PARAMETER) t = T_PARAM;
    } else if (n->type == NUMBER_DATA)            t = T_CONST;
    return t;
}

inline static void e_comment(const char *fmt, ...)
{
    printf(" # ");
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    putchar('\n');
}

inline static void emit_label_nnl(label_t label)                  { printf("\n.L%" PRId64 ":", label);          }
inline static void e0_reg_nnl(const char *instr, reg_t reg)       { printf("\t%s %s", instr, regs[reg]);        }
inline static void e0_nnl(const char *instr)                      { printf("\t%s", instr);                      }
inline static void e0_imm_nnl(const char *instr, int_type imm)    { printf("\t%s .L%" PRIdit "", instr, imm);   }
inline static void e0_label_nnl(const char *instr, label_t label) { printf("\t%s .L%" PRId64 "", instr, label); }
inline static void e_imm_reg_nnl(const char *instr, int_type imm, reg_t reg) { printf("\t%s $%" PRIdit ", %s", instr, imm, regs[reg]); }
inline static void e_reg_reg_nnl(const char *instr, reg_t reg_left, reg_t reg_right) { printf("\t%s %s, %s", instr, regs[reg_left], regs[reg_right]); }

inline static void emit_label(label_t label)                  { emit_label_nnl(label);  putchar('\n'); }
inline static void e0_reg(const char *instr, reg_t reg)       { e0_reg_nnl(instr, reg); putchar('\n'); }
inline static void e0(const char *instr)                      { e0_nnl(instr);              putchar('\n'); }
inline static void e0_imm(const char *instr, int_type imm)    { e0_imm_nnl(instr, imm);     putchar('\n'); }
inline static void e0_label(const char *instr, label_t label) { e0_label_nnl(instr, label); putchar('\n'); }
inline static void e_imm_reg(const char *instr, int_type imm, reg_t reg) { e_imm_reg_nnl(instr, imm, reg); putchar('\n'); }
inline static void e_reg_reg(const char *instr, reg_t reg_left, reg_t reg_right) { e_reg_reg_nnl(instr, reg_left, reg_right); putchar('\n'); }


inline static void e_expr_comment(node_t *expr)
{
    printf(" # ");
    src_newline = SRC_NEVER_NEWLINE;
    node_print_expression(expr);
    putchar('\n');
}

inline static void e_param_comment(node_t *left, oper_t t_left, node_t *right, oper_t t_right)
{
    if (!right) {
        if (t_left == T_CONST) e_comment("%" PRIdit, left->data_integer);
        else if (left->entry)  e_comment("%s", left->entry->name);
        return;
    }

    if (t_left == T_CONST && t_right == T_CONST) e_comment("%" PRIdit ", %" PRIdit, left->data_integer, right->data_integer);
    else if (t_left == T_CONST)                  e_comment("%" PRIdit ", %s", left->data_integer, right->entry->name);
    else if (t_left == T_CONST)                  e_comment("%" PRIdit ", %s", left->entry->name, right->data_integer);
    else                                         e_comment("%s, %s", left->entry->name, right->entry->name);
}

inline static void e_param(ir_ctx_t *ctx, symbol_t *func, node_t *n, oper_t t_n, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) stack_top;
    uint64_t saved = VEC_LEN(func->locals);
    uint64_t locals_aligned = saved * sizeof(int_type);
    locals_aligned += locals_aligned % 16;

    switch (t_n) {
        case T_STACK: printf("%" PRId64 "(%%rsp)", (stack_offset)*sizeof(int_type)); break;
        case T_REG:   debug("Not supported!"); exit(1); break;
        case T_PARAM: printf("%" PRId64 "(%%rbp)", param_rsp_offset(func, n->entry)); break;
        case T_LOCAL: printf("%" PRId64 "(%%rbp)", local_rsp_offset(func, n->entry)); break;

        case T_GLOBAL: printf("_%s(%%rip)", n->entry->name); break;
        case T_CONST:  printf("$%" PRIdit, n->data_integer); break;

        /* Case for all regs: */
        #define X(name, str, value) case T_##name:
        REG_LIST
        #undef X
            printf("%s", regs[T_REG_TO_REG(t_n)]);
            break;
    }
}

inline static void e0_mem_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, oper_t t_left, size_t *stack_top, size_t stack_offset)
{
    printf("\t%s ", instr);
    e_param(ctx, func, left, t_left, stack_top, stack_offset);
}

inline static void e_mem_reg_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, oper_t t_left, reg_t reg, size_t *stack_top, size_t stack_offset)
{
    printf("\t%s ", instr);
    e_param(ctx, func, left, t_left, stack_top, stack_offset);
    printf(", %s", regs[reg]);
}

inline static void e_reg_mem_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr, reg_t reg,
                               node_t *right, oper_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("%s, ", regs[reg]);
    e_param(ctx, func, right, t_right, stack_top, stack_offset);
}

inline static void e_imm_mem_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr, int_type imm,
                               node_t *right, oper_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("$%" PRIdit", ", imm);
    e_param(ctx, func, right, t_right, stack_top, stack_offset);
}


inline static void e0_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, oper_t t_left, size_t *stack_top, size_t stack_offset)
{
    e0_mem_nnl(ctx, func, instr, left, t_left, stack_top, stack_offset);
    //e_param_comment(left, t_left, NULL, 0);
    putchar('\n');
}

inline static void e_mem_reg(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, oper_t t_left, reg_t reg, size_t *stack_top, size_t stack_offset)
{
    e_mem_reg_nnl(ctx, func, instr, left, t_left, reg, stack_top, stack_offset);
    //e_param_comment(left, t_left, NULL, 0);
    putchar('\n');
}

inline static void e_reg_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, reg_t reg,
                               node_t *right, oper_t t_right, size_t *stack_top, size_t stack_offset)
{
    e_reg_mem_nnl(ctx, func, instr, reg, right, t_right, stack_top, stack_offset);
    //e_param_comment(right, t_right, NULL, 0);
    putchar('\n');
}

inline static void e_imm_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, int_type imm,
                               node_t *right, oper_t t_right, size_t *stack_top, size_t stack_offset)
{
    e_imm_mem_nnl(ctx, func, instr, imm, right, t_right, stack_top, stack_offset);
    //e_param_comment(right, t_right, NULL, 0);
    putchar('\n');
}

#endif // __INSTR_H_
