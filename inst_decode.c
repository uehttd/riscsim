//
// Created by ilya on 14.04.18.
//

#include <stdint.h>

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

int decode_arithm_op(int32_t funct3, int32_t funct7, int32_t op1, int32_t op2, int32_t* rd, int32_t* pc)
{
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

int decode_load_op(int32_t funct3, int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc)
{
    switch (funct3)
    {
        case LB:
            lb_op(offset, base, mem, rd, pc);
            return EXEC_OK;
        case LH:
            lh_op(offset, base, mem, rd, pc);
            return EXEC_OK;
        case LW:
            lw_op(offset, base, mem, rd, pc);
            return EXEC_OK;
        case LBU:
            lbu_op(offset, base, mem, rd, pc);
            return EXEC_OK;
        case LHU:
            lhu_op(offset, base, mem, rd, pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_store_op(int32_t funct3, int32_t offset, int32_t base, char* mem, int32_t val, int32_t* pc)
{
    switch (funct3)
    {
        case SB:
            sb_op(offset, base, mem, val, pc);
            return EXEC_OK;
        case SH:
            sh_op(offset, base, mem, val, pc);
            return EXEC_OK;
        case SW:
            sw_op(offset, base, mem, val, pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_B_type(int32_t inst, int32_t* x, char* mem, int32_t* pc)
{
    int funct3 = slice(inst, 12, 3);
    int imm    = b_imm(inst);
    int rs1    = slice(inst, 15, 5);
    int rs2    = slice(inst, 20, 5);
    return decode_branch_op(funct3, imm, x[rs1], x[rs2], pc);
}

int decode_R_type(int32_t inst, int32_t* x, char* mem, int32_t* pc)
{
    int funct3 = slice(inst, 12, 3);
    int funct7 = slice(inst, 25, 7);
    int rd     = slice(inst,  7, 5);
    int rs1    = slice(inst, 15, 5);
    int rs2    = slice(inst, 20, 5);


    if (funct3 == SUB && funct7 == 0x20)
        return decode_arithm_op(ADD,    funct7, x[rs1], -x[rs2], (x + rd), pc);
    else
        return decode_arithm_op(funct3, funct7, x[rs1],  x[rs2], (x + rd), pc);
}

int decode_I_type(int32_t inst, int32_t* x, char* mem, int32_t* pc)
{
    int opcode = slice(inst, 0, 7);
    int funct3 = slice(inst, 12,  3);
    int funct7 = slice(inst, 25, 7);
    int imm    = i_imm(inst);
    int rs1    = slice(inst, 15,  5);
    int rd     = slice(inst,  7,  5);

    switch (opcode)
    {
        case OP_IMM:
            return decode_arithm_op(funct3, funct7, x[rs1], imm, (x + rd), pc);
        case JALR:
            if (funct3 == 0) {
                jalr_op(imm, x[rs1], (x + rd), pc);
                return EXEC_OK;
            }
            else
                return EXEC_EXIT;
        case LOAD:
            return decode_load_op(funct3, imm, x[rs1], mem, (x + rd), pc);
        default:
            return EXEC_EXIT;
    }
}

int decode_S_type(int32_t inst, int32_t* x, char* mem, int32_t* pc)
{
    int funct3 = slice(inst, 12, 3);
    int imm    = s_imm(inst);
    int rs1    = slice(inst, 15, 5);
    int rs2    = slice(inst, 20, 5);

    return decode_store_op(funct3, imm, x[rs1], mem, x[rs2], pc);
}

int decode_J_type(int32_t inst, int32_t* x, char* mem, int32_t* pc)
{
    int rd = slice(inst, 7, 5);
    int imm = j_imm(inst);

    jal_op(imm, (x + rd), pc);

    return EXEC_OK;
}

int decode_U_type(int32_t inst, int32_t* x, char* mem, int32_t* pc)
{
    int opcode = slice(inst, 0, 7);
    int rd     = slice(inst, 7, 5);
    int imm    = u_imm(inst);
    switch (opcode)
    {
        case LUI:
            lui_op(imm, (x + rd), pc);
            return EXEC_OK;
        case AUIPC:
            auipc_op(imm, (x + rd), pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int load_linear_block(char* mem, int32_t* pc, )

int exec_command(int32_t* x, char* mem, int32_t* pc) {
    int32_t inst = *(int32_t*)(mem + *pc);
    int opcode = slice(inst, 0, 7);
    int ret_status;
    switch (opcode)
    {
        case OP:
            ret_status = decode_R_type(inst, x, mem, pc);
            break;
        case OP_IMM:
        case LOAD:
        case JALR:
            ret_status = decode_I_type(inst, x, mem, pc);
            break;
        case LUI:
        case AUIPC:
            ret_status = decode_U_type(inst, x, mem, pc);
            break;
        case BRANCH:
            ret_status = decode_B_type(inst, x, mem, pc);
            break;
        case JAL:
            ret_status = decode_J_type(inst, x, mem, pc);
            break;
        case STORE:
            ret_status = decode_S_type(inst, x, mem, pc);
            break;
        default:
            return EXEC_EXIT;

    }
    x[0] = 0;
    return ret_status;
}

