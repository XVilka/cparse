%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lexglb.h"
#include "cdata.h"
#include "cparse.h"

%}

digits		[0-9]*
letters		[a-zA-Z]*
validid		[a-zA-Z_][a-zA-Z0-9]*

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
"enum"						{	return(ENUM); }
"struct"					{	return(STRUCT);	}
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

