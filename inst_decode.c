//
// Created by ilya on 14.04.18.
//

#include <stdint.h>

#include "inst_decode.h"
#include "rv32i_op.h"


#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))
#define i_imm(inst) (slice(inst, 20, 1) \
                | (((slice(inst, 31, 1) << 21) - slice(inst, 31, 1)) << 11))

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

int decode_R_type(int32_t inst, int32_t* x, int32_t* mem, int32_t* pc) {
    int funct3 = slice(inst, 12, 3);
    int funct7 = slice(inst, 25, 7);
    int rd     = slice(inst,  7, 5);
    int rs1    = slice(inst, 15, 5);
    int rs2    = slice(inst, 20, 5);
//    if (funct3 == ADD && funct7 == 0) {
//        add_op(x[rs1], x[rs2], (x + rd), pc);
//        return EXEC_OK;
//    }
    //TODO
}

int decode_I_type(int32_t inst, int32_t* x, int32_t* mem, int32_t* pc) {
    int funct3 = slice(inst, 12,  3);
    int imm    = i_imm(inst);
    int rs1    = slice(inst, 15,  5);
    int rd     = slice(inst,  7,  5);

    //TODO
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

