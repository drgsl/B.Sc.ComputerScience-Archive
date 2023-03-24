%{
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char *);

extern FILE* yyin;
extern char* yytext;
extern int yylineno;

//De scris in fisier
int fd1, fd2;
char buffer[100];
char buffer2[100];

//daca programul compileaza corect
int correct_compilation = 1;


//Functii
int cautare(char* tip, char* numeVar);
int cautaNume(char *numeVar);
char *obtineTipul(char *numeVar);
int schimbaValoareaNat(char *tip, char *numeVar, int valoareNat);
int schimbaValoareaReal(char *tip, char *numeVar, float valoareReal);
int schimbaValoareaSir(char *tip, char *numeVar, char *valoareSir);
int schimbaValoareaCara(char *tip, char *numeVar, char valoareCara);
int schimbaValoareabool(char *tip, char *numeVar, char *valoareBool);
int cautaVal(char *numeVar);
void Print(char *str, int value);

%} 
%union {
int natVal;
float realVal;
char* bolVal;
char charactVal;
char* sirVal;
char* nameVar;
char* type;
}
%token MAIN nat real character sir BOOL CLASS vec function define
%token IF  ELSE FOR WHILE exec comparation evaluate minus
%token copy compare concat AND OR PRINT
%token <natVal> integer
%token <realVal> nrReal
%token <charactVal> charact
%token <sirVal> s
%token <bolVal> bol
%token <nameVar> identifier


%type <natVal> valoare_nat
%type <realVal> valoare_real
%type <charactVal> valoare_charact
%type <sirVal> valoare_sir
%type <bolVal> valoare_boolean

%type <natVal> operatie_naturala
%type <natVal> operatii_naturale

%type <bolVal> operatii_boolene

%left '+' minus //asociere la stanga 
%left '*' '/'
%left '{' '}' '[' ']' '(' ')'
%left AND
%left OR
%start S
%%

//Inceput
S : progr
{     
      if(correct_compilation== 1)
            printf("Limbaj acceptat!\n");
      else printf("Eroare de compilare! \n");
}

//Declaratii
progr : declaratii_globale main_program
      | main_program
      ;
declaratii_globale : declaratii_globale declaratie    {write(fd1, "global\n", strlen("global\n"));}
                   | declaratie                       {write(fd1, "global\n", strlen("global\n"));}
                   ;
declaratie : variabila
           | variabila_declarata
           | obiect
           | array
           | definitie
           | metoda
           ;

//Variabile (din declaratii)
variabila : nat identifier                                    { if(cautaNume($2)) correct_compilation= 0; snprintf(buffer, 100, "nat %s ", $2); write(fd1, buffer, strlen(buffer)); }
          | character identifier                              { if(cautaNume($2)) correct_compilation= 0; snprintf(buffer, 100, "character %s ", $2); write(fd1, buffer, strlen(buffer)); }
          | real identifier                                   { if(cautaNume($2)) correct_compilation= 0; snprintf(buffer, 100, "real %s ", $2); write(fd1, buffer, strlen(buffer)); }
          | sir identifier                                    { if(cautaNume($2)) correct_compilation= 0; snprintf(buffer, 100, "sir %s ", $2); write(fd1, buffer, strlen(buffer)); }
          | BOOL identifier                                   { if(cautaNume($2)) correct_compilation= 0; snprintf(buffer, 100, "BOOL %s ", $2); write(fd1, buffer, strlen(buffer)); }
          ;
variabila_declarata : nat identifier '=' valoare_nat          { if(cautaNume($2)) correct_compilation= 0;  snprintf(buffer, 100, "nat %s = %d ", $2, $4); write(fd1, buffer, strlen(buffer)); }
                    | real identifier '=' valoare_real        { if(cautaNume($2)) correct_compilation= 0;  snprintf(buffer, 100, "real %s = %.3f ", $2, $4); write(fd1, buffer, strlen(buffer)); }
                    | sir identifier '=' valoare_sir          { if(cautaNume($2)) correct_compilation= 0;  snprintf(buffer, 100, "sir %s = %s ", $2, $4); write(fd1, buffer, strlen(buffer)); }
                    | BOOL identifier '=' valoare_boolean     { if(cautaNume($2)) correct_compilation= 0;  snprintf(buffer, 100, "BOOL %s = %s ", $2, $4); write(fd1, buffer, strlen(buffer)); }
                    | character identifier '=' valoare_charact { if(cautaNume($2)) correct_compilation= 0;  snprintf(buffer, 100, "character %s = %c ", $2, $4); write(fd1, buffer, strlen(buffer)); }
                    ;
obiect : CLASS identifier  { if(cautaNume($2)) correct_compilation= 0; snprintf(buffer2, 100, "CLASS %s \n", $2); write(fd2, buffer2, strlen(buffer2));write(fd2, "local\n", strlen("local\n")); } '{' declaratii_locale '}'              
       ;
