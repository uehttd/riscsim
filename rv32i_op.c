//
// Created by ilya on 15.04.18.
//

#include <stdint.h>
#include "rv32i_op.h"


void  add_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 + op2;
    (*pc)++;
}

void sub_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 - op2;
    (*pc)++;
}

void slt_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = (op1 < op2) ? 1 : 0;
    (*pc)++;
}

void sltu_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = ((uint32_t)op1 < (uint32_t)op2) ? 1 : 0;
    (*pc)++;
}

void xor_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 ^ op2;
    (*pc)++;
}

void sll_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 << (op2 & 0x1F);
    (*pc)++;
}

void srl_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = (uint32_t)op1 >> (op2 & 0x1F);
    (*pc)++;
}

void sra_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 >> (op2 & 0x1F);
    (*pc)++;
}

void or_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 | op2;
    (*pc)++;
}

void and_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
    *rd = op1 & op2;
    (*pc)++;
}