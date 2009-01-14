#include "distrito.h"

Distrito *addDistrito(Distrito *lista, Concelho *lc, char *distrito, int idDistrito) {
        if(lista == NULL) {
                lista = (Distrito *) malloc(sizeof(Distrito));

                lista->distrito = strdup(distrito);
                lista->idDistrito = idDistrito;
                lista->concelhos = lc;
                lista->prox = NULL;

                return lista;
        }
        Distrito *lista2 = (Distrito *) malloc(sizeof(Distrito));

        lista2->distrito = strdup(distrito);
        lista2->idDistrito = idDistrito;
        lista2->concelhos = lc;
        lista2->prox = lista;

        return lista2;
}

void geraListaDistritos(void) {
        FILE *distritos = fopen("distritos.txt","r");

        char *idDistrito = (char *) malloc(sizeof(char)*100);
        char *distrito = (char *) malloc(sizeof(char)*100);

        while (fscanf(distritos,"%[^;];%[^\n]%*c", idDistrito, distrito) != EOF) {
                Concelho *c = getConcelhosDoDistrito(atoi(idDistrito));
                lDistritos = addDistrito(lDistritos,c, strdup(distrito), atoi(idDistrito));
        }

        fclose(distritos);
}

char *getNomeDistrito(int cod) {
        Distrito *lista = lDistritos;

        for( ; lista != NULL ; lista = lista->prox) {
                if(lista->idDistrito == cod)
                        return strdup(lista->distrito);
        }
        return NULL;
}
