CFLAGS = -std=c11 -Wall -Wextra -pedantic -g -pg -fprofile -ftest-coverage
LDFLAGS = -g -pg -fprofile -ftest-coverage -ldtype

all: main outsider

main: main.c ipc.o

outsider: outsider.c ipc.o
	$(CC) $(CFLAGS) $(LDFLAGS) outsider.c -o outsider `pkg-config --cflags --libs sdl2 SDL2_image`

parse: parse.c

clean:
	find . -name "*~" -or -name "*.o" -or -name "*.gcno" -or -name "*.log" -or -name "main" -or -name "outsider" -or -name "client" -or -name "parse" -or -name "gman.out" | xargs rm
