%{
#include "distrito.h"
#include "y.tab.h"
%}

%%
[ a-zA-ZÀ-ú\-\'\.\(\)\/\'\`0-9]+  { yylval.vals = strdup(yytext); return id; }
[a-zA-ZÀ-ú\-\'\.\(\)\/\'\`0-9_:]+ { yylval.vals = strdup(yytext); return l; }
[!>,;|]                           { return yytext[0]; }
[\t\n]                            { ; }
%%

int yywrap() {
        return 1;
}
