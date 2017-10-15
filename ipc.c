#include "ipc.h"

child *create_map(FILE *map)
{
    return NULL;
}

child new_child(const char *filename, char * const args[])
{
    child ret;
    int ppipes[2];
    int cpipes[2];
    printf("%s %s %s\n", filename, args[0], args[1]);
    assert(pipe(ppipes) == 0);
    assert(pipe(cpipes) == 0);

    int id = fork();
    if (id == 0)
    {
	dup2(ppipes[0], 0);
	dup2(cpipes[1], 1);
	close(ppipes[1]);
	close(cpipes[0]);
	printf("%d %d\n", ppipes[0], cpipes[1]);
	execv(filename, args);
    }

    close(ppipes[0]);
    close(cpipes[1]);
    ret.o = cpipes[0];
    ret.i = ppipes[1];
    ret.id = id;

    return ret;
}
