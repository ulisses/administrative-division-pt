#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "distrito.h"

//cat wikipediaPT.xml | grep "<title>.*</title>" | sed '/.*[!"#$&:%;,=*+|0-9].*$/d' | sed -e '/[A-Z][A-Z].*/d' > titles.txt

typedef enum{Distrito_t, Concelho_t, Freguesia_t}Local;

int verbosev;

char *underscore(char *word) {
        char *ret = (char *) malloc(sizeof(char)*(strlen(word)+1));
        int i;

        for(i=0 ; word[i]!= '\0' ; i++) {
                if(word[i] == ' ')
                        ret[i] = '_';
                else
                        ret[i] = word[i];
        }
        ret[i] = '\0';

        return ret;
}

char *protege(char *link) {
        char *ret = (char *) malloc(sizeof(char)*(strlen(link)+3));
        int i, j;

        for(i=0, j=0 ; link[i]!= '\0' ; j++, i++) {
                if(link[i] == '(') {
                        ret[j] = '\\';
                        j++;
                        ret[j] = '(';
                }
                if(link[i] == ')') {
                        ret[j] = '\\';
                        j++;
                        ret[j] = ')';
                }
                else
                        ret[j] = link[i];
        }
        ret[j] = '\0';

        return ret;
}

int existePagina(char *nomeEntrada) {
        int res_s;

        // <title>nomeEntrada</title>
        char *nomeEntradaTitleBegin = strdup("<title>");
        char *nomeEntradaTitleEnd = strdup("</title>");
        char *nomeEntradaTitle = (char *) malloc(sizeof(char)*(strlen(nomeEntradaTitleBegin)+strlen(nomeEntradaTitleEnd)+strlen(nomeEntrada)+1));

        strcpy(nomeEntradaTitle, nomeEntradaTitleBegin);
        strcat(nomeEntradaTitle, nomeEntrada);
        strcat(nomeEntradaTitle, nomeEntradaTitleEnd);

        char *cat = strdup("cat titles.txt | grep -q \"");
        char *cmd = (char *) malloc(sizeof(char)*(strlen(nomeEntradaTitle)+strlen(cat)+2));

        cmd = strcpy(cmd, cat);
        cmd = strcat(cmd, nomeEntradaTitle);
        cmd = strcat (cmd, strdup("\""));

        res_s = system(cmd);
        if(res_s == 0) return 1;
        return 0;
}

char *padroesDistrito(char *entrada) {
        //Paterns
        char *wiki = strdup("http://pt.wikipedia.org/wiki/");
        char *dPattern1 = strdup("Distrito de ");

        char *dEntrada = (char *) malloc(sizeof(char)*(strlen(entrada)+strlen(dPattern1)+1));
        char *link = (char *) malloc(sizeof(char)*(strlen(dEntrada)+strlen(wiki)+1));
        char *dEntradaUnderscore;

        dEntrada = strcpy(dEntrada, dPattern1);
        dEntrada = strcat(dEntrada, entrada);

        dEntradaUnderscore = strdup(underscore(dEntrada));

        if(existePagina(dEntrada)) {
                if(verbosev == 1)
                        printf("II: Saving %s\n", dEntradaUnderscore);
                link = strcpy(link, wiki);
                link = strcat(link, dEntradaUnderscore);
        }
        else {
                link = strcpy(link, wiki);
                link = strcat(link, underscore(entrada));
                if(verbose == 1)
                        printf("EE: The entry %s does not exist, replacing by: %s\n", dEntradaUnderscore, link);
        }
        free(wiki);
        free(dPattern1);
        free(dEntrada);
        free(dEntradaUnderscore);
        return link;
}

char *padroesConcelho(char *entrada) {
        //Paterns
        char *wiki = strdup("http://pt.wikipedia.org/wiki/");
        char *dPattern1 = strdup(" (Portugal)");
        char *dEntrada = (char *) malloc(sizeof(char)*(strlen(entrada)+strlen(dPattern1)+1));
        char *link = (char *) malloc(sizeof(char)*(strlen(dEntrada)+strlen(wiki)+1));
        char *dEntradaUnderscore;

        dEntrada = strcpy(dEntrada, entrada);
        dEntrada = strcat(dEntrada, dPattern1);

        dEntradaUnderscore = strdup(underscore(dEntrada));

        if(existePagina(dEntrada)) {
                if(verbosev == 1)
                        printf("II: Saving %s\n", dEntradaUnderscore);
                link = strcpy(link, wiki);
                link = strcat(link, dEntradaUnderscore);
        }
        else {
                link = strcpy(link, wiki);
                link = strcat(link, underscore(entrada));
                if(verbose == 1)
                        printf("EE: The entry %s does not exist, replacing by: %s\n", dEntradaUnderscore, link);
        }
        free(wiki);
        free(dPattern1);
        free(dEntrada);
        free(dEntradaUnderscore);
        return link;
}

