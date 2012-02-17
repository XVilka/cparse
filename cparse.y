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

%extra_argument {item_list *ctx}

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
	new_struct_node(ctx, A.sval);
}
union ::= UNION name(A) OBRACE deflist EBRACE SEMICOLON. {
	new_union_node(ctx, A.sval);
}
enum ::= ENUM name(A) OBRACE deflist EBRACE SEMICOLON.
variable ::= modifier(D) signedness(C) type(B) name(A) SEMICOLON. {
	new_variable_node(ctx, A.sval, B.dval, C.dval, D.dval);
}
pointer ::= modifier(D) signedness(C) type(B) ASTERISK name(A) SEMICOLON. {
	new_pointer_node(ctx, A.sval, B.dval, C.dval, D.dval);
}
array ::= modifier(E) signedness(D) type(C) name(A) LBRACKET size(B) RBRACKET SEMICOLON. {
	new_array_node(ctx, A.sval, C.dval, D.dval, E.dval, B.dval);
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
signedness(A) ::= . { A.sval = ""; A.dval = NONE_SIGN; }
signedness(A) ::= SIGNED. { A.sval = "signed"; A.dval = TYPE_SIGNED; }
signedness(A) ::= UNSIGNED. { A.sval = "unsigned"; A.dval = TYPE_UNSIGNED; }
modifier(A) ::= . { A.sval = ""; A.dval = NONE_MODIFIER; }
modifier(A) ::= STATIC. { A.sval = "static"; A.dval = VAR_STATIC; }
modifier(A) ::= CONST. {A.sval = "const"; A.dval = VAR_CONST; }
modifier(A) ::= REGISTER. { A.sval = "register"; A.dval = VAR_REGISTER; }
modifier(A) ::= VOLATILE. { A.sval = "volatile"; A.dval = VAR_VOLATILE; }
name(A) ::= IDENTIFIER(B). { A.sval = B.sval; }

