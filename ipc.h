#ifndef IPC_H
#define IPC_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    int i;
    int o;
    int id;
}child;

typedef struct
{
    char *command;
    char *args[];
}command;

child new_child(const char *filename, char * const args[]);

child *create_map(FILE *map);

#endif
