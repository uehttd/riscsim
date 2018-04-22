#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "inst_decode.h"
#include "load_elf.h"

int32_t x[32]; //32 general-purpose intteger registers
char mem[134217728]; //code memory model. TODO:this may require change accroding to the spec
int32_t pc; //program counter


int main(int argc, char** argv)
{
    for(int i = 0; i < 32; i++)
        x[i] = 0;

    x[2] = 134217720; //init stack pointer

    if (load_code(argc, argv) != EXIT_SUCCESS)
        return EXIT_FAILURE;
    while (1)
    {
        int op_status = exec_command(x, mem,  &pc);
        if (op_status == EXEC_EXIT)
            break;
    }

    printf("program returned: %d\n", x[10]);
    return 0;
}


//defines test
//int main(int argc, char** argv) {
//    int32_t test1var = 0xDEADBEEF;
//    assert(slice(test1var,  0, 4) == 0xF);
//    assert(slice(test1var,  4, 4) == 0xE);
//    assert(slice(test1var,  8, 4) == 0xE);
//    assert(slice(test1var, 12, 4) == 0xB);
//    assert(slice(test1var, 16, 4) == 0xD);
//    assert(slice(test1var, 20, 4) == 0xA);
//    assert(slice(test1var, 24, 4) == 0xE);
//    assert(slice(test1var, 28, 4) == 0xD);
//
//    int32_t test2var = 0xFFF00000;
//    int32_t test3var = 0x7FF00000;
//    int32_t test4var = 0xFFFF1234;
//    int32_t test5var = 0x12300000;
//
//    assert(i_imm(test2var) == 0xFFFFFFFF);
//    assert(i_imm(test3var) == 0x000007FF);
//    assert(i_imm(test4var) == 0xFFFFFFFF);
//    assert(i_imm(test5var) == 0x00000123);
//    return 0;
//}

