%{
    int num_lines = 0, num_chars = 0;
%}

%option noyywrap
%%
\n	{++num_lines; ++num_chars;}
.	{++num_chars;}

%%
int main(int argc, char** argv){
    FILE *g;
    if(argc>0)
        yyin = fopen(argv[1],"r");
	yylex ();
	printf ("There were %d lines and %d characters.\n",
		num_lines, num_chars);
	return 0;
}