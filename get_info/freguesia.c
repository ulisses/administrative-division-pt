#include "freguesia.h"

Freguesia *addFreguesia(Freguesia *lista, char *freguesia, int idFreguesia, int idDistrito, int idConcelho) {
        if(lista == NULL) {
                lista = (Freguesia *) malloc(sizeof(Freguesia));

                lista->freguesia = strdup(freguesia);
                lista->idFreguesia = idFreguesia;
                lista->idDistrito = idDistrito;
                lista->idConcelho = idConcelho;
                lista->prox = NULL;

                return lista;
        }
        Freguesia *lista2 = (Freguesia *) malloc(sizeof(Freguesia));

        lista2->freguesia = strdup(freguesia);
        lista2->idFreguesia = idFreguesia;
        lista2->idDistrito = idDistrito;
        lista2->idConcelho = idConcelho;
        lista2->prox = lista;

        return lista2;
}

void geraListaFreguesias(void) {
        FILE *todos_cp = fopen("todos_cp.txt","r");

        char *idFreguesia = (char *) malloc(sizeof(char)*100);
        char *nomeFreguesia = (char *) malloc(sizeof(char)*100);
        char *idDistrito = (char *) malloc(sizeof(char)*100);
        char *idConcelho = (char *) malloc(sizeof(char)*100);

        while(fscanf(todos_cp,"%[^;];%[^;];%[^;];%[^;];%*[^\n]%*c",idDistrito, idConcelho, idFreguesia, nomeFreguesia) != EOF)
                if(!existe(atoi(idFreguesia), atoi(idConcelho), atoi(idDistrito)))
                        lFreguesias = addFreguesia(lFreguesias, strdup(nomeFreguesia), atoi(idFreguesia), atoi(idDistrito), atoi(idConcelho));

        fclose(todos_cp);
}

int existe(int idFreguesia, int idConcelho, int idDistrito) {
        int ret = 0;
        Freguesia *lf = lFreguesias;
        
        for( ; lf != NULL ; lf=lf->prox) {
                if(lf->idFreguesia == idFreguesia && lf->idConcelho == idConcelho && lf->idDistrito == idDistrito)
                        return 1;
        }
        return ret;
}

Freguesia *getFreguesiasDoDistritoEDoConcelho(int idDistrito,int idConcelho) {
        Freguesia *lista = NULL;
        Freguesia *l = lFreguesias;

        for( ; l != NULL ; l = l->prox)
                if(l->idDistrito == idDistrito && l->idConcelho == idConcelho)
                        lista = addFreguesia(lista,strdup(l->freguesia), l->idFreguesia,idDistrito, idConcelho);

        return lista;
}
