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

%type source {item_list *}
%type deflist {item_list *}
%type def {item_list *}
%type struct {item_list *}
%type union {item_list *}
%type variable {item_list *}
%type pointer {item_list *}
%type array {item_list *}

source(A) ::= deflist(B). { A = B; }
deflist(A) ::= def(B) deflist(C). { B->next = C; A = B; }
deflist(A) ::= def(B). { A = B; }
def(A) ::= struct(B). { A = B; }
def(A) ::= union(B). { A = B; }
def(A) ::= variable(B). { A = B; }
def(A) ::= pointer(B). { A = B; } 
def(A) ::= array(B). { A = B; }
struct(A) ::= STRUCT name(B) OBRACE deflist(C) EBRACE SEMICOLON. {
	A = new_struct_node(B.sval, C);
}
union(A) ::= UNION name(B) OBRACE deflist(C) EBRACE SEMICOLON. {
	A = new_union_node(B.sval, C);
}
variable(A) ::= modifier(E) signedness(D) type(C) name(B) SEMICOLON. {
	A = new_variable_node(B.sval, C.dval, D.dval, E.dval);
}
variable(A) ::= modifier(E) shorttype(C) name(B) SEMICOLON. {
	switch (C.dval) {
		case UINT8_T:
			A = new_variable_node(B.sval, TYPE_SHORT, TYPE_UNSIGNED, E.dval);
			break;
		case UINT16_T:
			A = new_variable_node(B.sval, TYPE_INT, TYPE_UNSIGNED, E.dval);
			break;
		case UINT32_T:
			A = new_variable_node(B.sval, TYPE_LONG, TYPE_UNSIGNED, E.dval);
			break;
		case UINT64_T:
			A = new_variable_node(B.sval, TYPE_LONGLONG, TYPE_UNSIGNED, E.dval);
			break;
		default:
			break;
	}
}
pointer(A) ::= modifier(E) signedness(D) type(C) ASTERISK name(B) SEMICOLON. {
	A = new_pointer_node(B.sval, C.dval, D.dval, E.dval);
}
pointer(A) ::= modifier(E) shorttype(C) ASTERISK name(B) SEMICOLON. {
	switch (C.dval) {
		case UINT8_T:
			A = new_pointer_node(B.sval, TYPE_SHORT, TYPE_UNSIGNED, E.dval);
			break;
		case UINT16_T:
			A = new_pointer_node(B.sval, TYPE_INT, TYPE_UNSIGNED, E.dval);
			break;
		case UINT32_T:
			A = new_pointer_node(B.sval, TYPE_LONG, TYPE_UNSIGNED, E.dval);
			break;
		case UINT64_T:
			A = new_pointer_node(B.sval, TYPE_LONGLONG, TYPE_UNSIGNED, E.dval);
			break;
		default:
			break;
	}
}
array(A) ::= modifier(F) signedness(E) type(D) name(B) LBRACKET size(C) RBRACKET SEMICOLON. {
	A = new_array_node(B.sval, D.dval, E.dval, F.dval, C.dval);
}
array(A) ::= modifier(F) shorttype(D) name(B) LBRACKET size(C) RBRACKET SEMICOLON. {
	switch (D.dval) {
		case UINT8_T:
			A = new_array_node(B.sval, TYPE_SHORT, TYPE_UNSIGNED, F.dval, C.dval);
			break;
		case UINT16_T:
			A = new_array_node(B.sval, TYPE_INT, TYPE_UNSIGNED, F.dval, C.dval);
			break;
		case UINT32_T:
			A = new_array_node(B.sval, TYPE_LONG, TYPE_UNSIGNED, F.dval, C.dval);
			break;
		case UINT64_T:
			A = new_array_node(B.sval, TYPE_LONGLONG, TYPE_UNSIGNED, F.dval, C.dval);
			break;
		default:
			break;
	}
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
shorttype(A) ::= UINT8. { A.dval = UINT8_T; }
shorttype(A) ::= UINT16. { A.dval = UINT16_T; }
shorttype(A) ::= UINT32. { A.dval = UINT32_T; }
shorttype(A) ::= UINT64. { A.dval = UINT64_T; }
signedness(A) ::= . { A.sval = ""; A.dval = NONE_SIGN; }
signedness(A) ::= SIGNED. { A.sval = "signed"; A.dval = TYPE_SIGNED; }
signedness(A) ::= UNSIGNED. { A.sval = "unsigned"; A.dval = TYPE_UNSIGNED; }
modifier(A) ::= . { A.sval = ""; A.dval = NONE_MODIFIER; }
modifier(A) ::= STATIC. { A.sval = "static"; A.dval = VAR_STATIC; }
modifier(A) ::= CONST. {A.sval = "const"; A.dval = VAR_CONST; }
modifier(A) ::= REGISTER. { A.sval = "register"; A.dval = VAR_REGISTER; }
modifier(A) ::= VOLATILE. { A.sval = "volatile"; A.dval = VAR_VOLATILE; }
name(A) ::= IDENTIFIER(B). { A.sval = B.sval; }

