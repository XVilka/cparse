%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lexglb.h"
#include "cdata.h"
#include "cparse.h"

%}

%%
"void"						{	return(VOID); }
"char"						{	return(CHAR); }
"int"						{	return(INTEGER); }
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
"struct"					{	return(STRUCT);	}
"union"						{	return(UNION); }

"{"							{	return(OBRACE); }
"}"							{	return(EBRACE); }
"["							{	return(LBRACKET); }
"]"							{	return(RBRACKET); }
";"							{	return(SEMICOLON); }

[ \t\v\n\f]					{  }
[a-zA-Z_][a-zA-Z0-9_]*		{	
								yylval.sval = strdup(yytext);
								return(IDENTIFIER); }
[0-9]*						{	
								yylval.dval = atoi(yytext);
								return(NUMBER); 
							}
.							{ /* ignore bad characters */ }

%%

void yyerror(char *s) {
	printf("Error is %s\n", s);
}

int yywrap(void) {
	return (1);
}

