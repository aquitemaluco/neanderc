#include <stdio.h>
#include <stdlib.h>

#include "nmem.h"
#include "nproc.h"
#include "nterm.h"
#include "nprog.h"

void nprogram(PNMEM m);
void normal_run(PNPROC p);
void step_run(PNPROC p);

int main()
{
    //Aloca recurso para memoria
    PNMEM m = getnmem();
    //Aloca recurso para o processador
    PNPROC p = getnproc();

    initneander(p, m);

    char c;
    char emod;
    char arquivo[256];
    for(;;) {
        print_main_menu();
        c = nread_key();
        switch(c) {
            case '1':
                print_fmode();
                printf("> ");
                scanf("%s", arquivo);
                loadnfprog(m, arquivo);
                print_memmap(m);
                print_exmode();
                emod = nread_key();
                if(emod == '1') {
                    run(p);
                }
                else {
                    step_run(p);
                }
                print_memmap(m);
                printf("\n\n\nDigite uma tecla para continuar...\n");
                nread_key();
            break;
            case '2':
                internprog(m);
                print_memmap(m);
                print_exmode();
                emod = nread_key();
                if(emod == '1') {
                    run(p);
                }
                else {
                    step_run(p);
                }
                print_memmap(m);
                printf("\n\n\nDigite uma tecla para continuar...\n");
                nread_key();
            break;
            case '3':
                nprogram(m);
                print_memmap(m);
                print_exmode();
                emod = nread_key();
                if(emod == '1') {
                    run(p);
                }
                else {
                    step_run(p);
                }
                print_memmap(m);
                printf("\n\n\nDigite uma tecla para continuar...\n");
                nread_key();
            break;
            case '9':
                releasenmem(m);
                resetnproc(p);
                printf("\n\n\nBye Neander user! :)\n\n");
                return 0;
            break;
        }
    }


    return 0;
}

void normal_run(PNPROC p)
{
    if(run(p) == 0) {
		printf("Programa executado com sucesso!\n");
	}
	else {
		printf("Final inesperado!!!\n");
	}
}

void step_run(PNPROC p)
{
	//Laco principal
	for(;;) {
        if(nstep(p) == 0) {
            printf("Programa executado com sucesso!\n");
            return (void) 0;
        }

        printf("Digite 1 para continuar\n");
        nread_key();
	}
}

void nprogram(PNMEM m)
{
    //Pequeno programa para teste

    //Instrucoes de programa
    // Teste de LDA/ADD/STA
    (*(m->minadr + 0) = NOP);
    (*(m->minadr + 1) = LDA);
    (*(m->minadr + 2) = 128);
    (*(m->minadr + 3) = ADD);
    (*(m->minadr + 4) = 129);
    (*(m->minadr + 5) = STA);
    (*(m->minadr + 6) = 130);
    // Teste condicao Z
    (*(m->minadr + 7) = LDA);
    (*(m->minadr + 8) = 131);
    (*(m->minadr + 9) = JZ);
    (*(m->minadr + 10) = 100); //Desvia para 100
    // Teste JMP
    (*(m->minadr + 11) = NOP); //Retorno
    (*(m->minadr + 12) = JMP);
    (*(m->minadr + 13) = 110); //Desvia para 110
    // Teste OR/AND
    (*(m->minadr + 14) = LDA); //Retorno
    (*(m->minadr + 15) = 133);
    (*(m->minadr + 16) = OR); // 1 | 2 = 3
    (*(m->minadr + 17) = 134);
    (*(m->minadr + 18) = AND);
    (*(m->minadr + 19) = 133); // 3 & 1 = 1
    (*(m->minadr + 20) = HLT); //Retorno
    // Teste de condicao N
    (*(m->minadr + 100) = LDA);
    (*(m->minadr + 101) = 132);
    (*(m->minadr + 102) = JN);
    (*(m->minadr + 103) = 11);//Desvia para 11
    (*(m->minadr + 104) = HLT);
    //
    (*(m->minadr + 110) = NOT);
    (*(m->minadr + 111) = JMP);
    (*(m->minadr + 112) = 14);

    //Dados
    (*(m->minadr + 128) = 1);
    (*(m->minadr + 129) = 2);
    //Negativo
    (*(m->minadr + 131) = 0);
    //Zero
    (*(m->minadr + 132) = -1);
    //
    (*(m->minadr + 133) = 1);
    (*(m->minadr + 134) = 2);
}
