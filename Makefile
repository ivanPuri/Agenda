CC = gcc
PY_CFLAGS := $(shell python3-config --cflags)
PY_LDFLAGS := $(shell python3-config --ldflags --embed)
CFLAGS = -Wall -Wextra -std=gnu99 -g -I headers $(PY_CFLAGS)
LIBS = -lncurses $(PY_LDFLAGS)

SOURCES = src/main.c src/linkedlist.c src/file_reader.c src/tester.c src/tui.c

app: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o agenda $(LIBS)

clean:
	rm -rf agenda *.dSYM

run: app
	./agenda
