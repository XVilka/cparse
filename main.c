#include <stdio.h>
#include <stdlib.h>
#include "cdata.h"
#include "lexglb.h"

extern FILE *yyin;
typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern int yylex(void);
extern YY_BUFFER_STATE yy_scan_string(const char*);
extern void yy_delete_buffer(YY_BUFFER_STATE);

int main(int argc, char** argv)
{
	int n;
	int yv;
	char buf[4096];
	FILE *cfile;
	void* pParser = cdataParseAlloc(malloc);
	item_list *ctx = (item_list *)malloc(sizeof(item_list));

	cfile = fopen("test_parser.c", "ro");
	if (cfile != NULL)
		printf("File opened successfully!\n");
	printf("---------------------------\n");
	while ((n = fread(buf, 1, 4096, cfile)) > 0)
	{
		buf[n] = '\0';
		printf("%s", buf);
		printf("==========================\n");
		yy_scan_string(buf);
		while ((yv=yylex()) !=0)
		{
			cdataParse(pParser, yv, yylval, ctx);
		}
	}
	printf("\n\n");
	printf("---------------------------\n");
	fclose(cfile);
	printf("File closed successfully!\n");

	cdataParse(pParser, 0, yylval, ctx);
	cdataParseFree(pParser, free);
	return EXIT_SUCCESS;
}
