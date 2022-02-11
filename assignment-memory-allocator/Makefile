BUILDDIR=build
SRCDIR=src
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(wildcard $(SRCDIR)/*.c))
HEADERS = $(wildcard $(SRCDIR)/*.h)
CC=gcc
CFLAGS = -std=gnu11 -Wall -pedantic -I$(SRCDIR)/ -ggdb -Wextra -Werror -DDEBUG


all: $(BUILDDIR)/main

run: $(BUILDDIR)/main
	./$(BUILDDIR)/main

build:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean build run