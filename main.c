#include <stdio.h>
#include <stdlib.h>
#include "includes\utils.h"
#include "includes\assembler.h"

int main(int argc, char *argv[])
{
    FILE *ins = fopen(argv[1], "r");
    int sz = countlines(ins);
    int regs[16] = {0};
    int mem[65535] = {0};
    LoadInsMemory(ins, mem, sz);
    // for (int i = 0; mem[i] != 0; i++)
    //     printf("%d -> %d |", i, mem[i]);
    // printf("\n");
    char *insarry = fillchararray(ins);
    // printchararray(insarry, sz, 0);
    Instruction **list = DecodeAllIns(insarry, sz);
    // for (int i = 0; i < sz; i++)
    //     printf("PC: %d, mne: %s, rs: %d, rt: %d, rd: %d, imm: %d\n",
    //     list[i]->PC, list[i]->mnemonic, list[i]->rs, list[i]->rt,
    //     list[i]->rd, list[i]->imm);
    Run(insarry, sz, regs, mem);
    return 0;
}