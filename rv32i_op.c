//
// Created by yury Pavlyuk on 20.04.18.
//
#include <stdint.h>
#include "rv32i_op.h"
#include "inst_decode.h"

extern inline void  add_op(inst_t* i, char* mem, int32_t* pc);

extern inline void  sub_op(inst_t* i, char* mem, int32_t* pc);

extern inline void slt_op(inst_t* i, char* mem, int32_t* pc);

extern inline void sltu_op(inst_t* i, char* mem, int32_t* pc);

extern inline void xor_op(inst_t* i, char* mem, int32_t* pc);

extern inline void sll_op(inst_t* i, char* mem, int32_t* pc);

extern inline void srl_op(inst_t* i, char* mem, int32_t* pc);

extern inline void sra_op(inst_t* i, char* mem, int32_t* pc);

extern inline void or_op(inst_t* i, char* mem, int32_t* pc);

extern inline void and_op(inst_t* i, char* mem, int32_t* pc);

// *************** ARITHM_IMM *********************

extern inline void  addi_op(inst_t* i, char* mem, int32_t* pc);

extern inline void slti_op(inst_t* i, char* mem, int32_t* pc);

extern inline void sltui_op(inst_t* i, char* mem, int32_t* pc);

extern inline void xori_op(inst_t* i, char* mem, int32_t* pc);

extern inline void slli_op(inst_t* i, char* mem, int32_t* pc);

extern inline void srli_op(inst_t* i, char* mem, int32_t* pc);

extern inline void srai_op(inst_t* i, char* mem, int32_t* pc);

extern inline void ori_op(inst_t* i, char* mem, int32_t* pc);

extern inline void andi_op(inst_t* i, char* mem, int32_t* pc);

//*************************

extern inline void lui_op(inst_t* i, char* mem, int32_t* pc);

extern inline void auipc_op(inst_t* i, char* mem, int32_t* pc);

//******************** UNCONDITIONAL JUMPS ********************

extern inline void jal_op(inst_t* i, char* mem, int32_t* pc);

extern inline void jalr_op(inst_t* i, char* mem, int32_t* pc);

//*************************** BRANCH ***************************

extern inline void beq_op(inst_t* i, char* mem, int32_t* pc);

extern inline void bne_op(inst_t* i, char* mem, int32_t* pc);

extern inline void blt_op(inst_t* i, char* mem, int32_t* pc);

extern inline void bltu_op(inst_t* i, char* mem, int32_t* pc);

extern inline void bge_op(inst_t* i, char* mem, int32_t* pc);

extern inline void bgeu_op(inst_t* i, char* mem, int32_t* pc);

//************************ LOAD AND STORE ***********************

extern inline void   lw_op(inst_t* i, char* mem, int32_t* pc);

extern inline void   lh_op(inst_t* i, char* mem, int32_t* pc);

extern inline void   lb_op(inst_t* i, char* mem, int32_t* pc);

extern inline void  lhu_op(inst_t* i, char* mem, int32_t* pc);

extern inline void  lbu_op(inst_t* i, char* mem, int32_t* pc);

extern inline void   sw_op(inst_t* i, char* mem, int32_t* pc);

extern inline void   sh_op(inst_t* i, char* mem, int32_t* pc);

extern inline void   sb_op(inst_t* i, char* mem, int32_t* pc);

//****************************************************************

extern inline void exit_op(inst_t* i, char* mem, int32_t* pc);