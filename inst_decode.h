//
// Created by ilya on 13.04.18.
//

#ifndef RISCSIM_INST_DECODE_H
#define RISCSIM_INST_DECODE_H

#include "rv32i_op.h"

enum opcode_e {
    OP = 0x33,
    OP_IMM = 0x23
};

enum funct3_e {
    ADD = 0x00
};

enum funct7_e {

};

int exec_command(int32_t* x, int32_t* mem, int32_t* pc) {
    int32_t inst = mem[*pc];
    int opcode = inst & 0x7F; //TODO: maybe move to decode function
    if (opcode == OP) {
        int funct3 = (inst >> 12) & 0x7; //TODO: move these slices to defines
        int funct7 = (inst >> 25) & 0x7F;//TODO: or function for each type of command (RISBUJ)
        if (funct3 == ADD && funct7 == 0) {
            int rs1 = (inst >> 15) & 0x1F;
            int rs2 = (inst >> 20) & 0x1F;
            add_op(x[rs1], x[rs2], pc);
        }
    }
}

#endif //RISCSIM_INST_DECODE_H
