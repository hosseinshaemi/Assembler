#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "includes/utils.h"

int countlines(FILE *fp)
{
    int lines = 0;
    int c;
    int last = '\n';
    while (EOF != (c = fgetc(fp)))
    {
        if (c == '\n' && last != '\n')
            ++lines;
        last = c;
    }
    rewind(fp);
    return lines;
}

char *fillchararray(FILE *fp) {
    int sz = countlines(fp);
    char *conv;
    char *array = (char *) calloc(sz, 40);
    char chunk[100];

    int i = 0;
    while (fgets(chunk, 100, fp) != NULL) {
        chunk[strcspn(chunk, "\n")] = 0;
        if (chunk[0] == '\0') continue;
        conv = inttobinary32(chunk);
        strcpy(array + i * 40, conv);
        i++;
    }
    rewind(fp);
    return array;
}

void printchararray(char *arr, int sz, int kind) {
    if (kind == 0)
        for (int i = 0; i < sz; i++)
            printf("%s\n", arr + i * 40);
    else
        for (int i = 0; i < sz * 40; i++)
            printf("%d ", *(arr + i));
}

char *inttobinary32(char *str) {
    int number;
    if (*str == '-')
        number = atoi(str + 1) * -1;
    else
        number = atoi(str);
    
    if (number < 65535)
        return str;
    
    int i = 0;
    char *binary = (char *) calloc(1, 40);
    binary[i] = '0' + (number < 0);
    i++;
    for (long bit = 1L << (CHAR_BIT * sizeof number - 2); bit; bit >>= 1) {
        binary[i] = '0' + !!(number & bit);
        i++;
    }
    binary[i] = '\0';
    return binary;
}

int bintoint(char *str) {
    return (int) strtol(str, NULL, 2);
}

void GetStatus(int *regs, int *mem, int memindex) {
    for (int i = 0; i < 16; i++)
        printf("[R%d]: %d | ", i, regs[i]);
    printf("\n");
    if (memindex != -1)
        printf("mem[%d]: %d\n", memindex, mem[memindex]);
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
}

void LoadInsMemory(FILE *fp, int *mem, int sz) {
    char chunk[100];

    int i = 0;
    while (fgets(chunk, 100, fp) != NULL) {
        chunk[strcspn(chunk, "\n")] = 0;
        if (chunk[0] == '\0') continue;
        if (chunk[0] == '-')
            mem[i] = atoi(&chunk[1]) * -1;
        else
            mem[i] = atoi(chunk);
        i++;
    }
    i++;
    mem[i] = 0;
    rewind(fp);
}

void PrintInsFromBin(Instruction *ins) {
    printf("ins: ");
    if (ins->type == 'R') {
        printf("%s %d, %d, %d\n", ins->mnemonic, ins->rd, ins->rs, ins->rt);
    } else if (ins->type == 'I') {
        if (!strcmp(ins->mnemonic, "lui")) {
            printf("%s %d, %d\n", ins->mnemonic, ins->rt, ins->imm);
            return;
        }
        if (!strcmp(ins->mnemonic, "jalr")) {
            printf("%s %d, %d\n", ins->mnemonic, ins->rt, ins->rs);
            return;
        }
        printf("%s %d, %d, %d\n", ins->mnemonic, ins->rt, ins->rs, ins->imm);
    } else if (ins->type == 'J') {
        if (!strcmp(ins->mnemonic, "j")) {
            printf("%s %d\n", ins->mnemonic, ins->imm);
            return;
        }
        if (!strcmp(ins->mnemonic, "halt")) {
            printf("%s\n", ins->mnemonic);
            return;
        }
    }
}
