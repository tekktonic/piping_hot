#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "ipc.h"

/*@checked@*/
int main(int argc, char **argv)
{
    char *command;
    child outsider;
    char *tm = malloc(256);

    if (argv[1])
	command = argv[1];
    else
	command = "outsider";

    char *cmd[5] = {command, command, "640", "480", NULL};
    char sink[2];
    outsider = new_child(command, cmd);


    int ret;
    ret = write(outsider.i, "load:player.png:", 256);
    if (ret == -1)
    {
	fprintf(stderr, "load %s\n", strerror(errno));
	exit(1);
    }
    ret = write(outsider.i, "draw:player.png:0:0:", 256);
    if (ret == -1)
    {
	fprintf(stderr, "draw %s\n", strerror(errno));
	exit(1);
    }
    sleep(8);
    kill(outsider.id, SIGKILL);
    free(tm);

    return 0;
}
