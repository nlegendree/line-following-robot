EXEC=rc
SRCDIR=src
BINDIR=bin
INCLUDEDIR=include
LEVDEVDIR=/usr/include/libevdev-1.0
CC=gcc
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR) -I$(LEVDEVDIR)
LIBS=-levdev -lwiringPi -lwiringPiDev

SRCS := $(wildcard $(SRCDIR)/*.c)

OBJS := $(SRCS:%.c=%.o)

all : $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(OBJS)
	$(CC) -o $@ $(SRCDIR)/*.o $(LIBS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f bin/*
	rm -f src/*.o