%include {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cdata.h"
}

%syntax_error {
	printf("Syntax error!\n");
}

%name cdataParse

%token_type {Token}
%default_type {Token}

program ::= deflist.
deflist ::= deflist def.
deflist ::= def.
def ::= struct.
def ::= union.
def ::= enum.
def ::= variable.
struct ::= STRUCT name(A) OBRACE deflist EBRACE SEMICOLON. {
	printf("Found struct with name \"%s\"!\n", A.sval);
}
union ::= UNION name(A) OBRACE deflist EBRACE SEMICOLON.
enum ::= ENUM name(A) OBRACE deflist EBRACE SEMICOLON.
variable ::= modifier signedness type(B) name(A) SEMICOLON. {
	printf("Found variable with name \"%s\" type \"%s\"!\n", A.sval, B.sval);
}
variable ::= modifier signedness type(B) ASTERISK name(A) SEMICOLON.
variable ::= modifier signedness type(C) name(A) LBRACKET size(B) RBRACKET SEMICOLON.
size(A) ::= NUMBER(B). { A.dval = B.dval; }
type ::= .
type(A) ::= CHAR. { A.sval = "char"; }
type(A) ::= SHORT. { A.sval = "short"; }
type(A) ::= INTEGER. { A.sval = "int"; }
type(A) ::= LONG. { A.sval = "long"; }
type(A) ::= LONG LONG. { A.sval = "long long"; }
type(A) ::= FLOAT. { A.sval = "float"; }
type(A) ::= DOUBLE. { A.sval = "double"; }
type(A) ::= VOID. { A.sval = "void"; }
signedness ::= .
signedness ::= SIGNED.
signedness ::= UNSIGNED.
modifier ::= .
modifier ::= STATIC.
modifier ::= CONST.
modifier ::= REGISTER.
modifier ::= VOLATILE.
name(A) ::= IDENTIFIER(B). { A.sval = B.sval; }

