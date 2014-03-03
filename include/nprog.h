#ifndef NPROG_H
#define NPROG_H 1

void clean_buf(char buf[4]);
void loadnfprog(PNMEM m, char * file);
void internprog(PNMEM m);
int parseinst(char *inst);

#endif
