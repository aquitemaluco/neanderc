#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "nmem.h"
#include "nproc.h"
#include "nterm.h"

char nread_key()
{
	struct termios oldT, newT;
	char c;

	ioctl(0, TCGETS ,&oldT); /* get current mode */
	newT=oldT;
	newT.c_lflag &= ~ECHO;   /* echo off */
	newT.c_lflag &= ~ICANON; /* one char @ a time */
	ioctl(0, TCSETS ,&newT); /* set new terminal mode */
	c = '\0';
	do {
		read(0, &c, 1);      /* read 1 char @ a time from stdin */
	} while(c == '\0');
	ioctl(0, TCSETS, &oldT); /* restore previous terminal mode */

    return c;
}

void printnproc(PNPROC p)
{
    if(p->pc == 0) {
        printf("+--------------------------------------------------+\n");
        printf("+                  NEADER PROC                     +\n");
    }
	printf("+--------------------------------------------------+\n");
    printf("+    AC = %3d  RI = %3d  PC = %3d  N = %1d  Z = %1d    +\n",
			p->ac, p->ri, p->pc, p->s >> Z , p->s & ~N);
	printf("+--------------------------------------------------+\n");
}

void print_main_menu()
{
    printf("+======================================================+\n");
    printf("|               Bem-vindo ao Neader                    |\n");
    printf("+======================================================+\n");
    printf("|             1 - Executar um arquivo                  |\n");
    printf("|             2 - Modo interativo                      |\n");
    printf("|             3 - Executar programa teste              |\n");
    printf("|             9 - Sair                                 |\n");
    printf("+------------------------------------------------------+\n");

}

void print_exmode()
{
    printf("+======================================================+\n");
    printf("|                  Modo de execucao                    |\n");
    printf("+======================================================+\n");
    printf("|             1 - Execucao normal                      |\n");
    printf("|             2 - Execucao por passo                   |\n");
    printf("+------------------------------------------------------+\n");

}

void print_fmode()
{
    printf("+======================================================+\n");
    printf("|                  Arquivo de memoria                  |\n");
    printf("+======================================================+\n");
    printf("|    Insira o nome do arquivo de memoria com a         |\n");
    printf("|    extensao. \".mem\"                                  |\n");
    printf("+------------------------------------------------------+\n");

}

