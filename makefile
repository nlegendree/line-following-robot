EXEC=rc
SRCDIR=code/src
BINDIR=bin
INCLUDEDIR=code/include
LATEXDIR=latex
LEVDEVDIR=/usr/include/libevdev-1.0
CC=gcc
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR) -I$(LEVDEVDIR)
LIBS=-lc -lm -levdev -lwiringPi -lwiringPiDev

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
