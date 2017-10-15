#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#include "parse.h"
#include "dtype.h"

bool isascii(unsigned char u8char)
{
    return u8char <= 128;
}

enum type strtype(const char *str)
{

    for(char c = (char)*str; c != (char)0; c = *(str++))
	if (isascii(c) == false)
	    return UTF8;
    return ASCII;
}

struct parsed parse(char *string)
{
    struct parsed ret;
    ret.cmd = NULL;
    ret.args = new_List(NULL);

    ret.cmd = strtok(string, ":");

    if (ret.cmd)
    {
	char *buf1;
	char *buf2;
	while((buf1 = strtok(NULL, ":")))
	{
	    buf2 = malloc(strlen(buf1) + sizeof(char));
	    if (buf2 == NULL)
	    {
		printf("malloc failed!\n");
		exit(1);
	    }
	    strcpy(buf2, buf1); // no need to strncpy since we know it's the right size
	    List_enqueue(ret.args, buf2);
	}
    }

    return ret;
}


int main(void)
{
    struct parsed output;
    char string[] = "some:foo:bar:test:thing:";

    output = parse(string);

    printf("%s\n", output.cmd);

    LIST_FOREACH(output.args, printf("%s\n", list_elm->car););

    return 0;
}
