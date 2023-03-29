#include "includes/assembler.h"
#include "includes/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Control *FormControl(char *mne) {
    Control *cu = (Control *) malloc(sizeof(Control));
    if (!strcmp(mne, "add") || !strcmp(mne, "sub") || !strcmp(mne, "slt")
    || !strcmp(mne, "or") || !strcmp(mne, "nand")) {
        cu->regdist = 1;
        cu->alusrc = 0;
        cu->memtoreg = 0;
        cu->regwrite = 1;
        cu->memread = 0;
        cu->memwrite = 0;
        cu->branch = 0;
        cu->jump = 0;
        if (!strcmp(mne, "add"))
            cu->aluop = 2;
        else if (!strcmp(mne, "sub"))
            cu->aluop = 6;
        else if (!strcmp(mne, "slt"))
            cu->aluop = 7;
        else if (!strcmp(mne, "or"))
            cu->aluop = 1;
        else if (!strcmp(mne, "nand"))
            cu->aluop = 4;
        return cu;
    }

    if (!strcmp(mne, "addi") || !strcmp(mne, "ori") || !strcmp(mne, "slti")
    || !strcmp(mne, "lui")) {
        cu->regdist = 0;
        cu->branch = 0;
        cu->jump = 0;
        cu->memread = 0;
        cu->memtoreg = 0;
        cu->memwrite = 0;
        cu->alusrc = 1;
        cu->regwrite = 1;
        if (!strcmp(mne, "addi"))
            cu->aluop = 2;
        else if (!strcmp(mne, "ori"))
            cu->aluop = 1;
        else if (!strcmp(mne, "slti"))
            cu->aluop = 7;
        else if (!strcmp(mne, "lui"))
            cu->aluop = 2;
        return cu;
    }

    if (!strcmp(mne, "lw")) {
        cu->regdist = 0;
        cu->branch = 0;
        cu->jump = 0;
        cu->memread = 1;
        cu->memtoreg = 1;
        cu->memwrite = 0;
        cu->alusrc = 1;
        cu->regwrite = 1;
        cu->aluop = 2;
        return cu;
    }

    if (!strcmp(mne, "sw")) {
        cu->regdist = 'x';
        cu->branch = 0;
        cu->jump = 0;
        cu->memread = 0;
        cu->memtoreg = 'x';
        cu->memwrite = 1;
        cu->alusrc = 1;
        cu->regwrite = 0;
        cu->aluop = 2;
        return cu;
    }

    if (!strcmp(mne, "beq")) {
        cu->regdist = 'x';
        cu->branch = 1;
        cu->jump = 0;
        cu->memread = 0;
        cu->memtoreg = 'x';
        cu->memwrite = 0;
        cu->alusrc = 0;
        cu->regwrite = 0;
        cu->aluop = 6;
        return cu;
    }

    if (!strcmp(mne, "jalr")) {
        cu->regdist = 0;
        cu->branch = 0;
        cu->jump = 1;
        cu->memread = 0;
        cu->memtoreg = 0;
        cu->memwrite = 0;
        cu->alusrc = 'x';
        cu->regwrite = 1;
        cu->aluop = 'x';
        return cu;
    }

    if (!strcmp(mne, "j")) {
        cu->regdist = 'x';
        cu->branch = 0;
        cu->jump = 1;
        cu->memread = 0;
        cu->memtoreg = 0;
        cu->memwrite = 0;
        cu->alusrc = 'x';
        cu->regwrite = 0;
        cu->aluop = 'x';
        return 0;
    }

    if (!strcmp(mne, "halt")) {
        cu->regdist = 'x';
        cu->branch = 0;
        cu->jump = 0;
        cu->memread = 0;
        cu->memtoreg = 0;
        cu->memwrite = 0;
        cu->alusrc = 'x';
        cu->regwrite = 0;
        cu->aluop = 'x';
        return cu;
    }

}

