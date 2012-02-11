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
def ::= pointer.
def ::= array.
struct ::= STRUCT name(A) OBRACE deflist EBRACE SEMICOLON. {
	new_struct_node(A.sval);
}
union ::= UNION name(A) OBRACE deflist EBRACE SEMICOLON.
enum ::= ENUM name(A) OBRACE deflist EBRACE SEMICOLON.
variable ::= modifier signedness type(B) name(A) SEMICOLON. {
	new_variable_node(A.sval, B.dval);
}
pointer ::= modifier signedness type(B) ASTERISK name(A) SEMICOLON. {
	new_pointer_node(A.sval, B.dval);
}
array ::= modifier signedness type(C) name(A) LBRACKET size(B) RBRACKET SEMICOLON. {
	new_array_node(A.sval, B.dval, C.dval);
}
size(A) ::= NUMBER(B). { A.dval = B.dval; }
type ::= .
type(A) ::= CHAR. { A.sval = "char"; A.dval = TYPE_CHAR; }
type(A) ::= SHORT. { A.sval = "short"; A.dval = TYPE_SHORT; }
type(A) ::= INTEGER. { A.sval = "int"; A.dval = TYPE_INT; }
type(A) ::= LONG. { A.sval = "long"; A.dval = TYPE_LONG; }
type(A) ::= LONG LONG. { A.sval = "long long"; A.dval = TYPE_LONGLONG; }
type(A) ::= FLOAT. { A.sval = "float"; A.dval = TYPE_FLOAT; }
type(A) ::= DOUBLE. { A.sval = "double"; A.dval = TYPE_DOUBLE; }
type(A) ::= VOID. { A.sval = "void"; A.dval = TYPE_VOID; }
signedness ::= .
signedness ::= SIGNED.
signedness ::= UNSIGNED.
modifier ::= .
modifier ::= STATIC.
modifier ::= CONST.
modifier ::= REGISTER.
modifier ::= VOLATILE.
name(A) ::= IDENTIFIER(B). { A.sval = B.sval; }