char *padroesFreguesia(char *entrada, char *concelho) {
        char *wiki = strdup("http://pt.wikipedia.org/wiki/");
        char *link = (char *) malloc(sizeof(char)*(strlen(wiki)+strlen(entrada)+1));
        //Patern 1
        char *cAbrirP1 = strdup(" (");
        char *cFecharP1 = strdup(")");
        char *cEntrada1 = (char *) malloc(sizeof(char)*(strlen(entrada)+strlen(concelho)+strlen(cFecharP1)+strlen(cAbrirP1)+1));
        char *link1 = (char *) malloc(sizeof(char)*(strlen(cEntrada1)+strlen(wiki)+1));
        char *cEntradaUnderscore1;

        cEntrada1 = strcpy(cEntrada1, entrada);
        cEntrada1 = strcat(cEntrada1, cAbrirP1);
        cEntrada1 = strcat(cEntrada1, concelho);
        cEntrada1 = strcat(cEntrada1, cFecharP1);
        cEntradaUnderscore1 = strdup(underscore(cEntrada1));
        //Patern 2
        char *cfreg = strdup(" (freguesia)");
        char *cEntrada2 = (char *) malloc(sizeof(char)*(strlen(entrada)+strlen(cfreg)+1));
        char *link2 = (char *) malloc(sizeof(char)*(strlen(cEntrada2)+strlen(wiki)+1));
        char *cEntradaUnderscore2;

        cEntrada2 = strcpy(cEntrada2, entrada);
        cEntrada2 = strcat(cEntrada2, cfreg);
        cEntradaUnderscore2 = strdup(underscore(cEntrada2));
        //Patern 3
        char *cEntrada3 = entrada;

        if(existePagina(cEntrada1)) {
                if(verbosev == 1)
                        printf("II: Saving %s\n", cEntradaUnderscore1);
                link1 = strcpy(link1, wiki);
                link1 = strcat(link1, cEntradaUnderscore1);
                link = link1;
        }
        else if(existePagina(cEntrada2)) {
                if(verbosev == 1)
                        printf("II: Saving %s\n", cEntradaUnderscore2);
                link2 = strcpy(link2, wiki);
                link2 = strcat(link2, cEntradaUnderscore2);
                link = link2;
        }
        else if(existePagina(cEntrada3)) {
                if(verbosev == 1)
                        printf("II: Saving %s\n", underscore(cEntrada3));
                link = strcpy(link, wiki);
                link = strcat(link, underscore(entrada));
        }
        else {
                link = strcpy(link, wiki);
                link = strcat(link, underscore(entrada));
                if(verbose == 1)
                        printf("EE: The entry %s and %s does not exist, replacing by: %s\n", cEntradaUnderscore1, cEntradaUnderscore2, link);
        }
/*        free(wiki);
        free(cAbrirP1);
        free(cFecharP1);
        free(cEntrada1);
        free(cEntradaUnderscore1);
        free(cfreg);
        free(cEntrada2);
        free(cEntradaUnderscore2);*/
        return link;
}

char *wikipedia(char *entrada, char *concelho, Local l) {
        switch(l) {
                case Distrito_t :
                        return padroesDistrito(entrada);
                case Concelho_t :
                        return padroesConcelho(entrada);
                case Freguesia_t :
                        return padroesFreguesia(entrada, concelho);
        }
        return NULL; //nunca acontece
}

/*
idD>link
        idL1>link,
        idL2>link,
        idL3>link
        !idC1>link;
        idL1>link,
        idL2>link,
        idL3>link
        !idC2>link|
*/
void nonRep() {
        FILE *fp = fopen("bd.txt","w");
        Concelho *c = NULL;
        Freguesia *f = NULL;
        int i, j, k;

        for(i=0 ; lDistritos != NULL ; lDistritos = lDistritos->prox) {
                fputs("\n",fp);
                fprintf(fp, "%s>%s", lDistritos->distrito, wikipedia(strdup(lDistritos->distrito), NULL, Distrito_t));
                for(j=0, c = lDistritos->concelhos ; c != NULL ; c = c->prox) {
                        for(k=0, f = c->freguesias ; f != NULL ; f = f->prox) {
                                if(f->prox==NULL)
                                        fprintf(fp, "\t%s>%s\n",f->freguesia, wikipedia(strdup(f->freguesia), strdup(c->concelho), Freguesia_t));
                                else
                                        fprintf(fp, "\t%s>%s,\n",f->freguesia, wikipedia(strdup(f->freguesia), strdup(c->concelho), Freguesia_t));
                        }
                        if(c->prox==NULL)
                                fprintf(fp, "\t!%s>%s|\n", c->concelho, wikipedia(strdup(c->concelho), NULL, Concelho_t));
                        else
                                fprintf(fp, "\t!%s>%s;\n", c->concelho, wikipedia(strdup(c->concelho), NULL, Concelho_t));
                }
        }
        fclose(fp);
}

