%{
#include <stdio.h>
#include <string.h>
#include "distrito.h"

Distrito *d;
%}

%union {
        char *vals;
        Freguesia *valf;
        Concelho *valc;
        Distrito *vald;
}

%token  <vals>id l
%type   <vals>Link IdL IdD IdC
%type   <valf>Local Locais
%type   <valc>Concelho Concelhos
%type   <vald>Distrito Distritos
%%
OrGeo     : Distritos { d = $1; }
          ;
Distritos : Distrito '|' { $$ = $1; }
          | Distritos Distrito '|' { $$ = catDistritos($1,$2); }
          ;
Distrito  : IdD Link Concelhos { $$ = addDistrito($1, $2, $3); }
          ;
Concelhos : Concelho { $$ = $1; }
          | Concelhos ';' Concelho { $$ = catConcelhos($1, $3); }
          ;
Concelho  : Locais '!' IdC Link { $$ = addConcelho($1, $3, $4); }
          ;
Locais    : Local { $$ = $1; }
          | Locais ',' Local { $$ = catFreguesias($1, $3); }
          ;
Link      : '>' l { $$ = $2; }
          ;
IdD       : id { $$ = $1; }
          ;
IdC       : id { $$ = $1; }
          ;
Local     : IdL Link { $$ = addFreguesia($1, $2); }
          ;
IdL       : id { $$ = $1; }
          ;
%%

void yyerror(char *s) {
        fprintf(stderr, "ERRO: %s\n",s);
}

int main() {
        yyparse();
        geraHTML(d);

        return 0;
}
