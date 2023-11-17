EXEC=rc
SRCDIR=src
BINDIR=bin
INCLUDEDIR=include
LATEXDIR=latex
CC=gcc
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR)
LIBS=-lc -lm -lSDL2 -lwiringPi -lwiringPiDev

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:.c=.o)

all : $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f $(BINDIR)/$(EXEC)
	rm -f $(SRCDIR)/*.o
	rm -f $(LATEXDIR)/*.pdf $(LATEXDIR)/*.fls $(LATEXDIR)/*.fdb_latexmk $(LATEXDIR)/*.aux $(LATEXDIR)/*.log
