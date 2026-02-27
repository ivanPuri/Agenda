CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -g -I headers

SOURCES = src/main.c src/time_parser.c src/linkedlist.c src/file_reader.c

app: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o app

clean:
	rm -rf app *.dSYM

run: app
	./app
