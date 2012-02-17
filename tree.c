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

item_list* new_variable_node(char* name, short type, short sign, short modifier)
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

item_list* new_pointer_node(char* name, short type, short sign, short modifier)
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

item_list* new_array_node(char* name, short type, short sign, short modifier, long size)
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

/* Do i need reverse "defs" in normal order? */

item_list* list_reverse(item_list *defs)
{
	item_list *t;
	item_list *q = defs;
	item_list *p = NULL;
	while (q != NULL) {
		t = q->next;
		q->next = p;
		p = q;
		q = t;
	}
	return p;
}

item_list* new_struct_node(char* name, item_list *defs)
{
	item_list *itms;
	itms = list_reverse(defs);
	printf("STRUCT---\n");
	print_tree(itms);
	printf("---ENDOFSTRUCT\n");
	struct item_struct *istr = (struct item_struct *)malloc(sizeof(struct item_struct));
	item_list *tmp = (item_list *)malloc(sizeof(item_list));
	istr->name = name;
	istr->items = itms;
	tmp->next = NULL;
	tmp->item_type = ITEM_STRUCT;
	tmp->item.str = istr;
	//print_tree(tmp);
	return tmp;
}

item_list* new_union_node(char* name, item_list *defs)
{
	item_list *itms;
	itms = list_reverse(defs);
	printf("UNION---\n");
	print_tree(itms);
	printf("---ENDOFUNION\n");
	struct item_union *iun = (struct item_union *)malloc(sizeof(struct item_union));
	item_list *tmp = (item_list *)malloc(sizeof(item_list));
	iun->name = name;
	iun->items = itms;
	tmp->next = NULL;
	tmp->item_type = ITEM_UNION;
	tmp->item.un = iun;
	return tmp;
}
