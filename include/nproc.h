#ifndef NPROC_H
#define NPROC_H 1

// Conjuto de instrucoes
#define NOP		0
#define STA		1
#define LDA		2
#define ADD		3
#define OR		4
#define AND		5
#define NOT		6
#define JMP		8
#define JN		9
#define JZ		10
#define HLT		15

// Condicao do registrador de nfstatus
#define Z 1
#define N 2
#define CLSTATUS 0

// Estrutura do NPROC Neander Processador
typedef struct s_nproc NPROC;
struct s_nproc {
	unsigned char pc;  // Program counter
    unsigned char ac;  // Acumulador
    unsigned char ri;  // Reg instrucao
    unsigned char *rm; // Reg memoria
    unsigned char s;   // nfstatus. 1 = n, 2 = z
};

typedef NPROC *PNPROC;

//Manipulacao do processador
PNPROC getnproc();
void initneander(PNPROC p, PNMEM m);
void resetnproc(PNPROC p);

//Fucoes para execucao
int nstep (PNPROC p);
int run(PNPROC p);

//Microcode
void nfstatus(PNPROC p);
void nfnop();
void nfsta(PNPROC p);
void nflda(PNPROC p);
void nfadd(PNPROC p);
void nfor(PNPROC p);
void nfand(PNPROC p);
void nfnot(PNPROC p);
void nfjmp(PNPROC p);
void nfjn(PNPROC p);
void nfjz(PNPROC p);
void nfhlt(PNPROC p);

#endif
