#ifndef __INSTR_H_
#define __INSTR_H_

#include <stdio.h>
#include <inttypes.h>

#include "node.h"
#include "nodetypes.h"
#include "ir.h"
#include "utils.h"

enum {
  REG_RDI = 0x0,
  REG_RSI = 0x1,
  REG_RDX = 0x2,
  REG_RCX = 0x3,
  REG_R8  = 0x4,
  REG_R9  = 0x5,
  REG_RAX = 0x6,
  REG_RSP = 0x7,
  REG_RBP = 0x8
};

static const char *param_regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"
};

#define N_PARAM_REGS 6

static const char *regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9", "%rax", "%rsp", "%rbp"
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
 * | register parameters:        |
 * |    +parameter 5             |
 * |    +parameter 4             |
 * |    +parameter ...           |
 * |    +parameter 0             |
 * | local variables             |
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
    /* Parameter was passed as register and is stored at the beginning
     * of the stack frame. */
    offset = -param->seq*8 - 8;

end:
    assert(offset != 0);
    return offset;
}

inline static int64_t local_rsp_offset(symbol_t *func, symbol_t *local)
{
    int64_t offset = 0;
    assert(local->type == SYM_LOCAL_VAR);

    if (func->nparms >= N_PARAM_REGS) {
        offset = -local->seq*8 - N_PARAM_REGS*8 - 8;
        goto end;
    }
    offset = -local->seq*8 - func->nparms*8 - 8;

end:
    assert(offset != 0);
    return offset;


    ////assert(local->entry->type == SYM_LOCAL_VAR);
    //if (func->nparms >= N_PARAM_REGS) {
    //     return -(local->seq + N_PARAM_REGS)*8 - 8*2;
    //}
    //return -local->seq*8 + func->nparms*8 - 8*2;
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
    expr_instr_type_s(left, tl);
    expr_instr_type_s(right, tr);
}


inline static void emit_label(uint64_t label) { printf("\n_label_%" PRId64 ":\n", label); }

inline static void e0_reg(const char *instr, uint8_t reg) { printf("\t%s %s\n", instr, regs[reg]); }
inline static void e0(const char *instr) { printf("\t%s\n", instr); }
inline static void e0_imm(const char *instr, int_type imm) { printf("\t%s _label_%" PRIdit "\n", instr, imm); }
inline static void e0_label(const char *instr, uint64_t label) { printf("\t%s _label_%" PRId64 "\n", instr, label); }

inline static void e_reg_reg(const char *instr, uint8_t reg_left, uint8_t reg_right) { printf("\t%s %s, %s\n", instr, regs[reg_left], regs[reg_right]); }

inline static void e_param(ir_ctx_t *ctx, symbol_t *func, node_t *n, uint8_t t_n, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) stack_top;
    uint64_t saved = VEC_LEN(func->locals);
    uint64_t locals_aligned = saved * sizeof(int_type);
    locals_aligned += locals_aligned % 16;

    switch (t_n) {
        case T_STACK:  printf("%" PRId64 "(%%rsp)", (stack_offset)*sizeof(int_type)); break;
        case T_REG:    debug("Not supported!"); exit(1); break;

        case T_PARAM: printf("%" PRId64 "(%%rbp)", param_rsp_offset(func, n->entry)); break;
        case T_LOCAL: printf("%" PRId64 "(%%rbp)", local_rsp_offset(func, n->entry)); break;

        case T_GLOBAL: printf("_%s(%%rip)", n->entry->name); break;
        case T_CONST:  printf("$%" PRIdit, n->data_integer); break;
    }
}

inline static void e0_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, uint8_t t_left, size_t *stack_top, size_t stack_offset)
{
    printf("\t%s ", instr);
    e_param(ctx, func, left, t_left, stack_top, stack_offset);
    puts("");
}

inline static void e_mem_reg(ir_ctx_t *ctx, symbol_t *func, const char *instr,
                               node_t *left, uint8_t t_left, uint8_t reg, size_t *stack_top, size_t stack_offset)
{
    printf("\t%s ", instr);
    e_param(ctx, func, left, t_left, stack_top, stack_offset);
    printf(", %s\n", regs[reg]);
}

inline static void e_reg_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, uint8_t reg,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("%s, ", regs[reg]);
    e_param(ctx, func, right, t_right, stack_top, stack_offset);
    putchar('\n');
}

inline static void e_imm_mem(ir_ctx_t *ctx, symbol_t *func, const char *instr, int_type imm,
                               node_t *right, uint8_t t_right, size_t *stack_top, size_t stack_offset)
{
    (void) ctx; (void) func;
    printf("\t%s ", instr);
    printf("$%" PRIdit", ", imm);
    e_param(ctx, func, right, t_right, stack_top, stack_offset);
    putchar('\n');
}

inline static void e_imm_reg(const char *instr, int_type imm, uint8_t reg) { printf("\t%s $%" PRIdit ", %s\n", instr, imm, regs[reg]); }

#endif // __INSTR_H_
