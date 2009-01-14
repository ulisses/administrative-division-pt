#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct freguesia {
        int idFreguesia;
        int idDistrito;
        int idConcelho;
        char *freguesia;
        struct freguesia *prox;
}Freguesia;

int verbose ;
Freguesia *lFreguesias;

Freguesia *addFreguesia(Freguesia *lista, char *freguesia, int idFreguesia, int idDistrito, int idConcelho);
void geraListaFreguesias(void);
Freguesia *getFreguesiasDoDistritoEDoConcelho(int idDistrito,int idConcelho);
int existe(int idFreguesia, int idConcelho, int idDistrito);
