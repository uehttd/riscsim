//
// Created by ilya on 13.04.18.
//

#ifndef RISCSIM_INST_DECODE_H
#define RISCSIM_INST_DECODE_H

enum opcode_e {
    OP = 0x33,
    OP_IMM = 0x23
};

enum funct3_e {
    ADD  = 0x0,
    SUB  = 0x0,
    SLL  = 0x1,
    SLT  = 0x2,
    SLTU = 0x3,
    XOR  = 0x4,
    SRL  = 0x5,
    SRA  = 0x5,
    OR   = 0x6,
    AND  = 0x7
};

enum funct7_e {
    ZER  = 0x0
};

enum exec_command_status
{
    EXEC_OK,
    EXEC_EXIT
};

int exec_command(int32_t* x, int32_t* mem, int32_t* pc);

#endif //RISCSIM_INST_DECODE_H
