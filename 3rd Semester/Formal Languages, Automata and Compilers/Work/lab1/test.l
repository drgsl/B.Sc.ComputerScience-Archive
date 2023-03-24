%{
    #include <stdio.h>
%}

digit [0-9]
digitNon0 [1-9]
natural 0|{digitNon0}{digit}*
floatingPoint {natural}\.{digit}+
id [a-zA-Z][a-zA-Z0-9]*
reserved for|while|if|else
type int|float|char

%x comment

%option noyywrap
%%
{natural} {printf("%s\tnatural\n", yytext);}
{floatingPoint} {printf("%s\tfloat\n", yytext);}
- {printf("%s\tminus op\n", yytext);}
\+ {printf("%s\tplus op\n", yytext);}
[+][+] {printf("%s\tincrement op\n", yytext);}
{reserved} {printf("%s\treserved\n", yytext);}
{type} {printf("%s\ttype\n", yytext);}
{id} {printf("%s\tidentifier\n", yytext);}

"/*" {printf("Start of comment ... "); BEGIN(comment);}
<comment>"*/" {printf(" end of comment"); BEGIN(0);}
<comment>.|\n ;


.|\n ;
%%

int main(int argc, char** argv){
    FILE *g;
    if(argc>0)
        yyin = fopen(argv[1],"r");

    /*if(!(g = fopen("out.txt","w")))
        fprintf(stderr,"eroare creare fisier!");
    else
        yyout=g;*/

    yylex();
}
