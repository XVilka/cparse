%{
#include <stdio.h>
#define YYSTYPE char*
#define YYDECL int yylex( YYSTYPE * yylval, yyscan_t yyscanner)
#define YYLEX_PARAM yyscanner
#include "cparse.h"

%}

%parse-param { yyscan_t yyscanner }

%token COMMENT_START COMMENT_END
%token STRUCT UNION ENUM
%token CHAR SHORT INT LONG FLOAT DOUBLE VOID
%token SIGNED UNSIGNED
%token STATIC CONST REGISTER VOLATILE
%token NUMBER STRING IDENTIFIER
%token OBRACE EBRACE LBRACKET RBRACKET SEMICOLON ASTERISK

%%

defs:
	| defs def
	;

def:
	| st
	| un
	| en
	| var
	;

st:
	| STRUCT name OBRACE defs EBRACE SEMICOLON
	{
		printf("Found struct %s\n", $2);
	}
	;

un:
	| UNION name OBRACE defs EBRACE SEMICOLON
	{
		printf("Found union %s\n", $2);
	}
	;

en:
	| ENUM name OBRACE names EBRACE SEMICOLON
	;

var:
	| modifier signedness type name SEMICOLON
	{
		printf("Found %s variable of %s type\n", $4, $3);
	}
	| modifier signedness type ASTERISK name SEMICOLON
	{
		printf("Found %s pointer of %s type\n", $5, $3);
	}
	| modifier signedness type name LBRACKET size RBRACKET SEMICOLON
	{
		printf("Found %s array of %s type with size %ld\n", $4, $3, $6);
	}
	;

size:
	| NUMBER
	;

constant:
	| NUMBER
	| STRING
	;

type:
	| CHAR
	| SHORT
	| INT
	| LONG
	| LONG LONG
	| FLOAT
	| DOUBLE
	| VOID
	;

signedness:
	| SIGNED
	| UNSIGNED
	;

modifier:
	| STATIC
	| CONST
	| REGISTER
	| VOLATILE
	;

name:
	| IDENTIFIER
	;

names:
	| names name
	;

%%

int main(void)
{
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(stdin, scanner);
	while (yyparse( scanner));
	yylex_destroy(scanner);
}
