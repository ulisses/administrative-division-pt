#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freguesia.h"

typedef struct concelho {
        int idConcelho;
        int idDistrito;
        char *concelho;
        Freguesia *freguesias;
        struct concelho *prox;
}Concelho;

Concelho *lConcelho;

Concelho *addConcelho(Concelho *lista, Freguesia *lf, char *concelho, int idConcelho, int idDistrito);
char *getNomeConcelho(int cod);
void geraListaConcelhos(void);
char *getDistritoDoConcelho(int cod);
Concelho *getConcelhosDoDistrito(int cod);
