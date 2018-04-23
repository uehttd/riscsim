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
    FILE *fptr;
    fptr = fopen("../log.txt", "rb+");

    if(fptr == NULL) //if file does not exist, create it
    {
        fptr = fopen("../log.txt", "wb");
    }

    fprintf(fptr,"***************BEGIN***************\n");
    fprintf(fptr," opcode         rd             pc\n");

    for(int i = 0; i < 32; i++)
        x[i] = 0;

    x[2] = 134217720; //init stack pointer

    if (load_code(argc, argv) != EXIT_SUCCESS)
        return EXIT_FAILURE;
    while (1)
    {
        int op_status = exec_command(x, mem,  &pc, fptr);
        if (op_status == EXEC_EXIT)
            break;
    }

    printf("program returned: %d\n", x[10]);


    fclose(fptr);

    return 0;
}