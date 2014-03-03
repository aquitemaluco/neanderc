#include <stdlib.h>
#include <stdio.h>

#include "nmem.h"

PNMEM getnmem()
{
    PNMEM m = (PNMEM) malloc(sizeof(NMEM));
    if(!m) {
		fprintf (stderr, "Nao foi possivel criar o mapa de memoria!");
		exit(1);
    }
    m->minadr = m->d;
    m->maxadr = m->minadr + MEM_SIZE;
    return m;
}

void releasenmem(PNMEM m)
{
	m->minadr = NULL;
	m->maxadr = NULL;
	int i;
	for (i=0; i<MEM_SIZE; i++) {
		m->d[i] = 0;
	}
}
