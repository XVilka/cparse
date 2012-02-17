// TODO: add kernel like (uint8_t) types support

struct Token {
	int dval;
	char* sval;
};

typedef struct Token Token;

struct tree_thread {
	int level;
};

typedef struct tree_thread;

#define TYPE_CHAR		0
#define TYPE_SHORT		1
#define TYPE_INT		2
#define TYPE_LONG		3
#define TYPE_LONGLONG	4
#define TYPE_FLOAT		5
#define TYPE_DOUBLE		6
#define TYPE_VOID		7
#define TYPE_SIGNED		8
#define TYPE_UNSIGNED	9

#define NONE_SIGN	11
#define NONE_MODIFIER 12

#define VAR_STATIC 0
#define VAR_CONST  1
#define VAR_REGISTER 2
#define VAR_VOLATILE 3

#define ITEM_STRUCT				1
#define ITEM_ARRAY				2
#define ITEM_POINTER			3
#define ITEM_VARIABLE			4

struct item_variable {
	char* name;
	short type;
	short sign;
	short modifier;
	int size;
	union {
		short shrt;
		int intgr;
		long lng;
		char chr;
	} value;
};

struct item_pointer {
	char* name;
	short type;
	short sign;
	short modifier;
	int size;
	union {
		short shrt;
		int intgr;
		long lng;
		char chr;
	} value;
};

struct item_array {
	char* name;
	short type;
	short sign;
	short modifier;
	long size;
	long count;
	union {
		short *shrt;
		int *intgr;
		long *lng;
		char *chr;
	} value;
};

typedef struct item_lst item_list;

struct item_struct {
	char* name;
	long size;
	int level;
	item_list *items;
};

struct item_lst {
	short item_type;
	union {
		struct item_variable *var;
		struct item_pointer *ptr;
		struct item_array *arr;
		struct item_struct *str;
	} item;
	item_list *next;
	item_list *prev;
	item_list *head;
};

int new_variable_node(item_list *ctx, char* name, short type, short sign, short modifier);
int new_pointer_node(item_list *ctx, char* name, short type, short sign, short modifier);
int new_array_node(item_list *ctx, char* name, short type, short sign, short modifier, long size);
int new_struct_node(item_list *ctx, char* name);
int new_union_node(item_list *ctx, char* name);
