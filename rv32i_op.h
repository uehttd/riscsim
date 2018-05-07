//
// Created by ilya on 13.04.18.
//

#ifndef RISCSIM_RV32I_OP_H
#define RISCSIM_RV32I_OP_H

#include <stdint.h>
#include <stdio.h>
#include "inst_decode.h"

extern FILE* f_log;

#define log(name)   //fprintf(f_log, "%s\t%d\n", #name, *rd)
#define log_n(name) //fprintf(f_log, "%s\n", #name)

#define i_op2_imm ((i->op2) ? *(i->op2) : (i->imm_offs))


//******************** ARITHMETIC OPERATIONS ********************

inline void  add_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) + i_op2_imm;
    *pc += 4; //+4 bits since pc is pointer to int32_t
    log(add);
}

inline void  sub_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) - i_op2_imm;
    *pc += 4; //+4 bits since pc is pointer to int32_t
    log(sub);
}

inline void slt_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = (*(i->op1) < i_op2_imm) ? 1 : 0;
    *pc += 4;
    log(slt);
}

inline void sltu_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = ((uint32_t)*(i->op1) < (uint32_t)i_op2_imm) ? 1 : 0;
    *pc += 4;
    log(sltu);
}

inline void xor_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) ^ i_op2_imm;
    *pc += 4;
    log(xor);
}

inline void sll_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) << (i_op2_imm & 0x1F);
    *pc += 4;
    log(sll);
}

inline void srl_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = (uint32_t)*(i->op1) >> (i_op2_imm & 0x1F);
    *pc += 4;
    log(srl);
}

inline void sra_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) >> (i_op2_imm & 0x1F);
    *pc += 4;
    log(sra);
}

inline void or_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) | i_op2_imm;
    *pc += 4;
    log(or);
}

inline void and_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) & i_op2_imm;
    *pc += 4;
    log(and);
}

inline void lui_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1);
    *pc += 4;
    log(lui);
}

inline void auipc_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *(i->op1) + *pc;
    *pc += 4;
    log(auipc);
}
//******************** UNCONDITIONAL JUMPS ********************

inline void jal_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *pc + 4;
    *pc += i->imm_offs;
    log(jal);
}

inline void jalr_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *pc + 4;
    *pc = (i->imm_offs + *(i->op1)) & (0xFFFFFFFE);
    log(jalr);
}

//*************************** BRANCH ***************************

inline void beq_op(inst_t* i, char* mem, int32_t* pc)
{
    *pc += (*(i->op1) == *(i->op2)) ? i->imm_offs : 4;
    log_n(beq);
}

inline void bne_op(inst_t* i, char* mem, int32_t* pc)
{
    *pc += (*(i->op1) != *(i->op2)) ? i->imm_offs : 4;
    log_n(bne);
}

inline void blt_op(inst_t* i, char* mem, int32_t* pc)
{
    *pc += (*(i->op1) < *(i->op2)) ? i->imm_offs : 4;
    log_n(blt);
}

inline void bltu_op(inst_t* i, char* mem, int32_t* pc)
{
    *pc += ((uint32_t)*(i->op1) < (uint32_t)*(i->op2)) ? i->imm_offs : 4;
    log_n(bltu);
}

inline void bge_op(inst_t* i, char* mem, int32_t* pc)
{
    *pc += (*(i->op1) >= *(i->op2)) ? i->imm_offs : 4;
    log_n(bge);
}

inline void bgeu_op(inst_t* i, char* mem, int32_t* pc)
{
    *pc += ((uint32_t)*(i->op1) >= (uint32_t)*(i->op2)) ? i->imm_offs : 4;
    log_n(bgeu);
}

//************************ LOAD AND STORE ***********************

inline void   lw_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *((int32_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs));
    *pc += 4;
    log(lw);
}

inline void   lh_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *((int32_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs)) & 0x0000FFFF;
    if ((*(i->rd) >> 15) & 0x00000001)
        *(i->rd) = *(i->rd) | 0xFFFF0000;
    *pc += 4;
    log(lh);
}

inline void   lb_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *((int32_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs)) & 0x000000FF;
    if ((*(i->rd) >> 7) & 0x00000001)
        *(i->rd) = *(i->rd) | 0xFFFFFF00;
    *pc += 4;
    log(lb);
}

inline void  lhu_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *((int32_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs)) & 0x0000FFFF;
    *pc += 4;
    log(lhu);
}

inline void  lbu_op(inst_t* i, char* mem, int32_t* pc)
{
    *(i->rd) = *((int32_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs)) & 0x000000FF;
    *pc += 4;
    log(lbu);
}

inline void   sw_op(inst_t* i, char* mem, int32_t* pc)
{
    *((int32_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs)) = *(i->op2);
    *pc += 4;
    log_n(sw);
}

inline void   sh_op(inst_t* i, char* mem, int32_t* pc)
{
    *((int16_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs)) = *(i->op2) & 0x0000FFFF;
    *pc += 4;
    log_n(sh);
}

inline void   sb_op(inst_t* i, char* mem, int32_t* pc)
{
    *((int8_t*)(mem + (uint32_t)*(i->op1) + i->imm_offs)) = *(i->op2) & 0x000000FF;
    *pc += 4;
    log_n(sb);
}

#endif //RISCSIM_RV32I_OP_H
