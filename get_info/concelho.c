#include "concelho.h"

Concelho *addConcelho(Concelho *lista, Freguesia *lf, char *concelho, int idConcelho, int idDistrito) {
        if(lista == NULL) {
                lista = (Concelho *) malloc(sizeof(Concelho));

                lista->concelho = strdup(concelho);
                lista->idConcelho = idConcelho;
                lista->idDistrito = idDistrito;
                lista->freguesias = lf;
                lista->prox = NULL;

                return lista;
        }
        Concelho *lista2 = (Concelho *) malloc(sizeof(Concelho));

        lista2->concelho = strdup(concelho);
        lista2->idConcelho = idConcelho;
        lista2->idDistrito = idDistrito;
        lista2->freguesias = lf;
        lista2->prox = lista;

        return lista2;
}

void geraListaConcelhos(void) {
        FILE *concelhos = fopen("concelhos.txt","r");

        char *idConcelho = (char *) malloc(sizeof(char)*100);
        char *conc = (char *) malloc(sizeof(char)*100);
        char *idDistrito = (char *) malloc(sizeof(char)*100);

        while (fscanf(concelhos,"%[^;];%[^;];%[^\n]%*c", idDistrito, idConcelho, conc) != EOF) {
                Freguesia *lf = getFreguesiasDoDistritoEDoConcelho(atoi(idDistrito),atoi(idConcelho));
                lConcelho = addConcelho(lConcelho, lf, strdup(conc), atoi(idConcelho), atoi(idDistrito));
        }

        fclose(concelhos);
}

char *getNomeConcelho(int cod) {
        Concelho *lista = lConcelho;

        for( ; lista != NULL ; lista = lista->prox) {
                if(lista->idConcelho == cod)
                        return strdup(lista->concelho);
        }
        return NULL;
}

Concelho *getConcelhosDoDistrito(int cod) {
        Concelho *lista = NULL;
        Concelho *l = lConcelho;

        for( ; l != NULL ; l = l->prox)
                if(l->idDistrito == cod) {
                        Freguesia *lf = getFreguesiasDoDistritoEDoConcelho(l->idDistrito, l->idConcelho);
                        lista = addConcelho(lista,lf, strdup(l->concelho),l->idConcelho,cod);
                }

        return lista;
}
