%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE* yyin;
extern char* yytext;
extern int yylineno;
int yylex();
int yyerror();

FILE *fp;
FILE *fp2;

int sectiune = 1;

int ok = 1;
int nr_variabile = 0;
int start_type = 0;
int start_scope = 0;

int executa = 1;

int nr_functii = 0; 
char arg2[20][20];
int arg_nr;

typedef struct node
{
     struct node *left;
     struct node *right;
     char nume[20];
     int type;
} node;

enum enum_type {
     OP, IDENTIFIER, NUMBER, ARRAY_ELEM, OTHER
};

node* buildAST (char nume[20], struct node *expr1, struct node *expr2, int tip)
{
     node *new = (node *) malloc(sizeof(node));

     strcpy(new->nume, nume);
     
     new->type = tip;
     new->left = expr1;
     new->right = expr2;

     return new;
}

struct structura_variabile{
     char type[15];
     char nume[20];
     char scope[20];
     char valoare[100];
}variabile[100];

struct structura_functii{
     char type[10];
     char nume[20];
     int nr_arg;
     char argumente[20][20];
}functii[100];

int cautare_variabila(char nume[20])
{
     for(int i=0; i<nr_variabile; i++)
     {
          if(strcmp(variabile[i].nume, nume) == 0)
               return i;
     }
     return -1;
}

int cautare_functie(char nume[20], char argumente[20][20])
{
     int match = 1;
     for(int i=0; i<nr_functii; i++)
     {
          match = 1;
          for(int j=0;j<=functii[i].nr_arg; j++)
          {
               if(strcmp(argumente[j], functii[i].argumente[j]) != 0)
                    match = 0;
          }
          if(strcmp(functii[i].nume, nume) == 0 && match == 1)
               return i;
     }
     return -1;
}

char *strrev(char *str){
    char c, *front, *back;

    if(!str || !*str)
        return str;
    for(front=str,back=str+strlen(str)-1;front < back;front++,back--){
        c=*front;*front=*back;*back=c;
    }
    return str;
}

void int_to_array(int n, char aux[10])
{
     int minus = 0;
     if(n < 0)
     {
          minus = 1;
          n = -n;
     }
     int k = 0;
     while(n != 0)
     {
          aux[k] = (n % 10) + '0';
          k++;
          n = n / 10;
     }
     if(minus == 1)
     {
          aux[k] = '-';
          k++;
     }
     aux[k] = '\0';
     strrev(aux);
}

void printtree(node *tree)
{
     int i;
     if (tree->left || tree->right)
          printf("(");
     printf(" %s ", tree->nume);
     if (tree->left)
          printtree(tree->left);
     if (tree->right)
          printtree(tree->right);
     if (tree->left || tree->right)
          printf(")");
}

int evalAST(node *root)
{
     if(root->type == NUMBER)
          return atoi(root->nume);
     else if(root->type == OP)
     {
          if(strcmp(root->nume, "+") == 0)
               return evalAST(root->left) + evalAST(root->right);
          if(strcmp(root->nume, "-") == 0)
               return evalAST(root->left) - evalAST(root->right);
          if(strcmp(root->nume, "*") == 0)
               return evalAST(root->left) * evalAST(root->right);
          if(strcmp(root->nume, "/") == 0)
               return evalAST(root->left) / evalAST(root->right);
          if(strcmp(root->nume, ">") == 0)
               return evalAST(root->left) > evalAST(root->right);
          if(strcmp(root->nume, ">=") == 0)
               return evalAST(root->left) >= evalAST(root->right);
          if(strcmp(root->nume, "<") == 0)
               return evalAST(root->left) < evalAST(root->right);
          if(strcmp(root->nume, "<=") == 0)
               return evalAST(root->left) <= evalAST(root->right);
          if(strcmp(root->nume, "==") == 0)
               return evalAST(root->left) == evalAST(root->right);
          if(strcmp(root->nume, "!=") == 0)
               return evalAST(root->left) != evalAST(root->right);
          if(strcmp(root->nume, "&&") == 0)
               return evalAST(root->left) && evalAST(root->right);
          if(strcmp(root->nume, "||") == 0)
               return evalAST(root->left) || evalAST(root->right);
     }
     else if(root->type == IDENTIFIER)
     {
          int i = cautare_variabila(root->nume);
          return atoi(variabile[i].valoare);
     }
     else if(root->type == ARRAY_ELEM)
     {
          return 0;
     }
     else if(root->type == OTHER)
     {
          return 0;
     }
}

