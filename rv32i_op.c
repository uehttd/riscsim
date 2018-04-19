//
// Created by ilya on 15.04.18.
//

#include <stdint.h>
#include "rv32i_op.h"

//******************** ARITHMETIC OPERATIONS ********************
//TODO ensure of the right increments of pc value
void  add_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 + op2;
    *pc += 4; //+4 bits since pc is pointer to int32_t
}

void sub_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 - op2;
    *pc += 4;
}

void slt_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = (op1 < op2) ? 1 : 0;
    *pc += 4;
}

void sltu_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = ((uint32_t)op1 < (uint32_t)op2) ? 1 : 0;
    *pc += 4;
}

void xor_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 ^ op2;
    *pc += 4;
}

void sll_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 << (op2 & 0x1F);
    *pc += 4;
}

void srl_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = (uint32_t)op1 >> (op2 & 0x1F);
    *pc += 4;
}

void sra_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 >> (op2 & 0x1F);
    *pc += 4;
}

void or_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 | op2;
    *pc += 4;
}

void and_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 & op2;
    *pc += 4;
}

//******************** UNCONDITIONAL JUMPS ********************

void jal_op(int32_t offset, int32_t *rd, int32_t *pc)
{
    *rd = *pc + 4;
    *pc += offset;
}

void jalr_op(int32_t offset, int32_t base, int32_t* rd, int32_t* pc)
{
    *rd = *pc + 4;
    *pc += (offset + base) & (0xFFFE);
}

void beq_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 == op2) ? offset : 4;
}

void bne_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 != op2) ? offset : 4;
}

void blt_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 < op2) ? offset : 4;
}

void bltu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += ((uint32_t)op1 < (uint32_t)op2) ? offset : 4;
}

void bge_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += (op1 >= op2) ? offset : 4;
}

void bgeu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    *pc += ((uint32_t)op1 >= (uint32_t)op2) ? offset : 4;
}

