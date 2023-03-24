%{
#include <stdio.h>
#include "y.tab.h"
%}

%option noyywrap
%%

[ \t] ;
\n {yylineno++;}

"const int"|"const float"|"const char"|"const string"|"const bool"|"const double"|"const void"|"int"|"float"|"char"|"string"|"bool"|"double"|"void" {yylval.strval = strdup(yytext); return TYPE;}

"for" {return FOR;}
"while" {return WHILE;}
"if" {return IF;}
"else" {return ELSE;} 

"struct" {return STRUCT;}

"Print" {return PRINT;}

"main()" { return MAIN; }

"##" { return DELIM; }

">=" {return GE;}
"<=" {return LE;}
"==" {return EQ;}
"!=" {return NE;}

"&&" {return AND;}
"||" {return OR;}

\".*\" { yylval.strval = strdup(yytext); return TEXT; }
[0-9]+ { yylval.intval = atoi(yytext); return NR;}
[_a-zA-Z][_a-zA-Z0-9]* { yylval.strval = strdup(yytext); return ID;}

\/\/.* ;
\/\*(.*\n)*.*\*\/ ;

. {return yytext[0];}
