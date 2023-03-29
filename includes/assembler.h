#ifndef ASSEMBLER_H
#define ASSEMBLER_H

typedef struct CONTROL {
    char regdist;
    char branch;
    char memread;
    char memtoreg;
    char aluop;
    char memwrite;
    char alusrc;
    char regwrite;
    char jump;
} Control;

typedef struct INSTRUCTION {
    char type;
    char *mnemonic;
    int rs;
    int rt;
    int rd;
    int imm;
    int PC;
    Control *cu;
} Instruction;

Instruction *Decode(char *);
Instruction **DecodeAllIns(char *, int);
Control *FormControl(char *);
void Run(char *, int, int *, int *);

#endif