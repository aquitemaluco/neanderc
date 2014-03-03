#include <stdio.h>
#include <stdlib.h>

#include "nmem.h"
#include "nproc.h"
#include "nterm.h"

PNPROC getnproc()
{
    PNPROC p = (PNPROC) malloc(sizeof(NPROC));
    if(!p) {
		fprintf (stderr, "Nao foi possivel inicializar o NPROC\n");
        exit(1);
    }
    p->pc = 0;
    p->ac = 0;
    p->ri = 0;
    p->rm = NULL;
    p->s = 0;
    return p;
}


void initneander(PNPROC p, PNMEM m)
{
	if((p == NULL) || (m == NULL)) {
		fprintf (stderr, "init_mem: Proc ou Mem nulo!\n");
        exit(1);
	}

	for(p->rm = m->minadr; p->rm < m->minadr; p->rm++) {
		*(p->rm) = 0;
	}

	p->rm = m->minadr;
}

void resetnproc(PNPROC p)
{
	p->pc = 0;
    p->ac = 0;
    p->ri = 0;
    p->s = 0;
}

int nstep (PNPROC p)
{
	if(p == NULL) {
		fprintf (stderr, "run: NPROC nao inicializado\n");
        exit(1);
	}

	if(p->rm == NULL) {
		fprintf (stderr, "run: NMEM corrompida\n");
        exit(1);
	}

    //Busca instrucao
    p->ri = *(p->rm + p->pc);
    printnproc(p);
    //Incrementa PC
    p->pc++;

    //Decodifica instrucao
    switch (p->ri) {
        //NOP 0000
        case NOP:
            nfnop(p);
        break;
        //STA 0001
        case STA:
            nfsta(p);
        break;
        //LDA 0010
        case LDA:
            nflda(p);
        break;
        //ADD 0011
        case ADD:
            nfadd(p);
        break;
        //OR 0100
        case OR:
            nfor(p);
        break;
        //AND 0101
        case AND:
            nfand(p);
        break;
        //NOT 0110
        case NOT:
            nfnot(p);
        break;
        //JMP 1000
        case JMP:
            nfjmp(p);
        break;
        //JN 1001
        case JN:
            nfjn(p);
        break;
        //JZ 1010
        case JZ:
            nfjz(p);
        break;
        //HLT 1111
        case HLT:
            nfhlt(p);
            return 0;
        break;
        default:
            fprintf (stderr, "run: instrucao nao reconhecida! # %d #\n", p->ri);
            exit(1);
        break;

    }

    //Proximo passo.
    return 1;
}

int run(PNPROC p)
{
	//Laco principal
	for(;;) {
        if(nstep(p) == 0) {
            //Execucao com sucesso!
            return 0;
        }
	}
}

//Microcode
void nfstatus(PNPROC p)
{
	//Atualiza registrador de nfstatus
	p->s = CLSTATUS;
	((p->ac == 0) && (p->s = (p->s | Z))) ||
	((p->ac <  0) && (p->s = (p->s | N)));
}
void nfnop(PNPROC p) {
	//Perde um ciclo de maquina
}

void nfsta(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	*(p->rm + p->ri) = p->ac;
	printnproc(p);
	p->pc++;
}

void nflda(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	p->ac = *(p->rm + p->ri);
	nfstatus(p);
	printnproc(p);
	p->pc++;
}

void nfadd(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	p->ac = p->ac + *(p->rm + p->ri);
	nfstatus(p);
	printnproc(p);
	p->pc++;
}

void nfor(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	p->ac = p->ac | *(p->rm + p->ri);
	printnproc(p);
	p->pc++;
}

void nfand(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	p->ac = p->ac & *(p->rm + p->ri );
	nfstatus(p);
	printnproc(p);
	p->pc++;
}

void nfnot(PNPROC p)
{
	p->ac = (~p->ac)+1;
	nfstatus(p);
}

void nfjmp(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	printnproc(p);
	p->pc = p->ri;
}

void nfjn(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	printnproc(p);
	if (p->s == N) {
		p->pc = p->ri;
	}
	else {
		p->pc++;
	}
}

void nfjz(PNPROC p)
{
	p->ri = *(p->rm + p->pc);
	printnproc(p);
	if (p->s == Z) {
		p->pc = p->ri;
	}
	else {
		p->pc++;
	}
}

void nfhlt(PNPROC p)
{
	resetnproc(p);
	printnproc(p);
}