void print_memmap(PNMEM m)
{
    printf("  +===============================================================+\n");
    printf("  |                              MEM MAP                          |\n");
    printf("  +===============================================================+\n");
    printf("  |  0|  1|  2|  3|  4|  5|  6|  7|  8|  9|  A|  B|  C|  D|  E|  F|\n");
    printf("  +---------------------------------------------------------------+\n");
    printf(" 0|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 0), *(m->minadr + 1), *(m->minadr + 2), *(m->minadr + 3),
            *(m->minadr + 4), *(m->minadr + 5), *(m->minadr + 6), *(m->minadr + 7),
            *(m->minadr + 8), *(m->minadr + 9), *(m->minadr + 10), *(m->minadr + 11),
            *(m->minadr + 12), *(m->minadr + 13), *(m->minadr + 14), *(m->minadr + 15));
    printf(" 1|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 16), *(m->minadr + 17), *(m->minadr + 18), *(m->minadr + 19),
            *(m->minadr + 20), *(m->minadr + 21), *(m->minadr + 22), *(m->minadr + 23),
            *(m->minadr + 24), *(m->minadr + 25), *(m->minadr + 26), *(m->minadr + 27),
            *(m->minadr + 28), *(m->minadr + 29), *(m->minadr + 30), *(m->minadr + 31));
    printf(" 2|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 32), *(m->minadr + 33), *(m->minadr + 34), *(m->minadr + 35),
            *(m->minadr + 36), *(m->minadr + 37), *(m->minadr + 38), *(m->minadr + 39),
            *(m->minadr + 40), *(m->minadr + 41), *(m->minadr + 42), *(m->minadr + 43),
            *(m->minadr + 44), *(m->minadr + 45), *(m->minadr + 46), *(m->minadr + 47));
    printf(" 3|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 48), *(m->minadr + 49), *(m->minadr + 50), *(m->minadr + 51),
            *(m->minadr + 52), *(m->minadr + 53), *(m->minadr + 54), *(m->minadr + 55),
            *(m->minadr + 56), *(m->minadr + 57), *(m->minadr + 58), *(m->minadr + 59),
            *(m->minadr + 60), *(m->minadr + 61), *(m->minadr + 62), *(m->minadr + 63));
    printf(" 4|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 64), *(m->minadr + 65), *(m->minadr + 66), *(m->minadr + 67),
            *(m->minadr + 68), *(m->minadr + 69), *(m->minadr + 70), *(m->minadr + 71),
            *(m->minadr + 72), *(m->minadr + 73), *(m->minadr + 74), *(m->minadr + 75),
            *(m->minadr + 76), *(m->minadr + 77), *(m->minadr + 78), *(m->minadr + 79));
    printf(" 5|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 80), *(m->minadr + 81), *(m->minadr + 82), *(m->minadr + 83),
            *(m->minadr + 84), *(m->minadr + 85), *(m->minadr + 86), *(m->minadr + 87),
            *(m->minadr + 88), *(m->minadr + 89), *(m->minadr + 90), *(m->minadr + 91),
            *(m->minadr + 92), *(m->minadr + 93), *(m->minadr + 94), *(m->minadr + 95));
    printf(" 6|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 96), *(m->minadr + 97), *(m->minadr + 98), *(m->minadr + 99),
            *(m->minadr + 100), *(m->minadr + 101), *(m->minadr + 102), *(m->minadr + 103),
            *(m->minadr + 104), *(m->minadr + 105), *(m->minadr + 106), *(m->minadr + 107),
            *(m->minadr + 108), *(m->minadr + 109), *(m->minadr + 110), *(m->minadr + 111));
    printf(" 7|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 112), *(m->minadr + 113), *(m->minadr + 114), *(m->minadr + 115),
            *(m->minadr + 116), *(m->minadr + 117), *(m->minadr + 118), *(m->minadr + 119),
            *(m->minadr + 120), *(m->minadr + 121), *(m->minadr + 122), *(m->minadr + 123),
            *(m->minadr + 124), *(m->minadr + 125), *(m->minadr + 126), *(m->minadr + 127));
    printf(" 8|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 128), *(m->minadr + 129), *(m->minadr + 130), *(m->minadr + 131),
            *(m->minadr + 132), *(m->minadr + 133), *(m->minadr + 134), *(m->minadr + 135),
            *(m->minadr + 136), *(m->minadr + 137), *(m->minadr + 138), *(m->minadr + 139),
            *(m->minadr + 140), *(m->minadr + 141), *(m->minadr + 142), *(m->minadr + 143));
    printf(" 9|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 144), *(m->minadr + 145), *(m->minadr + 146), *(m->minadr + 147),
            *(m->minadr + 148), *(m->minadr + 149), *(m->minadr + 150), *(m->minadr + 151),
            *(m->minadr + 152), *(m->minadr + 153), *(m->minadr + 154), *(m->minadr + 155),
            *(m->minadr + 156), *(m->minadr + 157), *(m->minadr + 158), *(m->minadr + 159));
    printf(" A|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 160), *(m->minadr + 161), *(m->minadr + 162), *(m->minadr + 163),
            *(m->minadr + 164), *(m->minadr + 165), *(m->minadr + 166), *(m->minadr + 167),
            *(m->minadr + 168), *(m->minadr + 169), *(m->minadr + 170), *(m->minadr + 171),
            *(m->minadr + 172), *(m->minadr + 173), *(m->minadr + 174), *(m->minadr + 175));
    printf(" B|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 176), *(m->minadr + 177), *(m->minadr + 178), *(m->minadr + 179),
            *(m->minadr + 180), *(m->minadr + 181), *(m->minadr + 182), *(m->minadr + 183),
            *(m->minadr + 184), *(m->minadr + 185), *(m->minadr + 186), *(m->minadr + 187),
            *(m->minadr + 188), *(m->minadr + 189), *(m->minadr + 190), *(m->minadr + 191));
    printf(" C|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 192), *(m->minadr + 193), *(m->minadr + 194), *(m->minadr + 195),
            *(m->minadr + 196), *(m->minadr + 197), *(m->minadr + 198), *(m->minadr + 199),
            *(m->minadr + 200), *(m->minadr + 201), *(m->minadr + 202), *(m->minadr + 203),
            *(m->minadr + 204), *(m->minadr + 205), *(m->minadr + 206), *(m->minadr + 207));
    printf(" D|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 208), *(m->minadr + 209), *(m->minadr + 210), *(m->minadr + 211),
            *(m->minadr + 212), *(m->minadr + 213), *(m->minadr + 214), *(m->minadr + 215),
            *(m->minadr + 216), *(m->minadr + 217), *(m->minadr + 218), *(m->minadr + 219),
            *(m->minadr + 220), *(m->minadr + 221), *(m->minadr + 222), *(m->minadr + 223));
    printf(" E|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 224), *(m->minadr + 225), *(m->minadr + 226), *(m->minadr + 227),
            *(m->minadr + 228), *(m->minadr + 229), *(m->minadr + 230), *(m->minadr + 231),
            *(m->minadr + 232), *(m->minadr + 233), *(m->minadr + 234), *(m->minadr + 235),
            *(m->minadr + 236), *(m->minadr + 237), *(m->minadr + 238), *(m->minadr + 239));
    printf(" F|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|\n",
            *(m->minadr + 240), *(m->minadr + 241), *(m->minadr + 242), *(m->minadr + 243),
            *(m->minadr + 244), *(m->minadr + 245), *(m->minadr + 246), *(m->minadr + 247),
            *(m->minadr + 248), *(m->minadr + 249), *(m->minadr + 250), *(m->minadr + 251),
            *(m->minadr + 252), *(m->minadr + 253), *(m->minadr + 254), *(m->minadr + 255));
    printf("  +---------------------------------------------------------------+\n");

}