int main() {
        lDistritos = NULL;
        lConcelho = NULL;
        lFreguesias = NULL;
        verbose=1;
        verbosev = 1;

        geraListaFreguesias();
        geraListaConcelhos();
        geraListaDistritos();
        puts("READY!");
        nonRep();

//         int pid;
//         int i;
//         char buf[999];
//         int status;
// 
//         for (i = 1; i <= 9999; i++) {
//                 pid = fork();
// 
//                 if(pid == 0) {
//                         puts("sou o filho");
//                         padroesConcelho(strdup("Porto"));
//                         exit(1);
//                 }
//                 else {
//                         puts("a");
//                         int c = wait(&status);
//                         if(WIFEXITED(status))
//                                 printf("esperei pelo filho: %d\n", c);
//                 }
//         }

//         printf("w=%s\n",wikipedia(strdup("Li_s_t"),Distrito_t));

/*        char *nf = strdup("Viseu");
        char *notPage = strdup("Viseu");
        int tam_buffer=100;
        char *buffer, *cp = NULL;
        FILE *f = fopen("concelhos.txt","r");

        cp = (char *) malloc(sizeof(char)*(tam_buffer+1));
        buffer  = (char *) malloc(sizeof(char)*(tam_buffer+1));
        buffer = fgets(buffer, tam_buffer, f);

        while(buffer != NULL) {
                strcpy(cp,buffer);
                cp = strstr(cp, notPage);
                if(strstr(buffer, notPage) != NULL) { //se a entrada na Wikipedia nao existir
                        puts("-----------------------------");
                        fclose(f);
                        removeFile(nf);
                        return 0; //false
                }
                ////free(buffer);
                ////free(cp);
                cp = (char *) malloc(sizeof(char)*(tam_buffer+1));
                buffer  = (char *) malloc(sizeof(char)*(tam_buffer+1));
                buffer = fgets(buffer, tam_buffer, f);
        }
        fclose(f);*/
//         int err=0;
//         FILE *f = fopen("Distrito_de_Braga","r");
//         err = errno; //possivel erro do fopen
//         printf("errno=%d\n",err);
//         if(!err)
//                 fclose(f);


//             int i;
//             char *c = malloc(sizeof(char)*10);
//             char *link;
// 
//            for( i = 3000; i < 3999; i++) {
//                 link = malloc(sizeof(char)*99);
// 
//                 sprintf(link, "%s%s",strdup("http://pt.wikipedia.org/wiki/"), strdup(itoa(i)));
//                 printf("%s;%s\n",link,strdup(itoa(i)));
//                 existePagina(link, strdup(itoa(i)));
//                 ////free(link);
//            }

//         char *buffer;
//         int i;
// 
//         for(i = 0; i < 999 ; i++) {
//                 buffer = (char *) malloc(sizeof(char)*5000);
//                 strcat(buffer,strdup("louras"));
//                 printf("%s\n",buffer);
//                 ////free(buffer);
//         }

// 
//         FILE *f = fopen("Distrito_de_Beja","r");
// 
//         while(fscanf(f, "%[^\n]", buffer) != EOF) {
//                 fscanf(f, "\n%*c");
//                 printf("%s\n",buffer);
//         }
//         fclose(f);

//         printf("%s\n",wikipedia(strdup("o l aasd fasd fasd fasd fasdf")));
//         printf("%s\n",wikipedia(strdup("o l aasd fasd fasd fasd fasdf")));
//         printf("%s\n",wikipedia(strdup("o l aasd fasd fasd fasd fasdf")));
//         printf("%s\n",wikipedia(strdup("o l aasd fasd fasd fasd fasdf")));
//         printf("%s\n",wikipedia(strdup("o l aasd fasd fasd fasd fasdf")));
//         printf("%s\n",wikipedia(strdup("o l aasd fasd fasd fasd fasdf")));


        return 0;
}
