#include "distrito.h"

Distrito *addDistrito(char *distrito, char *link, Concelho *concelhos ) {
        Distrito *dist = (Distrito *) malloc(sizeof(Distrito));

        dist->distrito = strdup(distrito);
        dist->link = strdup(link);
        dist->concelhos = concelhos;

        return dist;
}

Distrito *catDistritos(Distrito *lDist, Distrito *elem) {
        elem->prox = lDist;
        return elem;
}

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

void geraHTML(Distrito *d) {
        int i, j, k;
        Concelho *c;
        Freguesia *f;
        Distrito *d1 = d;
        char *buffer, *conc;
        FILE *df = fopen("pages/distritos.html","w"), *cf, *ff;

        FILE *concHTML = fopen("pages/concelhos.html","w");
        fprintf(concHTML, strdup("<pre>Aqui vão aparecer os Concelhos</pre>"));
        fclose(concHTML);

        FILE *fregHTML = fopen("pages/freguesias.html","w");
        fprintf(concHTML, strdup("<pre>Aqui vão aparecer as Freguesias</pre>"));
        fclose(fregHTML);

        FILE *mainHTML = fopen("pages/main.html","w");
        fprintf(mainHTML, strdup("<pre>Aqui vai aparecer conteúdo da Wikipedia</pre>"));
        fclose(mainHTML);

        FILE *indexHTML = fopen("pages/index.html","w");
        fprintf(indexHTML,strdup("<html><head><title>OrGeo</title></head><frameset framespacing=\"1\" border=\"5\" cols=\"200,200,180,*\" frameborder=\"1\"><frame name=\"distritos\" src=\"distritos.html\"  scrolling=\"auto\" noresize><frame name=\"concelhos\" src=\"concelhos.html\"  scrolling=\"auto\" noresize><frame name=\"freguesias\" src=\"freguesias.html\"  scrolling=\"auto\" noresize><frame name=\"main\"       src=\"main.html\" scrolling=\"auto\" noresize target=\"_self\"></frameset></html>"));
        fclose(indexHTML);

        fprintf(df, "<h3>Distritos de Portugal</h3>\n");
        for(i=0; d1 != NULL; d1 = d1->prox) {
                buffer = (char *) malloc(sizeof(char)*(strlen(d1->distrito)*2+strlen(d1->link)+97+23));
                buffer = strcpy(buffer,strdup("<li><font size=\"-1\"><a target=\"main\" href=\""));
                buffer = strcat(buffer,d1->link);
                buffer = strcat(buffer, strdup("\">"));
//                 buffer = strcat(buffer, strdup("<font size=\"-1\">"));
                buffer = strcat(buffer,d1->distrito);
//                 buffer = strcat(buffer, strdup("</font>"));
                buffer = strcat(buffer, strdup("</a> <a target=\"concelhos\" href=\"c_"));
                buffer = strcat(buffer,d1->distrito);
                buffer = strcat(buffer,strdup(".html\">Concelhos</a></font></li>"));
                fprintf(df,"%s\n", buffer);
                free(buffer);
                conc = (char *) malloc(sizeof(char)*(14+strlen(d1->distrito)));
                conc = strcpy(conc, strdup("pages/"));
                conc = strcat(conc, "c_");
                conc = strcat(conc, d1->distrito);
                conc = strcat(conc, ".html");
                cf = fopen(conc,"w");
                free(conc);
                fprintf(cf, "<h3>Concelhos de %s</h3>\n", d1->distrito);
                for(j=0, c = d1->concelhos ; c != NULL ; c = c->prox) {
                        buffer = (char *) malloc(sizeof(char)*(strlen(c->concelho)*2+strlen(c->link)+98+23));
                        buffer = strcpy(buffer,strdup("<li><font size=\"-1\"><a target=\"main\" href=\""));
                        buffer = strcat(buffer,c->link);
                        buffer = strcat(buffer, strdup("\">"));
//                         buffer = strcat(buffer, strdup(""));
                        buffer = strcat(buffer,c->concelho);
//                         buffer = strcat(buffer, strdup("</font>"));
                        buffer = strcat(buffer, strdup("</a> <a target=\"freguesias\" href=\"f_"));
                        buffer = strcat(buffer,c->concelho);
                        buffer = strcat(buffer,strdup(".html\">Freguesias</a></font></li>"));
                        fprintf(cf,"%s\n", buffer);
                        free(buffer);

                        conc = (char *) malloc(sizeof(char)*(14+strlen(c->concelho)));
                        conc = strcpy(conc, strdup("pages/"));
                        conc = strcat(conc, "f_");
                        conc = strcat(conc, c->concelho);
                        conc = strcat(conc, ".html");
                        ff = fopen(conc,"w");
                        free(conc);
                        fprintf(ff, "<h3>Freguesias de %s</h3>\n", c->concelho);
                        for(k=0, f = c->freguesias ; f != NULL ; f = f->prox) {
                                buffer = (char *) malloc(sizeof(char)*(strlen(f->freguesia)+strlen(f->link)+34+23));
                                buffer = strcpy(buffer, strdup("<li><a target=\"main\" href=\""));
                                buffer = strcat(buffer, f->link);
                                buffer = strcat(buffer, strdup("\">"));
                                buffer = strcat(buffer, strdup("<font size=\"-1\">"));
                                buffer = strcat(buffer, f->freguesia);
                                buffer = strcat(buffer, strdup("</font>"));
                                buffer = strcat(buffer, strdup("</a>"));
                                fprintf(ff,"%s\n", buffer);
                                free(buffer);
                        }
                        fclose(ff);
                }
                fclose(cf);
        }
        fclose(df);

/*        for(i=0 ; d != NULL ; d = d->prox) {
                for(j=0, c = d->concelhos ; c != NULL ; c = c->prox) {
                
                        for(k=0, f = c->freguesias ; f != NULL ; f = f->prox) {
                                createHTML();
                        }
                }
        }*/

/*        for(i=0 ; d != NULL ; d= d->prox) {
                printf("%s>%s", d->distrito, d->link);
                for(j=0, c = d->concelhos ; c != NULL ; c = c->prox) {
                        for(k=0, f = c->freguesias ; f != NULL ; f = f->prox) {
                                        printf("\t%s>%s\n",f->freguesia, f->link);
                        }
                        printf("\t!%s>%s;\n", c->concelho, c->link);
                }
        }*/
}