array : vec integer nat identifier '=' '[' lista_de_variabile_nat ']'         { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      | vec integer nat identifier '=' '[' ']'                                { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      | vec integer real identifier '=' '[' lista_de_variabile_real ']'       { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      | vec integer real identifier '=' '[' ']'                               { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      | vec integer character identifier '=' '[' lista_de_variabile_charact ']' { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      | vec integer character identifier '=' '[' ']'                            { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      | vec integer BOOL identifier '=' '[' lista_de_variabile_boolean ']'    { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      | vec integer BOOL identifier '=' '[' ']'                               { if(cautaNume($4)) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", $4); write(fd1, buffer, strlen(buffer)); }
      ;
definitie : define identifier integer
          | define identifier s
          | define identifier nrReal
          | define identifier charact
          | define identifier bol
          ;


//MAIN PROGRAM
main_program : MAIN'('')' acolade
           ;
acolade : '{' '}'
        | '{' cods '}'
        ;
cods : cods cod
     | cod
     ;
//Codul in sine
cod : interogare        // if-uri
    | loop             // for,while, do while
    | PRINT '(' sir identifier ',' nat integer ')'  { Print($4,$7);}

      // Apelare functie
      | identifier '(' ')'      
      {     
            if(cautare("function",$1) == 0) 
            {
                  printf("functia %s nu a fost declarata \n", $1); 
                  correct_compilation= 0;
            } 
      }

      //Atribuire, verificam daca au acelasi tip si sunt initializate
      //  | identifier '=' identifier     
      //  {
      //       char *tip1 = obtineTipul($1);  if(tip1 == NULL) { printf("variabila %s e neinitializata \n", $1); correct_compilation= 0; }
      //       char *tip2 = obtineTipul($3);  if(tip2 == NULL) { printf("variabila %s e neinitializata \n", $3); correct_compilation= 0; }
      //       if(tip1 && tip2 && strcmp(tip1,tip2) != 0) { printf("variabilele %s si %s nu sunt de acelasi tip \n", $1, $3); correct_compilation= 0;     }
      //       else schimbaValoareaNat("nat", $1, cautaVal($3));
      //  }

      // declaratii locale in cod
      | declaratie_main 

      // atribuire la reale
      | identifier '=' valoare_real  
      {
            if(cautare("real", $1) == 0) 
                  {correct_compilation= 0; printf("eroare la variabila %s \n", $1);}
            schimbaValoareaReal("real", $1, $3);
      
      }

      // atribuire la sir
      | identifier '=' valoare_sir  
      {
                  if(cautare("sir", $1) == 0)
                        {correct_compilation= 0; printf("eroare la variabila %s \n", $1);} 
                  schimbaValoareaSir("sir", $1, $3);
      }

      // atribuire la charact
      | identifier '=' valoare_charact 
      {
                  if(cautare("character", $1) == 0) 
                        {correct_compilation= 0; printf("eroare la variabila %s \n", $1);} 
                  schimbaValoareaCara("character", $1, $3);
      }

      // atribuire la boolean
      | identifier '=' valoare_boolean 
      {
                  if(cautare("BOOL", $1) == 0) 
                        {correct_compilation= 0; printf("eroare la variabila %s \n", $1);}
                  schimbaValoareabool("BOOL", $1, $3);
      }
            // atribuirea unei expresii la o variabila naturala
      | identifier '=' operatii_naturale
      {       
                  if(cautare("nat", $1) == 0) 
                        {correct_compilation = 0; printf("eroare la variabila %s \n", $1);} 
                  schimbaValoareaNat("nat", $1, $3);
      } 

            //functia evaluate(expr)
      | evaluate '(' operatii_naturale ')' {if(correct_compilation==1) printf("avem valoarea %d \n", $3);}
      |  evaluate '(' operatii_boolene ')' {if(correct_compilation==1) printf("avem valoarea %s \n", $3);}
      ;

declaratii_locale : declaratii_locale declaratie_main     {write(fd1, "local\n", strlen("local\n")); }
                  | declaratie_main                                {write(fd1, "local\n", strlen("local\n"));}
                  ;         
declaratie_main : variabila
                | variabila_declarata
                | obiect
                | array
                | definitie
                | metoda
                ;
// Calcul real al unei expresii
operatii_naturale : operatie_naturala { $$ = $1;}
                  | operatii_naturale '+' operatii_naturale { $$ = $1 + $3; }
                  | operatii_naturale minus operatii_naturale { $$ = $1 - $3;}
                  | operatii_naturale '*' operatii_naturale { $$ = $1 * $3;}
                  | operatii_naturale '/' operatii_naturale { $$ = $1 / $3;}
                  ;
operatie_naturala : 
                  //Verificam daca variabila este initializata si e de tipul int, si ii obtinem valoarea din tabel
                  identifier 
                  {
                        char *tip = obtineTipul($1); 
                        if (tip == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", $1);
                              correct_compilation= 0;
                        }
                        if (tip && strcmp(tip, "nat") != 0)
                        {
                              printf("variabila %s nu este de tipul natural\n", $1);
                              correct_compilation= 0;
                        }
                        if (tip && strcmp(tip, "nat") == 0 ) 
                        {
			      $$ =  cautaVal($1);
			      if( correct_compilation ==1)
                              printf("vom returna %d\n", $$);
                              
                        }
                  }

                  //Atribuim valoarea nr-ul natural
                  | integer {$$ = $1;}
                  ;
operatii_boolene : valoare_boolean AND valoare_boolean 
                  { char *tip1 = obtineTipul($1); 
                        if (tip1 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", $1);
                              correct_compilation= 0;
                        }
                        if (tip1 && strcmp(tip1, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", $1);
                              correct_compilation= 0;
                        }
                        char *tip2 = obtineTipul($3); 
                        if (tip2 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", $3);
                              correct_compilation= 0;
                        }
                        if (tip2 && strcmp(tip2, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", $3);
                              correct_compilation= 0;
                        }
                        if (tip1 && tip2 && strcmp(tip1, "BOOL") == 0 && strcmp(tip2, "BOOL") == 0 ) 
                        {
			      $$ = $1 && $3;
			      if( correct_compilation ==1)
                              printf("vom returna %s\n", $$);
                              
                        }
                  }
                 | valoare_boolean OR valoare_boolean 
                  {char *tip1 = obtineTipul($1); 
                        if (tip1 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", $1);
                              correct_compilation= 0;
                        }
                        if (tip1 && strcmp(tip1, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", $1);
                              correct_compilation= 0;
                        }
                        char *tip2 = obtineTipul($3); 
                        if (tip2 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", $3);
                              correct_compilation= 0;
                        }
                        if (tip2 && strcmp(tip2, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", $3);
                              correct_compilation= 0;
                        }
                        if (tip1 && tip2 && strcmp(tip1, "BOOL") == 0 && strcmp(tip2, "BOOL") == 0 ) 
                        {
			      $$ = $1 || $3;
			      if( correct_compilation ==1)
                              printf("vom returna %s\n", $$);
                              
                        }
                  }
                 ;

interogare : IF  '(' conditie ')' acolade
           | IF  '(' conditie ')' acolade ELSE acolade
           ;
conditie : identifier comparation identifier
         | identifier comparation integer
         | identifier comparation nrReal
         | compare '(' identifier ',' identifier ')'
         ;
loop : FOR variabila_declarata ',' identifier ',' integer acolade 
     | FOR variabila_declarata ',' integer ',' integer acolade
     | FOR variabila_declarata ',' charact ',' integer acolade
     | FOR variabila_declarata ',' identifier ',' nrReal acolade
     | WHILE conditie acolade
     | exec acolade WHILE conditie
     ;
// parametri : variabila
//           | variabila ',' parametri
//           ;
//Functie declarata
metoda: 
      // functie fara parametrii
      function identifier '(' ')'  
      {
            if(cautaNume($2) == 1) 
                  correct_compilation= 0;
            snprintf(buffer2, 100,"function %s: \n", $2); 
            write(fd2, buffer2, strlen(buffer2));
            write(fd2, "global\n", strlen("global\n"));
      } 
      acolade 
      // | // functie cu parametrii
      // function identifier '(' nat identifier ')'  
      // {
      //       if(cautaNume($2) == 1) 
      //             correct_compilation= 0;
      //       snprintf(buffer2, 100,"function %s: \n", $2); 
      //       write(fd2, buffer2, strlen(buffer2));
      //       if(cautaNume($5) == 1) 
      //             correct_compilation= 0;
      //       snprintf(buffer2, 100,"parametri: %d: \n", $5); 
      //       write(fd2, buffer2, strlen(buffer2));
      // } 
      // acolade 
      ;
//pentru numere naturale
valoare_nat : integer { $$=$1; }
            ;
lista_de_variabile_nat : integer
                       | lista_de_variabile_nat ',' integer
                       ;

//pentru numere reale
valoare_real : nrReal { $$=$1; }
             ;
lista_de_variabile_real : nrReal
                       | lista_de_variabile_real ',' nrReal
                       ;

//pentru characte
valoare_charact : charact { $$=$1; }
                 ;
lista_de_variabile_charact : charact
                       | lista_de_variabile_charact ',' charact
                       ;

//pentru boolean
valoare_boolean : bol { $$=$1; }
            ;
lista_de_variabile_boolean : bol
                       | lista_de_variabile_boolean ',' bol
                       ;
//pentru sir
valoare_sir : s { $$=$1; }
            | copy '(' identifier ')'  {$$=identifier;}
            | concat '(' identifier ',' identifier ')' {$$+=identifier;}
            ;
%%

/*a function that is called by the YACC when an error is encountered during parsing. 
It prints the error message "eroare de sintaxa" 
and the line number on which the error occurred. */
int yyerror(char *e){
      printf("eroare de sintaxa: %s la linia:%d\n",e,yylineno);
}
/* a function that searches for a variable with the given name and type in a file 
and returns 1 if found or 0 if not found. */
int cautare(char* tip, char* numeVar)  
{     
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET); //setez cursorul la inceputul fis
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  linie[strlen(linie) - 6] = '\0';      
            else if(strstr(linie, "global"))  
                  linie[strlen(linie) - 7] = '\0';   
            else linie[strlen(linie) - 2] = '\0';

            //Scoatem "="
            if(strstr(linie,"="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Comparam
            //printf("comparam [%s] cu [%s] \n", linie, variabila);
            if (strcmp(linie, variabila) == 0)
                  gasit = 1;
      }

      return gasit;
}

/*a function that checks if a variable with the given name has already been declared 
and returns 1 if it has been declared and 0 if it has not been declared. */
int cautaNume(char *numeVar) //verifica daca variabila a fost deja declarata
{
      int flag = 0;
      flag += cautare("nat",numeVar);
      flag += cautare("real",numeVar);
      flag += cautare("sir",numeVar);
      flag += cautare("character",numeVar);
      flag += cautare("BOOL",numeVar);
      flag += cautare("function", numeVar);
      flag += cautare("vec", numeVar);
      flag += cautare("CLASS", numeVar);
      if(flag == 0)
            return 0;
      printf("variabila %s deja exista \n" ,numeVar);
      return 1;
}
/*a function that takes a string and an integer as arguments
and prints the value of the expression "string + value" */
void Print(char *str, int value)
{
      int int_str=cautaVal(str);
      printf("valoarea expresiei %s+%d este %d\n", str,value,int_str+value);
}
/*a function that checks the type of a variable 
and returns the type of the variable. */
char *obtineTipul(char *numeVar) // verifica ce tip are numeVar si daca exista acest tip (daca variabila e initializata) si returneaza tipul 
{
      char *p = (char *)malloc(20);

      if( cautare("nat",numeVar) )
            strcpy(p, "nat");
      else if( cautare("real",numeVar) )
            strcpy(p, "real");
      else if( cautare("sir",numeVar) )
            strcpy(p, "sir");
      else if( cautare("BOOL",numeVar) )
            strcpy(p, "BOOL");
      else if( cautare("character",numeVar) )
            strcpy(p, "character");
      else if ( cautare("function",numeVar) )
            strcpy(p, "function");
      else if( cautare("vec",numeVar) )
            strcpy(p, "vec");
      else if( cautare("CLASS", numeVar) )
            strcpy(p, "CLASS");
      else  p = NULL;

      return p;
}

int schimbaValoareaNat(char *tip, char *numeVar, int valoareNat)  // x = 6
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %d %s",temp, valoareNat, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}

int schimbaValoareaReal(char *tip, char *numeVar, float valoareReal)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %.2f %s",temp, valoareReal, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}
int schimbaValoareaSir(char *tip, char *numeVar, char *valoareSir)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %s %s",temp, valoareSir, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}

int schimbaValoareaCara(char *tip, char *numeVar, char valoareCara)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %c %s",temp, valoareCara, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}

int schimbaValoareabool(char *tip, char *numeVar, char *valoareBool)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %s %s",temp, valoareBool, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}


/*a function that searches for a variable with the given name in a file, 
finds the value assigned to the variable 
and returns the value. */
int cautaVal(char *numeVar)
{
      char linie[100]="";
      int index = 0;
      char  c;
      char copie[100];

      char variabila[100];
      strcpy(variabila, "natural ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;
            
            //facem o copie a liniei
            strcpy(copie, linie);

            //Remove the local/global part
            if(strstr(linie,"local"))
                  linie[strlen(linie) - 6] = '\0';      
            else if(strstr(linie, "global"))  
                  linie[strlen(linie) - 7] = '\0';   
            else linie[strlen(linie) - 2] = '\0';

            //Scoatem "="
            if(strstr(linie,"="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Comparam
            //printf("comparam [%s] cu [%s] \n", linie, variabila);
            if (strcmp(linie, variabila) == 0)
            {
                  strtok(copie, "=");
                  char *valoare = strtok(NULL, " ");
                  return atoi(valoare);
            }
      }
      return 0;
}

int main(int argc, char** argv){
fd1 = open("symbol_table.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
fd2 = open("symbol_table_functions.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
yyin=fopen(argv[1],"r");
yyparse();
} 
