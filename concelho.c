#include "concelho.h"

Concelho *addConcelho(Freguesia *freguesias, char *concelho, char *link) {
        Concelho *conc = (Concelho *) malloc(sizeof(Concelho));

        conc->concelho = strdup(concelho);
        conc->link = strdup(link);
        conc->freguesias = freguesias;

        return conc;
}

Concelho *catConcelhos(Concelho *lConc, Concelho *elem) {
        elem->prox = lConc;
        return elem;
}
