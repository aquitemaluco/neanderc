#ifndef NMEM_H
#define NMEM_H 1

#define MEM_SIZE 256

// Estrutura NMEM Neander Memoria
typedef struct s_nmem NMEM;
struct s_nmem {
    unsigned char d[MEM_SIZE]; //Data
    //Controle
    unsigned char *minadr;
    unsigned char *maxadr;
};

typedef NMEM *PNMEM ;

PNMEM getnmem();
void releasenmem(PNMEM m);

#endif
