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

item_list* new_variable_node(item_list *ctx, char* name, short type, short sign, short modifier)
{
	struct item_variable *ivar = (struct item_variable *)malloc(sizeof(struct item_variable));
	item_list *tmp;
	ivar->name = name;
	ivar->type = type;
	ivar->sign = sign;
	ivar->modifier = modifier;
	//printf("Creating new var \"%s\"\n", name);
	tmp = (item_list *)malloc(sizeof(item_list));
	tmp->next = NULL;
	tmp->item_type = ITEM_VARIABLE;
	tmp->item.var = ivar;
	return tmp;
}

item_list* new_pointer_node(item_list *ctx, char* name, short type, short sign, short modifier)
{
	struct item_pointer *iptr = (struct item_pointer *)malloc(sizeof(struct item_pointer));
	item_list *tmp;
	iptr->name = name;
	iptr->type = type;
	iptr->sign = sign;
	iptr->modifier = modifier;
	//printf("Creating new ptr \"%s\"\n", name);
	// calculate pointer size
	// cursor->insert_item
	tmp = (item_list *)malloc(sizeof(item_list));
	tmp->next = NULL;
	tmp->item_type = ITEM_POINTER;
	tmp->item.ptr = iptr;
	return tmp;
}

item_list* new_array_node(item_list *ctx, char* name, short type, short sign, short modifier, long size)
{
	struct item_array *iarr = (struct item_array *)malloc(sizeof(struct item_array));
	item_list *tmp;
	iarr->name = name;
	iarr->type = type;
	iarr->count = size;
	iarr->sign = sign;
	iarr->modifier = modifier;
	//printf("Creating new array \"%s\"[%ld]\n", name, size);
	// calculate array size
	tmp = (item_list *)malloc(sizeof(item_list));
	tmp->next = NULL;
	tmp->item_type = ITEM_ARRAY;
	tmp->item.arr = iarr;
	return tmp;
}

item_list* new_struct_node(item_list *ctx, char* name, item_list *defs)
{
	printf("Members are:\n");
	print_tree(defs);
	struct item_struct *istr = (struct item_struct *)malloc(sizeof(struct item_struct));
	item_list *tmp = (item_list *)malloc(sizeof(item_list));
	istr->name = name;
	istr->items = defs;
	//printf("Creating new structure \"%s\"\n", name);
	// cursor->insert_item
	// set cursor here
	tmp->next = NULL;
	tmp->item_type = ITEM_STRUCT;
	tmp->item.str = istr;
	//print_tree(tmp);
	return tmp;
}

item_list* new_union_node(item_list *ctx, char* name, item_list *defs)
{
	//struct item_union iun;
	//iun.name = name;
	// cursor->insert_item
	// set cursor here
	return NULL;
}
