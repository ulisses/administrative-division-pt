#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freguesia.h"

typedef struct concelho {
        char *concelho;
        char *link;
        Freguesia *freguesias;
        struct concelho *prox;
}Concelho;

Concelho *addConcelho(Freguesia *freguesias, char *concelho, char *link);
Concelho *catConcelhos(Concelho *lConc, Concelho *elem);