void freeNode(node *p) 
{
     int i;
     if (!p) return;
     free(p->left);
     free(p->right);
     free(p);
}

%}

%union {
int intval;
char* strval;
struct node *nodeval;
}

%token <strval>TYPE
%token <strval>ID 
%token <intval>NR
%token <strval>TEXT
%token PRINT
%token FOR 
%token WHILE 
%token IF 
%token ELSE
%token STRUCT
%token MAIN
%token DELIM

%type <nodeval>assignment 
%type <nodeval>expr

%left AND OR
%left '<' '>' GE LE EQ NE 

%right '='
%left '+' '-'
%left '*' '/'

%%

start: decVar delim decFunctions delim main { if(ok == 1) printf("Program corect sintactic\n"); else printf("Programul nu este corect sintactic\n"); }
     ;

delim: DELIM { sectiune++; }
     ;

decVar: decVar declarationGlobal
      | 
      ;

decFunctions: decFunctions function
            | decFunctions structDec ';' 
            | 
            ;

declarationGlobal: TYPE dec ';' { char *s = strdup($1); for(int i=start_type; i<nr_variabile; i++) { strcpy(variabile[i].type, s); strcpy(variabile[i].scope, "global"); } start_type = nr_variabile; start_scope = nr_variabile; }
                 | TYPE array ';' 
                 ;

declaration: TYPE dec ';' { char *s = strdup($1); for(int i=start_type; i<nr_variabile; i++) { strcpy(variabile[i].type, s); if(sectiune == 3) strcpy(variabile[i].scope, "main"); }  start_type = nr_variabile;  }
           | TYPE array ';' 
           ;

main: MAIN '{' lines '}' 

dec: ID ',' dec                 { char *s = strdup($1); if(cautare_variabila(s) != -1) { printf("eroare: variabila deja definita; linia: %d\n", yylineno); ok = 0; } else { strcpy(variabile[nr_variabile].nume, s); nr_variabile++; } }
   | ID '=' assignment ',' dec  { char *s = strdup($1); char s1[20]; int_to_array(evalAST($3), s1); freeNode($3); if(cautare_variabila(s) != -1) { printf("eroare: variabila deja definita; linia: %d\n", yylineno); ok = 0; } else { strcpy(variabile[nr_variabile].nume, s); strcpy(variabile[nr_variabile].valoare, s1); nr_variabile++; } }
   | ID                         { char *s = strdup($1); if(cautare_variabila(s) != -1) { printf("eroare: variabila deja definita; linia: %d\n", yylineno); ok = 0; } else { strcpy(variabile[nr_variabile].nume, s); nr_variabile++; } }
   | ID '=' assignment          { char *s = strdup($1); char s1[20]; int_to_array(evalAST($3), s1); freeNode($3); if(cautare_variabila(s) != -1) { printf("eroare: variabila deja definita; linia: %d\n", yylineno); ok = 0; } else { strcpy(variabile[nr_variabile].nume, s); strcpy(variabile[nr_variabile].valoare, s1); nr_variabile++; } }
   ;

