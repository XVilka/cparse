#include <stdio.h>
#include <stdlib.h>
#include "cdata.h"

int new_tree(){
	return 0;
}

int print_tree(item_list *tmp) {
	item_list *p;
	p = tmp;
	if (p != NULL) {
		while (p != NULL) {
			switch (p->item_type) {
				case ITEM_VARIABLE:
					printf("var %s\n", p->item.var->name);
					break;
				case ITEM_POINTER:
					printf("ptr %s\n", p->item.ptr->name);
					break;
				case ITEM_ARRAY:
					printf("arr %s[%ld]\n", p->item.arr->name, p->item.arr->count);
					break;
				case ITEM_STRUCT:
					printf("Entering struct %s...\n", p->item.str->name);
					print_tree(p->item.str->items);
					break;
				case ITEM_UNION:
					printf("Entering union %s...\n", p->item.un->name);
					print_tree(p->item.un->items);
					break;
				case ITEM_FUNCTION:
					printf("Entering function %s...\n", p->item.fnc->name);
					print_tree(p->item.fnc->args);
					break;
				default:
					printf("invalid item!\n");
					break;
			}
			p = p->next;
		}
	} else {
		printf("Empty tree!\n");
	}
	return 0;
}

item_list* new_variable_node(char* name, short type, short sign, short modifier)
{
	struct item_variable *ivar = (struct item_variable *)malloc(sizeof(struct item_variable));
	item_list *tmp;
	ivar->name = name;
	ivar->type = type;
	ivar->sign = sign;
	ivar->modifier = modifier;
	tmp = (item_list *)malloc(sizeof(item_list));
	tmp->next = NULL;
	tmp->item_type = ITEM_VARIABLE;
	tmp->item.var = ivar;
	return tmp;
}

item_list* new_pointer_node(char* name, short type, short sign, short modifier)
{
	struct item_pointer *iptr = (struct item_pointer *)malloc(sizeof(struct item_pointer));
	item_list *tmp;
	iptr->name = name;
	iptr->type = type;
	iptr->sign = sign;
	iptr->modifier = modifier;
	tmp = (item_list *)malloc(sizeof(item_list));
	tmp->next = NULL;
	tmp->item_type = ITEM_POINTER;
	tmp->item.ptr = iptr;
	return tmp;
}

item_list* new_array_node(char* name, short type, short sign, short modifier, long size)
{
	struct item_array *iarr = (struct item_array *)malloc(sizeof(struct item_array));
	item_list *tmp;
	iarr->name = name;
	iarr->type = type;
	iarr->count = size;
	iarr->sign = sign;
	iarr->modifier = modifier;
	tmp = (item_list *)malloc(sizeof(item_list));
	tmp->next = NULL;
	tmp->item_type = ITEM_ARRAY;
	tmp->item.arr = iarr;
	return tmp;
}

item_list* new_struct_node(char* name, item_list *defs)
{
	//printf("STRUCT---\n");
	//print_tree(defs);
	//printf("---ENDOFSTRUCT\n");
	struct item_struct *istr = (struct item_struct *)malloc(sizeof(struct item_struct));
	item_list *tmp = (item_list *)malloc(sizeof(item_list));
	istr->name = name;
	istr->items = defs;
	tmp->next = NULL;
	tmp->item_type = ITEM_STRUCT;
	tmp->item.str = istr;
	printf("STRUCT---\n");
	print_tree(tmp);
	printf("---ENDOFSTRUCT\n");
	return tmp;
}

item_list* new_union_node(char* name, item_list *defs)
{
	//printf("UNION---\n");
	//print_tree(defs);
	//printf("---ENDOFUNION\n");
	struct item_union *iun = (struct item_union *)malloc(sizeof(struct item_union));
	item_list *tmp = (item_list *)malloc(sizeof(item_list));
	iun->name = name;
	iun->items = defs;
	tmp->next = NULL;
	tmp->item_type = ITEM_UNION;
	tmp->item.un = iun;
	return tmp;
}

/* Function can return another function or have multiple returns */
//item_list* new_function_node(char* name, item_list *rets, item_list *args)
item_list* new_function_node(char* name, short ret_type, item_list *args, short fmodifier, short callconvention, char* attributes)
{
	func_t *ifnc = (func_t *)malloc(sizeof(func_t));
	item_list *tmp = (item_list *)malloc(sizeof(item_list));
	ifnc->name = name;
	ifnc->rets = ret_type;
	ifnc->fmod = fmodifier;
	ifnc->call = callconvention;
	ifnc->attr = attributes;
	ifnc->args = args;
	tmp->next = NULL;
	tmp->item_type = ITEM_FUNCTION;
	tmp->item.fnc = ifnc;
	printf("FUNCTION---\n");
	print_tree(tmp);
	printf("---ENDOFFUNCTION\n");
	return tmp;
}


