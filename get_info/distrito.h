#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "concelho.h"

typedef struct distrito {
        int idDistrito;
        char *distrito;
        Concelho *concelhos;
        struct distrito *prox;
}Distrito;

Distrito *lDistritos;

Distrito *addDistrito(Distrito *lista, Concelho *lc, char *distrito, int idDistrito);
char *getNomeDistrito(int cod);
void geraListaDistritos(void);
char *padroesDistrito(char *entrada);
