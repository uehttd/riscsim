//
// Created by ilya on 15.04.18.
//

#include <stdint.h>
#include "rv32i_op.h"

//******************** ARITHMETIC OPERATIONS ********************
//TODO ensure of the right increments of pc value
inline void  add_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 + op2;
    *pc += 4; //+4 bits since pc is pointer to int32_t
}

inline void sub_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 - op2;
    *pc += 4;
}

inline void slt_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = (op1 < op2) ? 1 : 0;
    *pc += 4;
}

inline void sltu_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = ((uint32_t)op1 < (uint32_t)op2) ? 1 : 0;
    *pc += 4;
}

inline void xor_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 ^ op2;
    *pc += 4;
}

inline void sll_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 << (op2 & 0x1F);
    *pc += 4;
}

inline void srl_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = (uint32_t)op1 >> (op2 & 0x1F);
    *pc += 4;
}

inline void sra_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 >> (op2 & 0x1F);
    *pc += 4;
}

inline void or_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 | op2;
    *pc += 4;
}

inline void and_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 & op2;
    *pc += 4;
}

//******************** UNCONDITIONAL JUMPS ********************

inline void jal_op(int32_t offset, int32_t *rd, int32_t *pc)
{
    *rd = *pc + 4;
    *pc += offset;
}

inline void jalr_op(int32_t offset, int32_t base, int32_t* rd, int32_t* pc)
{
    *rd = *pc + 4;
    *pc += (offset + base) & (0xFFFE);
}

//*************************** BRANCH ***************************

inline void beq_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 == op2) ? offset : 4;
}

inline void bne_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 != op2) ? offset : 4;
}

inline void blt_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 < op2) ? offset : 4;
}

inline void bltu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += ((uint32_t)op1 < (uint32_t)op2) ? offset : 4;
}

inline void bge_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 >= op2) ? offset : 4;
}

inline void bgeu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += ((uint32_t)op1 >= (uint32_t)op2) ? offset : 4;
}

//************************ LOAD AND STORE ***********************

inline void   lw_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc)
{
    *rd = *((int32_t*)(mem + base + offset));
    *pc += 4;
}

inline void   lh_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc)
{
    *rd = *((int32_t*)(mem + base + offset)) & 0x0000FFFF;
    if ((*rd >> 15) & 0x00000001)
        *rd = *rd | 0xFFFF0000;
    *pc += 4;
}

inline void   lb_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc)
{
    *rd = *((int32_t*)(mem + base + offset)) & 0x000000FF;
    if ((*rd >> 7) & 0x00000001)
        *rd = *rd | 0xFFFFFF00;
    *pc += 4;
}

inline void  lhu_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc)
{
    *rd = *((int32_t*)(mem + base + offset)) & 0x0000FFFF;
    *pc += 4;
}

inline void  lbu_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc)
{
    *rd = *((int32_t*)(mem + base + offset)) & 0x000000FF;
    *pc += 4;
}

inline void   sw_op(int32_t offset, int32_t base, char* mem, int32_t val, int32_t* pc)
{
    *((int32_t*)(mem + base + offset)) = val;
    *pc += 4;
}

inline void   sh_op(int32_t offset, int32_t base, char* mem, int32_t val, int32_t* pc)
{
    *((int16_t*)(mem + base + offset)) = val & 0x0000FFFF;
    *pc += 4;
}

inline void   sb_op(int32_t offset, int32_t base, char* mem, int32_t val, int32_t* pc)
{
    *((int8_t*)(mem + base + offset)) = val & 0x000000FF;
    *pc += 4;
}