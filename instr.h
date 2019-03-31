#ifndef __INSTR_H_
#define __INSTR_H_

#include <stdio.h>
#include <inttypes.h>

#include "node.h"
#include "nodetypes.h"
#include "ir.h"
#include "utils.h"

#include "node_src.h"

enum {
  REG_RDI = 0x0,
  REG_RSI = 0x1,
  REG_RDX = 0x2,
  REG_RCX = 0x3,
  REG_R8  = 0x4,
  REG_R9  = 0x5,
  REG_RAX = 0x6,
  REG_RSP = 0x7,
  REG_RBP = 0x8,
  REG_R10  = 0x9,
  REG_R11 = 0xA
};

static const char *param_regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"
};

#define N_PARAM_REGS 6

static const char *regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9", "%rax", "%rsp", "%rbp", "%r10", "%r11"
};

enum {
   T_STACK=0x0,
   T_REG=0x1,
   T_LOCAL=0x2,
   T_GLOBAL=0x4,
   T_CONST=0x8,
   T_PARAM=0x10,
};

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

inline static int64_t local_rsp_offset(symbol_t *func, symbol_t *local)
{
    int64_t offset = 0;
    assert(local->type == SYM_LOCAL_VAR);
    offset = -local->seq*8 - 8;
    assert(offset != 0);
    return offset;
}

inline static uint16_t instr_type(node_t *n)
{
    uint16_t t = 0;
    if (n->type == IDENTIFIER_DATA) {
        if (n->entry->type == SYM_GLOBAL_VAR)     t = T_GLOBAL;
        else if (n->entry->type == SYM_LOCAL_VAR) t = T_LOCAL;
        else if (n->entry->type == SYM_PARAMETER) t = T_PARAM;
    } else if (n->type == NUMBER_DATA)            t = T_CONST;
    return t;
}

inline static void expr_instr_type_s(node_t *n, uint16_t *out)
{
    if (n->type == IDENTIFIER_DATA) {
        if (n->entry->type == SYM_GLOBAL_VAR)     *out |= T_GLOBAL;
        else if (n->entry->type == SYM_LOCAL_VAR) *out |= T_LOCAL;
        else if (n->entry->type == SYM_PARAMETER) *out |= T_PARAM;
    } else if (n->type == NUMBER_DATA)            *out |= T_CONST;
}

/* expr_instr_type: Create a representation of the instruction operand types. */
inline static void expr_instr_type(node_t *left, uint16_t *tl, node_t *right, uint16_t *tr) {
    *tl = instr_type(left);
    *tr = instr_type(right);
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

inline static void emit_label_nnl(uint64_t label)                  { printf("\n.L%" PRId64 ":", label);          }
inline static void e0_reg_nnl(const char *instr, uint8_t reg)      { printf("\t%s %s", instr, regs[reg]);        }
inline static void e0_nnl(const char *instr)                       { printf("\t%s", instr);                      }
inline static void e0_imm_nnl(const char *instr, int_type imm)     { printf("\t%s .L%" PRIdit "", instr, imm);   }
inline static void e0_label_nnl(const char *instr, uint64_t label) { printf("\t%s .L%" PRId64 "", instr, label); }
inline static void e_reg_reg_nnl(const char *instr, uint8_t reg_left, uint8_t reg_right) { printf("\t%s %s, %s", instr, regs[reg_left], regs[reg_right]); }
inline static void e_imm_reg_nnl(const char *instr, int_type imm, uint8_t reg) { printf("\t%s $%" PRIdit ", %s", instr, imm, regs[reg]); }

inline static void emit_label(uint64_t label)                  { emit_label_nnl(label);  putchar('\n'); }
inline static void e0_reg(const char *instr, uint8_t reg)      { e0_reg_nnl(instr, reg); putchar('\n'); }
inline static void e0(const char *instr)                       { e0_nnl(instr);              putchar('\n'); }
inline static void e0_imm(const char *instr, int_type imm)     { e0_imm_nnl(instr, imm);     putchar('\n'); }
inline static void e0_label(const char *instr, uint64_t label) { e0_label_nnl(instr, label); putchar('\n'); }
inline static void e_reg_reg(const char *instr, uint8_t reg_left, uint8_t reg_right) { e_reg_reg_nnl(instr, reg_left, reg_right); putchar('\n'); }
inline static void e_imm_reg(const char *instr, int_type imm, uint8_t reg) { e_imm_reg_nnl(instr, imm, reg); putchar('\n'); }


inline static void e_expr_comment(node_t *expr)
{
    printf(" # ");
    src_newline = SRC_NEVER_NEWLINE;
    node_print_expression(expr);
    putchar('\n');
}

inline static void e_param_comment(node_t *left, uint8_t t_left, node_t *right, uint8_t t_right)
{
    if (!right) {
        if (t_left == T_CONST ) {
            e_comment("%" PRIdit, left->data_integer);
        } else if (left->entry) {
            e_comment("%s", left->entry->name);
        }
        return;
    }

    if (t_left == T_CONST && t_right == T_CONST) {
        e_comment("%" PRIdit ", %" PRIdit, left->data_integer, right->data_integer);
    } else if (t_left == T_CONST) {
        e_comment("%" PRIdit ", %s", left->data_integer, right->entry->name);
    } else if (t_left == T_CONST) {
        e_comment("%" PRIdit ", %s", left->entry->name, right->data_integer);
    } else {
        e_comment("%s, %s", left->entry->name, right->entry->name);
    }
}

inline static void e_param(ir_ctx_t *ctx, symbol_t *func, node_t *n, uint8_t t_n, size_t *stack_top, size_t stack_offset)
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
    }
}

inline static void e0_mem_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, uint8_t t_left, size_t *stack_top, size_t stack_offset)
{
    printf("\t%s ", instr);
    e_param(ctx, func, left, t_left, stack_top, stack_offset);
}

inline static void e_mem_reg_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, uint8_t t_left, uint8_t reg, size_t *stack_top, size_t stack_offset)
{
    printf("\t%s ", instr);
    e_param(ctx, func, left, t_left, stack_top, stack_offset);
    printf(", %s", regs[reg]);
}

inline static void e_reg_mem_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr, uint8_t reg,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("%s, ", regs[reg]);
    e_param(ctx, func, right, t_right, stack_top, stack_offset);
}

inline static void e_imm_mem_nnl(ir_ctx_t *ctx, symbol_t *func, const char *instr, int_type imm,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("$%" PRIdit", ", imm);
    e_param(ctx, func, right, t_right, stack_top, stack_offset);
}


inline static void e0_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, uint8_t t_left, size_t *stack_top, size_t stack_offset)
{
    e0_mem_nnl(ctx, func, instr, left, t_left, stack_top, stack_offset);
    //e_param_comment(left, t_left, NULL, 0);
    putchar('\n');
}

inline static void e_mem_reg(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, uint8_t t_left, uint8_t reg, size_t *stack_top, size_t stack_offset)
{
    e_mem_reg_nnl(ctx, func, instr, left, t_left, reg, stack_top, stack_offset);
    //e_param_comment(left, t_left, NULL, 0);
    putchar('\n');
}

inline static void e_reg_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, uint8_t reg,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    e_reg_mem_nnl(ctx, func, instr, reg, right, t_right, stack_top, stack_offset);
    //e_param_comment(right, t_right, NULL, 0);
    putchar('\n');
}

inline static void e_imm_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, int_type imm,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    e_imm_mem_nnl(ctx, func, instr, imm, right, t_right, stack_top, stack_offset);
    //e_param_comment(right, t_right, NULL, 0);
    putchar('\n');
}

#endif // __INSTR_H_
