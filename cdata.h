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
#define TYPE_SIGNED		8
#define TYPE_UNSIGNED	9

#define UINT8_T		1
#define UINT16_T	2
#define UINT32_T	3
#define UINT64_T	4

#define NONE_SIGN	11
#define NONE_MODIFIER 12

#define VAR_STATIC 0
#define VAR_CONST  1
#define VAR_REGISTER 2
#define VAR_VOLATILE 3

#define FMODIFIER_NONE	0
#define FMODIFIER_STATIC 1
#define FMODIFIER_VOLATILE 2
#define FMODIFIER_INLINE 3

#define CALLCONV_NONE 0
#define CALLCONV_STDCALL 1
#define CALLCONV_CCALL 2

#define ITEM_STRUCT				1
#define ITEM_UNION				2
#define ITEM_ENUM				3
#define ITEM_ARRAY				4
#define ITEM_POINTER			5
#define ITEM_VARIABLE			6
#define ITEM_FUNCTION			7

typedef struct item_function func_t;

struct item_variable {
	char* name;
	short type;
	short sign; // move to bitmask
	short modifier; // move to bitmask
	int size;
	union {
		short shrt;
		int intgr;
		long lng;
		char chr;
		func_t *fnc;
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
		//func_t fnc;
	} value;
};

/* TODO: support for multidimension array */
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

struct item_union {
	char* name;
	long size;
	int level;
	item_list *items;
};

struct item_function {
	char* name;
	long size; // Size of function header?
	int param_count; // Function arguments counter
	/*item_list *rets; // Type of return value */
	short rets;
	short fmod; //  static, inline or volatile?
	short call; // calling convention
	char* attr; // __attribute__(()) list
	item_list *args; // list of arguments
};

struct item_lst {
	short item_type;
	union {
		struct item_variable *var;
		struct item_pointer *ptr;
		struct item_array *arr;
		struct item_struct *str;
		struct item_union *un;
		struct item_function *fnc;
	} item;
	item_list *next;
	item_list *prev;
	item_list *head;
};

item_list* new_variable_node(char* name, short type, short sign, short modifier);
item_list* new_pointer_node(char* name, short type, short sign, short modifier);
item_list* new_array_node(char* name, short type, short sign, short modifier, long size);
item_list* new_struct_node(char* name, item_list *defs);
item_list* new_union_node(char* name, item_list *defs);
item_list* new_function_node(char* name, short ret_type, item_list *args, short fmodifier, short callconvention, char* attributes);

int print_tree(item_list *tmp);