Instruction *Decode(char *binstr) {
    static int PC = 0;
    Instruction *ins = (Instruction *) malloc(sizeof(Instruction));
    memset(ins, 0, sizeof(Instruction));

    if (strlen(binstr) <= 6) {
        int imm = 0;
        if (*binstr == '-')
            imm = atoi(binstr + 1) * -1;
        else
            imm = atoi(binstr);
        ins->mnemonic = "value";
        ins->imm = imm;
        ins->PC = -1;
        return ins;
    }
    
    char opcode[5] = {0}, rs[5] = {0}, 
    rt[5] = {0}, rd[5] = {0}, imm[17] = {0};
    memcpy(opcode, binstr + 4, 4);

    if (!strcmp(opcode, "0000")) {
        ins->mnemonic = "add";
        ins->type = 'R';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(rd, binstr + 16, 4);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->rd = bintoint(rd);
        ins->cu = FormControl("add");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "0001")) {
        ins->mnemonic = "sub";
        ins->type = 'R';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(rd, binstr + 16, 4);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->rd = bintoint(rd);
        ins->cu = FormControl("sub");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "0010")) {
        ins->mnemonic = "slt";
        ins->type = 'R';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(rd, binstr + 16, 4);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->rd = bintoint(rd);
        ins->cu = FormControl("slt");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "0011")) {
        ins->mnemonic = "or";
        ins->type = 'R';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(rd, binstr + 16, 4);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->rd = bintoint(rd);
        ins->cu = FormControl("or");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "0100")) {
        ins->mnemonic = "nand";
        ins->type = 'R';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(rd, binstr + 16, 4);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->rd = bintoint(rd);
        ins->cu = FormControl("nand");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "0101")) {
        ins->mnemonic = "addi";
        ins->type = 'I';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(imm, binstr + 16, 16);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("addi");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "0110")) {
        ins->mnemonic = "slti";
        ins->type = 'I';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(imm, binstr + 16, 16);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("slti");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "0111")) {
        ins->mnemonic = "ori";
        ins->type = 'I';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(imm, binstr + 16, 16);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("ori");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "1000")) {
        ins->mnemonic = "lui";
        ins->type = 'I';
        memcpy(rt, binstr + 12, 4);
        memcpy(imm, binstr + 16, 16);
        ins->rs = 0;
        ins->rt = bintoint(rt);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("lui");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "1001")) {
        ins->mnemonic = "lw";
        ins->type = 'I';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(imm, binstr + 16, 16);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("lw");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "1010")) {
        ins->mnemonic = "sw";
        ins->type = 'I';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(imm, binstr + 16, 16);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("sw");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "1011")) {
        ins->mnemonic = "beq";
        ins->type = 'I';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        memcpy(imm, binstr + 16, 16);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("beq");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "1100")) {
        ins->mnemonic = "jalr";
        ins->type = 'I';
        memcpy(rs, binstr + 8, 4);
        memcpy(rt, binstr + 12, 4);
        ins->rs = bintoint(rs);
        ins->rt = bintoint(rt);
        ins->imm = 0;
        ins->cu = FormControl("jalr");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "1101")) {
        ins->mnemonic = "j";
        ins->type = 'J';
        memcpy(imm, binstr + 16, 16);
        ins->imm = bintoint(imm);
        ins->cu = FormControl("j");
        ins->PC = PC++;
    } else if (!strcmp(opcode, "1110")) {
        ins->mnemonic = "halt";
        ins->type = 'J';
        ins->cu = FormControl("halt");
        ins->PC = PC++;
    } else {
        printf("This instruction is not valid\n");
        return NULL;
    }
    
    return ins;
}

Instruction **DecodeAllIns(char *arr, int sz) {
    Instruction **insList = (Instruction **) calloc(sz, sizeof(Instruction*));
    for (int i = 0; i < sz; i++)
            insList[i] = Decode(arr + (i * 40));
    return insList;
}

void Run(char *arr, int sz, int *regs, int *mem) {
    Instruction *ins;
    int PC = 0;
    while (1) {
        ins = Decode(arr + (PC * 40));
        printf("Running PC = %d\n", PC);
        PrintInsFromBin(ins);
        if (ins->type == 'R') {
            if (!strcmp(ins->mnemonic, "add"))
                regs[ins->rd] = regs[ins->rs] + regs[ins->rt];
            else if (!strcmp(ins->mnemonic, "sub"))
                regs[ins->rd] = regs[ins->rs] - regs[ins->rt];
            else if (!strcmp(ins->mnemonic, "slt"))
                regs[ins->rd] = regs[ins->rs] < regs[ins->rt] ? 1 : 0;
            else if (!strcmp(ins->mnemonic, "or"))
                regs[ins->rd] = regs[ins->rs] | regs[ins->rt];
            else if (!strcmp(ins->mnemonic, "nand"))
                regs[ins->rd] = ~(regs[ins->rs] & regs[ins->rt]);
            GetStatus(regs, mem, -1);
            printf("Press the ENTER key to execute the next instruction ...\n");
            getchar();
            PC++;
            continue;
        } else if (ins->type == 'I') {

            if (!strcmp(ins->mnemonic, "beq")) {
                PC = regs[ins->rt] == regs[ins->rs] ? PC + 1 + ins->imm : PC + 1;
                printf("Press the ENTER key to execute the next instruction ...\n");
                getchar();
                continue;
            } else if (!strcmp(ins->mnemonic, "jalr")) {
                regs[ins->rt] = PC + 1;
                PC = ins->rs;
                printf("Press the ENTER key to execute the next instruction ...\n");
                getchar();
                continue;
            }

            if (!strcmp(ins->mnemonic, "addi"))
                regs[ins->rt] = regs[ins->rs] + ins->imm;
            else if (!strcmp(ins->mnemonic, "slti"))
                regs[ins->rt] = regs[ins->rs] < ins->imm ? 1 : 0;
            else if (!strcmp(ins->mnemonic, "ori"))
                regs[ins->rt] = regs[ins->rs] | ins->imm;
            else if (!strcmp(ins->mnemonic, "lui"))
                regs[ins->rt] = ins->imm << 16;
            else if (!strcmp(ins->mnemonic, "lw"))
                regs[ins->rt] = mem[regs[ins->rs] + ins->imm] <= 65535 ? mem[regs[ins->rs] + ins->imm] : 0;
            else if (!strcmp(ins->mnemonic, "sw")) {
                mem[regs[ins->rs] + ins->imm] = regs[ins->rt];
                GetStatus(regs, mem, regs[ins->rs] + ins->imm);
                printf("Press the ENTER key to execute the next instruction ...\n");
                getchar();
                PC++;
                continue;
            }
            
            GetStatus(regs, mem, -1);
            printf("Press the ENTER key to execute the next instruction ...\n");
            getchar();
            PC++;
            continue;
        } else if (ins->type == 'J') {
            if (!strcmp(ins->mnemonic, "j")) {
                PC = ins->imm;
                printf("Press the ENTER key to execute the next instruction ...\n");
                getchar();
                continue;
            } else if (!strcmp(ins->mnemonic, "halt")) {
                printf("Press the ENTER key to execute the next instruction ...\n");
                getchar();
                printf("Runned successfully ...!");
                exit(0);
            }
        }
    }
}

