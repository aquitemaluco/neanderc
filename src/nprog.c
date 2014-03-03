#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nmem.h"
#include "nproc.h"
#include "nterm.h"
#include "nprog.h"

void clean_buf(char buf[4])
{
	buf[0] = '\0';
	buf[1] = '\0';
	buf[2] = '\0';
	buf[3] = '\0';
}

// Carrega um arquivo de programa do neander para a memoria
void loadnfprog(PNMEM m, char *file)
{
	FILE *h;

	h = fopen(file, "r");
	if (h == NULL) {
		fprintf (stderr, "Erro ao abrir o arquivo de programa.");
		exit(1);
	}

	int i = 0;
	int ch;
	int is_ins = 0;
	int addr, ins;
	char adr_buf[4], ins_buf[4];
	while ((ch = getc(h)) != -1) {
		// 32 = (sp) space
		if(ch == 32) {
			//Flag de controle
			is_ins = 1;
			i = 0;
			continue;
		}
		// 10 = (nl) new line
		else if(ch == 10) {
			//Converte em int
			addr = atoi(adr_buf);
			ins = atoi(ins_buf);
            if(ins > 255)
            {
                fprintf (stderr, "MEM overflow\n");
                exit(1);
            }
             printf("addr: %d - inst: %d\n", addr, ins);
			//Armazena na memoria
			if(addr == 0) {
				(*(m->minadr + addr) = ins);
			}
			else {
				(*(m->minadr + addr) = ins);
			}
			//Limpa o buffer
			clean_buf(adr_buf);
			clean_buf(ins_buf);
			//Flag de controle
			is_ins = 0;
			i = 0;
			continue;
		}

		if(is_ins == 1) {
			ins_buf[i] = ch;
		}
		else{
			adr_buf[i] = ch;
		}
		i++;
	}

	fclose(h);
}

void internprog(PNMEM m)
{
    int addr, inst;
    char strinst[4];
    printf("+======================================================+\n");
    printf("|                  Modo interativo                     |\n");
    printf("| Entre com a programacao use letra maiuscula:         |\n");
    printf("|      addr: endereco de memoria  ex: 0-255            |\n");
    printf("|      inst: instrucao / dado     ex: NOP, STA         |\n");
    printf("|                                                      |\n");
    printf("| Modo interativo encerra quando entrar inst: HLT      |\n");
    printf("+------------------------------------------------------+\n");
    for(;;) {
        printf("\n");
        printf("addr: ");
        scanf("%d", &addr);
        printf("inst: ");
        scanf("%s", strinst);

        printf("addr: %d - inst: %s", addr, strinst);
        inst = parseinst(strinst);
        if(inst > 255)
        {
            fprintf (stderr, "MEM overflow\n");
            exit(1);
        }
        (*(m->minadr + addr) = inst);

        if(inst == HLT) break;
    }

    printf("\n");
}

int parseinst(char *inst)
{
    int ins = 0;
    if(strcmp(inst, "NOP") == 0) return NOP;
    if(strcmp(inst, "STA") == 0) return STA;
    if(strcmp(inst, "LDA") == 0) return LDA;
    if(strcmp(inst, "ADD") == 0) return ADD;
    if(strcmp(inst, "OR" ) == 0) return OR;
    if(strcmp(inst, "AND") == 0) return AND;
    if(strcmp(inst, "NOT") == 0) return NOT;
    if(strcmp(inst, "JMP") == 0) return JMP;
    if(strcmp(inst, "JN" ) == 0) return JN;
    if(strcmp(inst, "JZ" ) == 0) return JZ;
    if(strcmp(inst, "HLT") == 0) return HLT;
    //
    ins = atoi(inst);
    if((ins > -1) || (ins < 256) ) return ins;

    return HLT;
}
