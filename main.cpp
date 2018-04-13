#include <iostream>

#include "inst_decode.h"

int32_t x[32]; //32 general-purpose intteger registers
int32_t mem[16000]; //code memory model. TODO:this may require change accroding to the spec
int32_t pc; //program counter

void load_code(char* filename);
int  exec_command(int32_t* x, int32_t* mem, int32_t* pc);

enum command_exec_status
{
    EXEC_OK,
    EXEC_EXIT
};

int main(int argc, char** argv) {
    load_code(argv[1]);
    while (1) {
        int op_status = exec_command(int32_t* x, int32_t* mem,  int32_t* pc);
        if (op_status == EXEC_EXIT)
            break;
    }
    return 0;
}

