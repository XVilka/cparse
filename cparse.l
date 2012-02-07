%{
#include <stdio.h>
#include <stdlib.h>

#include "cdata.h"
#include "cparse.h"

%}

digits		[0-9]*
letters		[a-zA-Z]*
validid		[a-zA-Z_][a-zA-Z0-9]*

%%
"/*"						{	return(COMMENT_START);	}
"*/"						{	return(COMMENT_END);	}

"void"						{	return(VOID); }
"char"						{	return(CHAR); }
"int"						{	return(INT); }
"long"						{	return(LONG); }
"short"						{	return(SHORT); }
"float"						{	return(FLOAT); }
"double"					{	return(DOUBLE); }
"const"						{	return(CONST); }
"register"					{	return(REGISTER); }
"signed"					{	return(SIGNED); }
"unsigned"					{	return(UNSIGNED); }
"static"					{	return(STATIC); }
"volatile"					{	return(VOLATILE); }
"enum"						{	return(ENUM); }
"struct"					{
								printf("Found struc\n");
								return(STRUCT);
							}
"union"						{	return(UNION); }

"{"							{	return(OBRACE); }
"}"							{	return(EBRACE); }
"["							{	return(LBRACKET); }
"]"							{	return(RBRACKET); }
";"							{	return(SEMICOLON); }

[ \t\v\n\f]					{  }
validid						{	return(IDENTIFIER); }
digits						{	return(NUMBER); }
.							{ /* ignore bad characters */ }

%%

void yyerror(char *s) {
	printf("Error is %s\n", s);
}

int yywrap(void) {
	return (1);
}

int check_type() {
	return(IDENTIFIER);
}

int main(int argc, char** argv) {
	char *programname;
	char *cfile;
	FILE *lexin = NULL;
	if (argc == 2) {
		programname = argv[0];
		cfile = argv[1];
		lexin = fopen(cfile, "r");
		printf("Opened file %s for parsing!\n", cfile);
		lexx(lexin);
		fclose(lexin);
		printf("Parsing done!\n");
	} else {
		printf("Error! I need c program to parse!\n");
		return -1;
	}
	return 0;
}
