#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <signal.h>

#include <SDL.h>
#include <SDL_image.h>
#include <poll.h>

#include "dtype.h"

void load_image(Hash images, SDL_Renderer *renderer, const char *name)
{
    Hash_insert(images, name, IMG_LoadTexture(renderer, name));
}

int main(int argc, char **argv)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Hash images;
    FILE *log = fopen("outsider.log", "w");
    char *inbuf = malloc(256);
    char *cbuf = malloc(256);
    char *cmd;
    assert(argc == 4);
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_NOPARACHUTE);

    window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, atoi(argv[2]), atoi(argv[3]), 0);

    renderer = SDL_CreateRenderer(window, -1, 0);

    images = new_Hash();
    fprintf(stderr, "you probably want to connect now\n");
    while (1)
    {
	fprintf(stderr, "looped\n");
	SDL_RenderPresent(renderer);
	memset(cbuf, 0, 256);

	read(0, inbuf, 256);
	strcpy(cbuf, inbuf);
	fprintf(stderr, "thing: %s\n", inbuf);
	cmd = strtok(cbuf, ":");

	if (!cmd)
	    continue;
	if (strcmp(cmd, "quit") == 0)
	    break;
	else if (strcmp(cmd, "load") == 0)
	{
	    char *image = strtok(NULL,":");
	    fprintf(stderr, "loading!\n");
	    load_image(images, renderer, image);
	}
	else if (strcmp(cmd, "draw") == 0)
	{
	    SDL_Rect rect;
	    char *image = strtok(NULL, ":");
	    char *x = strtok(NULL,":");
	    char *y = strtok(NULL,":");
	    rect.x = atoi(x);
	    rect.y = atoi(y); // yes, this is fine. only a server is going to be passing this info
	    rect.w = 32;
	    rect.h = 32;

	    SDL_RenderCopy(renderer, Hash_get(images, image), NULL, &rect);
	    }

    }
    fclose(log);
    return 0;
}

