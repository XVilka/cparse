#include <stdio.h>
#include "cdata.h"

int new_variable_node(strucContx *ctx, char* name, int type)
{
	struct item_variable ivar;
	ivar.name = name;
	ivar.type = type;
	// calculate var size
	// cursor->insert_item
	return 0;
}

int new_pointer_node(strucContx *ctx, char* name, int type)
{
	struct item_pointer iptr;
	iptr.name = name;
	iptr.type = type;
	// calculate pointer size
	// cursor->insert_item
	return 0;
}

int new_array_node(strucContx *ctx, char* name, int type, long size)
{
	struct item_array iarr;
	iarr.name = name;
	iarr.type = type;
	iarr.count = size;
	// calculate array size
	return 0;
}

int new_struct_node(strucContx *ctx, char* name)
{
	struct item_struct istr;
	istr.name = name;
	printf("Creating new structure \"%s\"\n", name);
	// cursor->insert_item
	// set cursor here
	return 0;
}

int new_union_node(strucContx *ctx, char* name)
{
	//struct item_union iun;
	//iun.name = name;
	// cursor->insert_item
	// set cursor here
	return 0;
}
