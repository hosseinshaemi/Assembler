#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "assembler.h"

int countlines(FILE *);
char *fillchararray(FILE *);
void printchararray(char *, int, int);
char *inttobinary32(char *);
int bintoint(char *);
void GetStatus(int *, int *, int);
void LoadInsMemory(FILE *, int *, int);
void PrintInsFromBin(Instruction *);

#endif