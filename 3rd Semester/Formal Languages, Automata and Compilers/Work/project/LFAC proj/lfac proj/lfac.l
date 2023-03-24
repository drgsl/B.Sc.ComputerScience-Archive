%{
#include <stdio.h>
#include "y.tab.h"
%}
%option noyywrap
%%
"-" {return minus;}
"WHILE" {return WHILE;}
"IF" {return IF;}
"FOR" {return FOR;}
"character" {return character;}
"sir" {return sir;}
"BOOL" {return BOOL;}
"real" {return real;}
"nat" {return nat;}
"define" {return define;}
"vec" {return vec;}
"MAIN" {return MAIN;}
"ELSE" {return ELSE;}
"copy" {return copy;}
"compare" {return compare;}
"concat" {return concat;}
"function" {return function;}
"CLASS" {return CLASS;}
"evaluate" {return evaluate;}
"exec" {return exec;}
"and" { return AND;}
"or" { return OR;}
"print" {return PRINT;}

"<"|">"|"=="|">="|"<=" {return comparation;}

("false")|("true") { yylval.bolVal=strdup(yytext); return bol;}
[a-zA-Z][a-zA-Z0-9]* { yylval.nameVar=strdup(yytext); return identifier;}
-?([1-9][0-9]*|0) { yylval.natVal=atoi(yytext); return integer;}
-?([1-9][0-9]*|0)\.([0-9]*) { yylval.realVal=atof(yytext); return nrReal;}
\'[^ \']\' { yylval.charactVal=yytext[1]; return charact;}
\"[^ \"]*\" { yylval.sirVal=strdup(yytext); return s;}
"//"[^\n\r]* ;
[ \t\r] ;
\n {yylineno++;}
. {return yytext[0];}
