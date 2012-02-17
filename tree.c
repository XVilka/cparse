#include <stdio.h>
#include <stdlib.h>
#include "cdata.h"

int new_tree(){
	return 0;
}

int new_variable_node(item_list *ctx, char* name, short type, short sign, short modifier)
{
	struct item_variable *ivar = (struct item_variable *)malloc(sizeof(struct item_variable));
	ivar->name = name;
	ivar->type = type;
	ivar->sign = sign;
	ivar->modifier = modifier;
	printf("Creating new var \"%s\"\n", name);
	// calculate var size
	// cursor->insert_item
	ctx->next = (item_list *)malloc(sizeof(item_list));
	ctx = ctx->next;
	ctx->next = NULL;
	ctx->item_type = ITEM_VARIABLE;
	ctx->item.var = ivar;
	return 0;
}

int new_pointer_node(item_list *ctx, char* name, short type, short sign, short modifier)
{
	struct item_pointer *iptr = (struct item_pointer *)malloc(sizeof(struct item_pointer));
	iptr->name = name;
	iptr->type = type;
	iptr->sign = sign;
	iptr->modifier = modifier;
	printf("Creating new ptr \"%s\"\n", name);
	// calculate pointer size
	// cursor->insert_item
	ctx->next = (item_list *)malloc(sizeof(item_list));
	ctx = ctx->next;
	ctx->next = NULL;
	ctx->item_type = ITEM_POINTER;
	ctx->item.ptr = iptr;
	return 0;
}

int new_array_node(item_list *ctx, char* name, short type, short sign, short modifier, long size)
{
	struct item_array *iarr = (struct item_array *)malloc(sizeof(struct item_array));
	iarr->name = name;
	iarr->type = type;
	iarr->count = size;
	iarr->sign = sign;
	iarr->modifier = modifier;
	printf("Creating new array \"%s\"[%ld]\n", name, size);
	// calculate array size
	ctx->next = (item_list *)malloc(sizeof(item_list));
	ctx = ctx->next;
	ctx->next = NULL;
	ctx->item_type = ITEM_ARRAY;
	ctx->item.arr = iarr;
	return 0;
}

int new_struct_node(item_list *ctx, char* name)
{
	struct item_struct *istr = (struct item_struct *)malloc(sizeof(struct item_struct));
	istr->name = name;
	printf("Creating new structure \"%s\"\n", name);
	// cursor->insert_item
	// set cursor here
	return 0;
}

int new_union_node(item_list *ctx, char* name)
{
	//struct item_union iun;
	//iun.name = name;
	// cursor->insert_item
	// set cursor here
	return 0;
}
