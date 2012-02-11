// TODO: add kernel like (uint8_t) types support

struct Token {
	int dval;
	char* sval;
};
typedef struct Token Token;

#define TYPE_CHAR		0
#define TYPE_SHORT		1
#define TYPE_INT		2
#define TYPE_LONG		3
#define TYPE_LONGLONG	4
#define TYPE_FLOAT		5
#define TYPE_DOUBLE		6
#define TYPE_VOID		7

#define ITEM_STRUCT				1
#define ITEM_ARRAY				2
#define ITEM_POINTER			3
#define ITEM_VARIABLE			4

struct item_variable {
	char* name;
	int type;
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
	int type;
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
	int type;
	long size;
	long count;
	union {
		short shrt;
		int intgr;
		long lng;
		char chr;
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

int new_variable_node(char* name, int type);
int new_pointer_node(char* name, int type);
int new_array_node(char* name, int type, long size);
int new_struct_node(char* name);
int new_union_node(char* name);
