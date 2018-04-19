//
// Created by ilya on 14.04.18.
//

#include <stdint.h>

#include "inst_decode.h"
#include "rv32i_op.h"


#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))
#define ones_or_zeroes(bit, len) (((bit) << (len)) - (bit))
#define i_imm(inst) (slice(inst, 20, 1) \
                    | (ones_or_zeroes(slice(inst, 31, 1), 21) << 11))
#define s_imm(inst) (slice(inst, 7, 5) | (slice(inst, 25, 6) << 5) | (ones_or_zeroes(slice(inst, 31, 1), 21) << 11))
#define j_imm(inst) ((slice(inst, 21, 10) << 1) | (slice(inst, 20, 1) << 11) \
                    | (slice(inst, 12, 8) << 12) | (ones_or_zeroes((inst, 31, 1), 12)))
#define b_imm(inst) ((slice(inst, 8, 4) << 1) | (slice(inst, 25, 6) << 5) \
                    | (slice(inst, 7, 1) << 11) | (ones_or_zeroes(slice(inst, 31, 1), 20) << 12))
int decode_arithm_op(int32_t funct3, int32_t funct7, int32_t op1, int32_t op2, int32_t* rd, int32_t* pc) {
    switch (funct3) {
        case ADD:
            add_op(op1, op2, rd, pc);
            return EXEC_OK;
        case SLT:
            slt_op(op1, op2, rd, pc);
            return EXEC_OK;
        case SLTU:
            sltu_op(op1, op2, rd, pc);
            return EXEC_OK;
        case XOR:
            xor_op(op1, op2, rd, pc);
            return EXEC_OK;
        case SRL: //same as case SRA
            switch (funct7)
            {
                case 0x00:
                    srl_op(op1, op2 & 0x1F, rd, pc); //TODO ensure that reg-reg operations will behave the same
                    return EXEC_OK;
                case 0x20:
                    sra_op(op1, op2 & 0x1F, rd, pc); //TODO ensure that reg-reg operations will behave the same
                    return EXEC_OK;
                default:
                    return EXEC_EXIT;
            }
        case SLL:
            if(funct7 == 0x00) {
                sll_op(op1, op2 & 0x1F, rd, pc);
                return EXEC_OK;
            } else
                return EXEC_EXIT;
        case AND:
            and_op(op1, op2, rd, pc);
            return EXEC_OK;
        case OR:
            or_op(op1, op2, rd, pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_branch_op(int32_t funct3, int32_t offset, int32_t op1, int32_t op2, int32_t* pc)
{
    switch (funct3)
    {
        case BEQ:
            beq_op(offset, op1, op2, pc);
            return EXEC_OK;
        case BNE:
            bne_op(offset, op1, op2, pc);
            return EXEC_OK;
        case BLT:
            blt_op(offset, op1, op2, pc);
            return EXEC_OK;
        case BLTU:
            bltu_op(offset, op1, op2, pc);
            return EXEC_OK;
        case BGE:
            bge_op(offset, op1, op2, pc);
            return EXEC_OK;
        case BGEU:
            bgeu_op(offset, op1, op2, pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_B_type(int32_t inst, int32_t* x, int32_t* mem, int32_t* pc)
{
    int funct3 = slice(inst, 12, 3);
    int imm    = b_imm(inst);
    int rs1    = slice(inst, 15, 5);
    int rs2    = slice(inst, 20, 5);
    return decode_branch_op(funct3, imm, x[rs1], x[rs2], pc);
}

int decode_R_type(int32_t inst, int32_t* x, int32_t* mem, int32_t* pc) {
    int funct3 = slice(inst, 12, 3);
    int funct7 = slice(inst, 25, 7);
    int rd     = slice(inst,  7, 5);
    int rs1    = slice(inst, 15, 5);
    int rs2    = slice(inst, 20, 5);

    decode_arithm_op(funct3, funct7, rs1, rs2, &rd, pc);
}

int decode_I_type(int32_t inst, int32_t* x, int32_t* mem, int32_t* pc) {
    int funct3 = slice(inst, 12,  3);
    int funct7 = slice(inst, 25, 7);
    int imm    = i_imm(inst);
    int rs1    = slice(inst, 15,  5);
    int rd     = slice(inst,  7,  5);

    decode_arithm_op(funct3, funct7, rs1, imm, &rd, pc);
}

int exec_command(int32_t* x, int32_t* mem, int32_t* pc) {
    int32_t inst = mem[*pc];
    int opcode = slice(inst, 0, 7);
    int ret_status = EXEC_EXIT;
    if (opcode == OP) {
        ret_status = decode_R_type(inst, x, mem, pc);
    }
    else if (opcode == OP_IMM) {
        ret_status = decode_I_type(inst, x, mem, pc);
    }

    return ret_status;
}

