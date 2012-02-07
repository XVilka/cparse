%token_type {char*}

%include {
#include <stdio.h>
#include <stdlib.h>
}

%syntax_error {
	printf("Syntax error!\n");
}

%name cdataParser

fl ::= deflist.
deflist ::= deflist def.
deflist ::= def.
def ::= struct.
def ::= union.
def ::= enum.
def ::= variable.
struct ::= STRUCT name OBRACE deflist  SEMICOLON.
union ::= UNION name OBRACE deflist SEMICOLON.
enum ::= ENUM name OBRACE deflist SEMICOLON.
variable ::= modifier signedness type name SEMICOLON.
variable ::= modifier signedness type ASTERISK name SEMICOLON.
variable ::= modifier signedness type name LBRACKET size RBRACKET SEMICOLON.
size ::= NUMBER.
type ::= .
type ::= CHAR.
type ::= SHORT.
type ::= INTEGER.
type ::= LONG.
type ::= LONG LONG.
type ::= FLOAT.
type ::= DOUBLE.
type ::= VOID.
signedness ::= .
signedness ::= SIGNED.
signedness ::= UNSIGNED.
modifier ::= .
modifier ::= STATIC.
modifier ::= CONST.
modifier ::= REGISTER.
modifier ::= VOLATILE.
name ::= IDENTIFIER.


