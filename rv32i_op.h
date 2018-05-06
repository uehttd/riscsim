//
// Created by ilya on 13.04.18.
//

#ifndef RISCSIM_RV32I_OP_H
#define RISCSIM_RV32I_OP_H

#include <stdint.h>
#include <stdio.h>

extern FILE* f_log;

#define log(name)   //fprintf(f_log, "%s\t%d\n", #name, *rd)
#define log_n(name) //fprintf(f_log, "%s\n", #name)

typedef void (func_op)(int32_t, int32_t, int32_t, int32_t*, char*, int32_t*);

//******************** ARITHMETIC OPERATIONS ********************

inline void  add_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 + op2;
    *pc += 4; //+4 bits since pc is pointer to int32_t
    log(add);
}

inline void  sub_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 - op2;
    *pc += 4; //+4 bits since pc is pointer to int32_t
    log(sub);
}

inline void slt_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = (op1 < op2) ? 1 : 0;
    *pc += 4;
    log(slt);
}

inline void sltu_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = ((uint32_t)op1 < (uint32_t)op2) ? 1 : 0;
    *pc += 4;
    log(sltu);
}

inline void xor_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 ^ op2;
    *pc += 4;
    log(xor);
}

inline void sll_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 << (op2 & 0x1F);
    *pc += 4;
    log(sll);
}

inline void srl_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = (uint32_t)op1 >> (op2 & 0x1F);
    *pc += 4;
    log(srl);
}

inline void sra_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 >> (op2 & 0x1F);
    *pc += 4;
    log(sra);
}

inline void or_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 | op2;
    *pc += 4;
    log(or);
}

inline void and_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 & op2;
    *pc += 4;
    log(and);
}

inline void lui_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1;
    *pc += 4;
    log(lui);
}

inline void auipc_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = op1 + *pc;
    *pc += 4;
    log(auipc);
}
//******************** UNCONDITIONAL JUMPS ********************

inline void jal_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = *pc + 4;
    *pc += offset;
    log(jal);
}

inline void jalr_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = *pc + 4;
    *pc = (offset + op1) & (0xFFFFFFFE);
    log(jalr);
}

//*************************** BRANCH ***************************

inline void beq_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *pc += (op1 == op2) ? offset : 4;
    log_n(beq);
}

inline void bne_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *pc += (op1 != op2) ? offset : 4;
    log_n(bne);
}

inline void blt_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *pc += (op1 < op2) ? offset : 4;
    log_n(blt);
}

inline void bltu_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *pc += ((uint32_t)op1 < (uint32_t)op2) ? offset : 4;
    log_n(bltu);
}

inline void bge_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *pc += (op1 >= op2) ? offset : 4;
    log_n(bge);
}

inline void bgeu_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *pc += ((uint32_t)op1 >= (uint32_t)op2) ? offset : 4;
    log_n(bgeu);
}

//************************ LOAD AND STORE ***********************

inline void   lw_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = *((int32_t*)(mem + (uint32_t)op1 + offset));
    *pc += 4;
    log(lw);
}

inline void   lh_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = *((int32_t*)(mem + (uint32_t)op1 + offset)) & 0x0000FFFF;
    if ((*rd >> 15) & 0x00000001)
        *rd = *rd | 0xFFFF0000;
    *pc += 4;
    log(lh);
}

inline void   lb_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = *((int32_t*)(mem + (uint32_t)op1 + offset)) & 0x000000FF;
    if ((*rd >> 7) & 0x00000001)
        *rd = *rd | 0xFFFFFF00;
    *pc += 4;
    log(lb);
}

inline void  lhu_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = *((int32_t*)(mem + (uint32_t)op1 + offset)) & 0x0000FFFF;
    *pc += 4;
    log(lhu);
}

inline void  lbu_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *rd = *((int32_t*)(mem + (uint32_t)op1 + offset)) & 0x000000FF;
    *pc += 4;
    log(lbu);
}

inline void   sw_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *((int32_t*)(mem + (uint32_t)op1 + offset)) = op2;
    *pc += 4;
    log_n(sw);
}

inline void   sh_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *((int16_t*)(mem + (uint32_t)op1 + offset)) = op2 & 0x0000FFFF;
    *pc += 4;
    log_n(sh);
}

inline void   sb_op(int32_t op1, int32_t op2, int32_t offset, int32_t* rd, char* mem, int32_t* pc)
{
    *((int8_t*)(mem + (uint32_t)op1 + offset)) = op2 & 0x000000FF;
    *pc += 4;
    log_n(sb);
}

#endif //RISCSIM_RV32I_OP_H