assignment: ID { char *s = strdup($1); int i = cautare_variabila(s); if(i == -1) { printf("eroare: variabila %s nu este definita; linia: %d\n", s, yylineno); ok = 0; } if(strcmp(variabile[i].type, "string" ) == 0 || strcmp(variabile[i].type, "void") == 0) { printf("eroare: variabila %s are tip diferit; linia: %d\n", s, yylineno); ok = 0; } $<nodeval>$ = buildAST(s, NULL, NULL, IDENTIFIER); }
          | NR { char s[20]; int nr = yylval.intval; int_to_array(nr, s); $<nodeval>$ = buildAST(s , NULL, NULL, NUMBER); }
          | ID '=' assignment { $<nodeval>$ = $3; char *s = strdup($1); int i = cautare_variabila(s); if(strcmp(variabile[i].type, "string") == 0 || strcmp(variabile[i].type, "void") == 0) { printf("eroare: variabila %s are tip diferit; linia: %d\n", s, yylineno); ok = 0; } if(strncmp(variabile[i].type, "const", 5) == 0) { printf("eroare: variabila %s este constanta; linia: %d\n", s, yylineno); ok = 0; } if(i == -1) { printf("eroare: variabila %s nu este definita", s); ok = 0; } char s1[20]; int_to_array(evalAST($3), s1); strcpy(variabile[i].valoare, s1); }
          | ID '=' functionCall { $<nodeval>$ = buildAST("function", NULL, NULL, OTHER); char *s = strdup($1); int i = cautare_variabila(s); if(strcmp(variabile[i].type, "string") == 0 || strcmp(variabile[i].type, "void") == 0) { printf("eroare: variabila %s are tip diferit; linia: %d\n", s, yylineno); ok = 0; } if(strncmp(variabile[i].type, "const", 5) == 0) { printf("eroare: variabila %s este constanta; linia: %d\n", s, yylineno); ok = 0; } if(i == -1) { printf("eroare: variabila %s nu este definita", s); ok = 0; } strcpy(variabile[i].valoare, "0"); }
          | ID '=' array { $<nodeval>$ = buildAST("array", NULL, NULL, OTHER); char *s = strdup($1); int i = cautare_variabila(s); if(strcmp(variabile[i].type, "string") == 0 || strcmp(variabile[i].type, "void") == 0) { printf("eroare: variabila %s are tip diferit; linia: %d\n", s, yylineno); ok = 0; } if(strncmp(variabile[i].type, "const", 5) == 0) { printf("eroare: variabila %s este constanta; linia: %d\n", s, yylineno); ok = 0; } if(i == -1) { printf("eroare: variabila %s nu este definita", s); ok = 0; } strcpy(variabile[i].valoare, "0"); }
          | assignment '+' assignment { $<nodeval>$ = buildAST("+", $1, $3, OP); }
          | assignment '-' assignment { $<nodeval>$ = buildAST("-", $1, $3, OP); }
          | assignment '*' assignment { $<nodeval>$ = buildAST("*", $1, $3, OP); }
          | assignment '/' assignment { $<nodeval>$ = buildAST("/", $1, $3, OP); }
          | '(' assignment ')' { $<nodeval>$ = $2; } 
          | '-' NR { char s[20]; int nr = -yylval.intval; int_to_array(nr, s); $<nodeval>$ = buildAST(s , NULL, NULL, NUMBER); }
          | '-' ID { char *s = strdup($2); int i = cautare_variabila(s); if(i == -1) { printf("eroare: variabila %s nu este definita", s); ok = 0; } int nr = -atoi(variabile[i].valoare); char s2[20]; int_to_array(nr, s2); $<nodeval>$ = buildAST(s2, NULL, NULL, NUMBER); }
          ;

function: TYPE ID '(' ')' bloc { char *s1 = strdup($1); char *s2 = strdup($2); if(cautare_functie(s2, arg2) != -1) { printf("eroare: functia este deja definita; linia: %d\n", yylineno); ok = 0; } else {strcpy(functii[nr_functii].type, s1); strcpy(functii[nr_functii].nume, s2); nr_functii++;} for(int i = start_scope; i < nr_variabile; i++) { strcpy(variabile[i].scope, functii[nr_functii - 1].nume); } start_scope = nr_variabile; }
        | TYPE ID '(' decList ')' bloc { char *s1 = strdup($1); char *s2 = strdup($2); if(cautare_functie(s2, arg2) != -1) { printf("eroare: functia este deja definita; linia: %d\n", yylineno); ok = 0; } else {strcpy(functii[nr_functii].type, s1); strcpy(functii[nr_functii].nume, s2); functii[nr_functii].nr_arg=arg_nr; for(int i=0; i<arg_nr; i++) strcpy(functii[nr_functii].argumente[i], arg2[i]); nr_functii++; arg_nr = 0;} for(int i = start_scope; i < nr_variabile; i++) { strcpy(variabile[i].scope, functii[nr_functii - 1].nume); } start_scope = nr_variabile; bzero(arg2, sizeof(arg2)); arg_nr = 0; }
        ;

decList: TYPE ID ',' decList {char *s = strdup($1); strcpy(arg2[arg_nr], s); arg_nr++; }
       | TYPE ID {char *s = strdup($1); strcpy(arg2[arg_nr], s); arg_nr++; }
       ;

bloc: '{' lines '}' { executa = 1; }
    ;

lines: lines line
     | 
     ;

line: declaration 
    | assignment ';'
    | array '=' assignment ';'
    | whileBloc
    | forBloc
    | ifBloc
    | PRINT '(' TEXT ',' expr ')' ';' { char *s1 = strdup($3); strcpy(s1, s1+1); s1[strlen(s1)-1]='\0'; int nr; nr = evalAST($5); printf("%s%d\n", s1, nr); }
    | functionCall ';'
    ;

