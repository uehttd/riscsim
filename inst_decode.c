//
// Created by ilya on 14.04.18.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#include "inst_decode.h"
#include "rv32i_op.h"


#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))
#define ones_or_zeroes(bit, len) (((bit) << (len)) - (bit))
#define i_imm(inst) (slice(inst, 20, 11) \
                    | (ones_or_zeroes(slice(inst, 31, 1), 21) << 11))
#define s_imm(inst) (slice(inst, 7, 5) | (slice(inst, 25, 6) << 5) | (ones_or_zeroes(slice(inst, 31, 1), 21) << 11))
#define j_imm(inst) ((slice(inst, 21, 10) << 1) | (slice(inst, 20, 1) << 11) | (slice(inst, 12, 8) << 12) \
                    | (ones_or_zeroes(slice(inst, 31, 1), 12) << 20))
#define b_imm(inst) ((slice(inst, 8, 4) << 1) | (slice(inst, 25, 6) << 5) \
                    | (slice(inst, 7, 1) << 11) | (ones_or_zeroes(slice(inst, 31, 1), 20) << 12))
#define u_imm(inst) ((slice(inst, 12, 8) << 12) | (slice(inst, 20, 11) << 20) | (slice(inst, 31, 1) << 31))

extern int32_t x[32];

int assign_arithm_op(int32_t funct3, int32_t funct7, func_op** F_ptr)
{
    switch (funct3) {
        case ADD:
            *F_ptr = &add_op;
            return EXEC_OK;
        case SLT:
            *F_ptr = &slt_op;
            return EXEC_OK;
        case SLTU:
            *F_ptr = &sltu_op;
            return EXEC_OK;
        case XOR:
            *F_ptr = &xor_op;
            return EXEC_OK;
        case SRL: //same as case SRA
            switch (funct7)
            {
                case 0x00:
                    *F_ptr = &srl_op;
                    return EXEC_OK;
                case 0x20:
                    *F_ptr = &sra_op;
                    return EXEC_OK;
                default:
                    return EXEC_EXIT;
            }
        case SLL:
            if(funct7 == 0x00) {
                *F_ptr = &sll_op;
                return EXEC_OK;
            } else
                return EXEC_EXIT;
        case AND:
            *F_ptr = &and_op;
            return EXEC_OK;
        case OR:
            *F_ptr = &or_op;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int assign_branch_op(int32_t funct3, func_op** F_ptr)
{
    switch (funct3)
    {
        case BEQ:
            *F_ptr = &beq_op;
            return EXEC_OK;
        case BNE:
            *F_ptr = &bne_op;
            return EXEC_OK;
        case BLT:
            *F_ptr = &blt_op;
            return EXEC_OK;
        case BLTU:
            *F_ptr = &bltu_op;
            return EXEC_OK;
        case BGE:
            *F_ptr = &bge_op;
            return EXEC_OK;
        case BGEU:
            *F_ptr = &bgeu_op;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int assign_load_op(int32_t funct3, func_op** F_ptr)
{
    switch (funct3)
    {
        case LB:
            *F_ptr = &lb_op;
            return EXEC_OK;
        case LH:
            *F_ptr = &lh_op;
            return EXEC_OK;
        case LW:
            *F_ptr = &lw_op;
            return EXEC_OK;
        case LBU:
            *F_ptr = &lbu_op;
            return EXEC_OK;
        case LHU:
            *F_ptr = &lhu_op;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int assign_store_op(int32_t funct3, func_op** F_ptr)
{
    switch (funct3)
    {
        case SB:
            *F_ptr = &sb_op;
            return EXEC_OK;
        case SH:
            *F_ptr = &sh_op;
            return EXEC_OK;
        case SW:
            *F_ptr = &sw_op;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

void decode_B_type(int32_t inst, int32_t *x, char *mem, inst_t *i)
{
    i->funct3 = slice(inst, 12, 3);
    i->funct7 = 0;
    i->op1    = (x + slice(inst, 15, 5));
    i->op2    = (x + slice(inst, 20, 5));
    i->rd     = NULL;
    i->imm_offs   = b_imm(inst);
}

void decode_R_type(int32_t inst, int32_t *x, char *mem, inst_t *i)
{
    i->funct3 = slice(inst, 12, 3);
    i->funct7 = slice(inst, 25, 7);

    i->rd  = (x + slice(inst,  7, 5));
    i->op1 = (x + slice(inst, 15, 5));
    i->op2 = (x + slice(inst, 20, 5));

    i->imm_offs = 0;
}

void decode_I_type(int32_t inst, int32_t *x, char *mem, inst_t *i)
{
    i->funct3 = slice(inst, 12, 3);
    i->funct7 = slice(inst, 25, 7);
    i->imm_offs = i_imm(inst);
    i->rd     = x + slice(inst, 7, 5);
    i->op1    = x + slice(inst, 15, 5);
    i->op2    = NULL;
}

void decode_S_type(int32_t inst, int32_t *x, char *mem, inst_t *i)
{
    i->funct3 = slice(inst, 12, 3);
    i->imm_offs   = s_imm(inst);
    i->op1    = x + slice(inst, 15, 5);
    i->op2    = x + slice(inst, 20, 5);
    i->funct7 = NULL;
    i->rd     = NULL;
}

void decode_J_type(int32_t inst, int32_t *x, char *mem, inst_t *i)
{
    i->funct3 = 0;
    i->funct7 = 0;
    i->op1 = NULL;
    i->op2 = NULL;
    i->rd = x + slice(inst, 7, 5);
    i->imm_offs = j_imm(inst);
}

void decode_U_type(int32_t inst, int32_t *x, char *mem, inst_t *i)
{
    i->rd     = x + slice(inst, 7, 5);
    i->imm_offs    = u_imm(inst);
    i->op1 = NULL;
    i->op2 = NULL;
}

int get_linear_block_size(char* mem, int32_t* pc)
{
    int32_t pc0 = *pc;
    int n = 0;
    do
    {
        int32_t inst = *(int32_t*)(mem + pc0 + 4*n);
        int32_t opcode = slice(inst, 0, 7);
        n++;
        if ((opcode == BRANCH) || (opcode == JALR) || (opcode == JAL) || (opcode == ECALL))
            break;
    } while(1);
    return n;
}

int load_decode_linear_block(char *mem, int pc0, linear_block *lb, int n_inst, int32_t *x)
{
    lb->inst = (inst_t*) calloc(n_inst, sizeof(inst_t));
    lb->n_inst = n_inst;
    lb->pc0 = pc0;

    for(int i = 0; i < n_inst; i++)
    {
        int32_t inst = *(int32_t*)(mem + pc0 + 4*i);
        lb->inst[i].opcode = slice(inst, 0, 7);
        switch (lb->inst[i].opcode)
        {
            case OP:
                decode_R_type(inst, x, mem, &(lb->inst[i]));
                if ((lb->inst[i].funct3 == SUB) &&(lb->inst[i].funct7 == 0x20))
                    lb->inst[i].F = &sub_op;
                else
                    assign_arithm_op(lb->inst[i].funct3, lb->inst[i].funct7, &(lb->inst[i].F));
                break;
            case OP_IMM:
                decode_I_type(inst, x, mem, &(lb->inst[i]));
                assign_arithm_op(lb->inst[i].funct3, lb->inst[i].funct7, &(lb->inst[i].F));
                break;
            case LOAD:
                decode_I_type(inst, x, mem, &(lb->inst[i]));
                assign_load_op(lb->inst[i].funct3, &(lb->inst[i].F));
                break;
            case JALR:
                decode_I_type(inst, x, mem, &(lb->inst[i]));
                lb->inst[i].F = &jalr_op;
                break;
            case LUI:
                decode_U_type(inst, x, mem, &(lb->inst[i]));
                lb->inst[i].F = &lui_op;
                break;
            case AUIPC:
                decode_U_type(inst, x, mem, &(lb->inst[i]));
                lb->inst[i].F = &auipc_op;
                break;
            case BRANCH:
                decode_B_type(inst, x, mem, &(lb->inst[i]));
                assign_branch_op(lb->inst[i].funct3, &(lb->inst[i].F));
                break;
            case JAL:
                decode_J_type(inst, x, mem, &(lb->inst[i]));
                lb->inst[i].F = &jal_op;
                break;
            case STORE:
                decode_S_type(inst, x, mem, &(lb->inst[i]));
                assign_store_op(lb->inst[i].funct3, &(lb->inst[i].F));
                break;
            default:
                lb->inst[i].F = NULL;
                return EXEC_EXIT;

        }
    }
}

#define ld_reg(addr) (*(int32_t*)(addr))
#define ld_reg_sub(addr, funct3, funct7) (((funct3) == SUB) && ((funct7) == 0x20) ? -ld_reg(addr) : ld_reg(addr))
extern int inst_cnt;
int exec_linear_block(char* mem, int32_t* pc, linear_block* lb, FILE* f_log)
{
    for(int i = 0; i < lb->n_inst; i++)
    {
        int32_t inst = ld_reg(mem + *pc);
        int32_t rd = slice(inst, 7, 5);
        //fprintf(f_log, "%8x\t%8x\t%2d\t", *pc, inst,
        //        ((lb->inst[i].opcode != STORE) && (lb->inst[i].opcode != BRANCH)) ? rd : 0);
        if(lb->inst[i].F)
            lb->inst[i].F(  lb->inst[i].op1 ? *(lb->inst[i].op1) : lb->inst[i].imm_offs,
                        lb->inst[i].op2 ? *(lb->inst[i].op2) : lb->inst[i].imm_offs,
                        lb->inst[i].imm_offs, lb->inst[i].rd, mem, pc);
        else
            return EXEC_EXIT;
        x[0] = 0;
        inst_cnt++;
    }
    return EXEC_OK;
}

int find_linear_block(int32_t pc0, linear_block* lb_cache, int n_block)
{
    for (int i = 0; i < n_block; i++)
        if(lb_cache[i].pc0 == pc0)
            return i;
    return -1;
}

int clear_linear_block(linear_block* lb)
{
    if (!lb->inst)
        free(lb->inst);
    lb->pc0 = 0;
    lb->n_inst = 0;
}