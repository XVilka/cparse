// TODO: add kernel like (uint8_t) types support

/* ====================== Tokens ===================== */

#define IDENTIFIER				1
#define TYPE_CHAR				10
#define TYPE_SHORT				11
#define TYPE_INT				12
#define TYPE_LONG				13
#define BRACKET_LQUADRATIC		22
#define BRACKET_RQUADRATIC		23
#define BRACKET_LFIGURE			24
#define BRACKET_RFIGURE			25
#define COMPLEX_STRUCT			30
#define COMPLEX_UNION			31

struct token {
	char* name;
	char* value;
	int type;
};

typedef struct token_lst token_list;
struct token_lst {
	struct token *tok;
	token_list *next;
	token_list *prev;
	token_list *head;
};

/* ==================== Lexems ====================== */

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