// argPrint: ID { char *s = strdup($1); int i = cautare_variabila(s); if( i == -1) { printf("eroare: variabila %s nu este definita\n", s); ok = 0; } else { printf("%s", variabile[i].valoare); } }
//         | argPrint ',' ID { char *s = strdup($3); int i = cautare_variabila(s); if( i == -1) { printf("eroare: variabila %s nu este definita\n", s); ok = 0; } else { printf("%s", variabile[i].valoare); } }
//         | TEXT { char *s = strdup($1); printf("%s", s); }
//         | argPrint ',' TEXT  { char *s = strdup($3); printf("%s", s); }
//         ;

whileBloc: WHILE '(' expr ')' line
         | WHILE '(' expr ')' bloc
         ;

forBloc: FOR '(' expr ';' expr ';' expr ')' line
       | FOR '(' expr ';' expr ';' expr ')' bloc
       ;

ifBloc: IF '(' expr ')' line { if($3 == 0) executa = 0; }
      | IF '(' expr ')' bloc { if($3 == 0) executa = 0; }
      ;

functionCall: ID '(' ')' { char *s = strdup($1); int i = cautare_functie(s, arg2); if(i == -1) { printf("eroare: functia nu este definita; linia: %d\n", yylineno); ok = 0; } }
            | ID '(' listaApel ')' { char *s = strdup($1); int i = cautare_functie(s, arg2); if(i == -1) { printf("eroare: functia nu este definita; linia: %d\n", yylineno); ok = 0; } bzero(arg2, sizeof(arg2)); arg_nr = 0; } 
            ;

listaApel: expr ',' listaApel { strcpy(arg2[arg_nr], "int"); arg_nr++; }
         | expr { strcpy(arg2[arg_nr], "int"); arg_nr++; }
         | functionCall ',' listaApel { strcpy(arg2[arg_nr], "int"); arg_nr++; }
         | functionCall { strcpy(arg2[arg_nr], "int"); arg_nr++; }
         ; 

array: ID'['assignment']'
     ;

structDec: STRUCT ID '{' declarationsStruct '}'
         ; 

declarationsStruct: TYPE listStruct ';'
                  | declarationsStruct TYPE listStruct ';'  
                  ;

listStruct: ID ',' listStruct 
          | ID
          ;

expr: expr GE expr { $<nodeval>$ = buildAST(">=", $1, $3, OP); }
    | expr LE expr { $<nodeval>$ = buildAST("<=", $1, $3, OP); }
    | expr EQ expr { $<nodeval>$ = buildAST("==", $1, $3, OP); }
    | expr NE expr { $<nodeval>$ = buildAST("!=", $1, $3, OP); }
    | expr '<' expr { $<nodeval>$ = buildAST("<", $1, $3, OP); }
    | expr '>' expr { $<nodeval>$ = buildAST(">", $1, $3, OP); }
    | expr AND expr { $<nodeval>$ = buildAST("&&", $1, $3, OP); }
    | expr OR expr { $<nodeval>$ =  buildAST("||", $1, $3, OP); }
    | assignment { $<nodeval>$ = $1; }
    // | array
    ;

%%

int yyerror(char * s)
{
     printf("eroare: %s la linia:%d\n",s,yylineno);
}

int main(int argc, char** argv)
{
     yyin = fopen(argv[1],"r");

     char *filename = "symbol_table.txt";
     fp = fopen("symbol_table.txt", "w+");

     if(fp == NULL)
     {
          printf("Eroare la deschiderea fisierului %s\n", filename);
          return -1;
     }
     
     fp = freopen(NULL, "w+", fp);

     char *filename2 = "symbol_table_functions.txt";
     fp2 = fopen("symbol_table_functions.txt", "w+");

     if(fp2 == NULL)
     {
          printf("Eroare la deschiderea fisierului %s\n", filename2);
          return -1;
     }
     
     fp2 = freopen(NULL, "w+", fp2);

     yyparse();

     for(int i=0; i<nr_variabile; i++)
     {
          fprintf(fp, "%s %s %s %s\n", variabile[i].nume, variabile[i].type, variabile[i].valoare, variabile[i].scope);
     }

     for(int i=0; i<nr_functii; i++)
     {
          fprintf(fp2, "%s %s ", functii[i].nume, functii[i].type);
          fprintf(fp2, "(");
          for(int j=0; j<functii[i].nr_arg; j++)
               fprintf(fp2, "%s ", functii[i].argumente[j]);
          fprintf(fp2, ")\n");
     }
} 