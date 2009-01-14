#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct freguesia {
        char *freguesia;
        char *link;
        struct freguesia *prox;
}Freguesia;

Freguesia *addFreguesia(char *freguesia, char *link);
Freguesia *catFreguesias(Freguesia *lFreg, Freguesia *elem);
