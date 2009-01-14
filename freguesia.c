#include "freguesia.h"

Freguesia *addFreguesia(char *freguesia, char *link) {
        Freguesia *freg = (Freguesia *) malloc(sizeof(Freguesia));

        freg->freguesia = strdup(freguesia);
        freg->link = strdup(link);
        freg->prox = NULL;

        return freg;
}

Freguesia *catFreguesias(Freguesia *lFreg, Freguesia *elem) {
        elem->prox = lFreg;
        return elem;
}
