%{
#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE char*
#define YYDECL int yylex( YYSTYPE * yylval, yyscan_t yyscanner)
#define YYLEX_PARAM yyscanner
#include "cparse.tab.h"
#include "cparse.h"

%}

%option reentrant

digits		[0-9]*
letters		[a-zA-Z]*
validid		[a-zA-Z_][a-zA-Z0-9]+

%%
"/*"						{ return(COMMENT_START); }
"*/"						{ return(COMMENT_END); }

"void"						{ count(); return(VOID); }
"char"						{ count(); return(CHAR); }
"int"						{ count(); return(INT); }
"long"						{ count(); return(LONG); }
"short"						{ count(); return(SHORT); }
"float"						{ count(); return(FLOAT); }
"double"					{ count(); return(DOUBLE); }
"const"						{ count(); return(CONST); }
"register"					{ count(); return(REGISTER); }
"signed"					{ count(); return(SIGNED); }
"unsigned"					{ count(); return(UNSIGNED); }
"static"					{ count(); return(STATIC); }
"volatile"					{ count(); return(VOLATILE); }
"enum"						{ count(); return(ENUM); }
"struct"					{ count(); return(STRUCT); }
"union"						{ count(); return(UNION); }

"{"							{ count(); return(OBRACE); }
"}"							{ count(); return(EBRACE); }
"["							{ count(); return(LBRACKET); }
"]"							{ count(); return(RBRACKET); }
";"							{ count(); return(SEMICOLON); }

[ \t\v\n\f]					{ count(); }
validid						{ count(); return(IDENTIFIER); }
digits						{ count(); return(NUMBER); }
.							{ /* ignore bad characters */ }

%%

yywrap() {
	return(1);
}


comment() {
		char c, c1;

loop:
		while ((c = input()) != '*' && c != 0)
				putchar(c);

		if ((c1 = input()) != '/' && c != 0)
		{
				unput(c1);
				goto loop;
		}

		if (c != 0)
				putchar(c1);
}


int column = 0;

void count() {
		int i;

		for (i = 0; yytext[i] != '\0'; i++)
				if (yytext[i] == '\n')
						column = 0;
				else if (yytext[i] == '\t')
						column += 8 - (column % 8);
				else
						column++;
}

int check_type() {
/*
	if (yytext == type_name)
		return(TYPE_NAME);
	else
*/
		return(IDENTIFIER);
}

int lexx(FILE* lexin)
{
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(lexin, scanner);
	while (yyparse( scanner));
	yylex_destroy(scanner);
	return 0;
}

int main(int argc, char** argv) {
	char *programname;
	char *cfile;
	FILE *lexin;
	if (argc == 2) {
		programname = argv[0];
		cfile = argv[1];
		lexin = fopen(cfile, "r");
		printf("Opened file %s for parsing!\n", cfile);
		lexx(lexin);
		printf("Parsing done!\n");
	} else {
		printf("Error! I need c program to parse!\n");
		return -1;
	}
	return 0;
}
