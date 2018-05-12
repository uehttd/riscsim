#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "inst_decode.h"
#include "load_elf.h"


int32_t x[32]; //32 general-purpose intteger registers
#define N_mem 134217728
char mem[N_mem]; //code memory model. TODO:this may require change accroding to the spec
int32_t pc; //program counter
uint32_t inst_cnt;
#define N_cache 1024
linear_block lb_cache[N_cache];

FILE *f_log;

int main(int argc, char** argv)
{
    f_log = fopen("log.txt", "w");

    //fprintf(f_log,"  pc\t\t    inst\trd\tname\t*rd\n");

    for(int i = 0; i < 32; i++)
        x[i] = 0;

    x[2] = N_mem - 8; //init stack pointer

    if (load_code(argc, argv) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    int cache_wr_num = 0;
    while (1)
    {
        int i;
        if ((i = find_linear_block(pc, lb_cache, N_cache)) == -1)
        {
            int n_inst = get_linear_block_size(mem, &pc);
            clear_linear_block(&lb_cache[cache_wr_num]);
            load_decode_linear_block(mem, pc, &lb_cache[cache_wr_num], n_inst, x);
            i = cache_wr_num;
            cache_wr_num = (cache_wr_num + 1) % N_cache;
        }
        int lb_status = exec_linear_block(mem,  &pc, &lb_cache[i], f_log);
        if (lb_status == EXEC_EXIT)
            break;
    }

    printf("program returned: %d\n", x[10]);
    printf("instructions done: %u\n", inst_cnt);
    fclose(f_log);

    return 0;
}