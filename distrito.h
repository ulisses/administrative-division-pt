#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "concelho.h"

typedef struct distrito {
        char *distrito;
        char *link;
        Concelho *concelhos;
        struct distrito *prox;
}Distrito;

Distrito *catDistritos(Distrito *lDist, Distrito *elem);
Distrito *addDistrito(char *distrito, char *link, Concelho *concelhos );
void geraHTML(Distrito *d);
