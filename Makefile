CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -g -I headers
LIBS = -lncurses

SOURCES = src/main.c src/linkedlist.c src/file_reader.c src/tester.c src/tui.c

app: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o app $(LIBS)

clean:
	rm -rf app *.dSYM

run: app
	./app