EXEC=rc
SRCDIR=code/src
BINDIR=bin
INCLUDEDIR=code/include
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

pdf :
	pdflatex -interaction=stopmode --shell-escape ./$(LATEXDIR)/rapport.tex
	rm -f ./*.fls ./*.fdb_latexmk ./*.aux ./*.log ./*.lof ./*.out ./*.synctex.gz ./*.toc
	rm -rf ./_minted-rapport

clean :
	rm -f ./$(BINDIR)/$(EXEC)
	rm -f ./$(SRCDIR)/*.o
	rm -f ./*.pdf ./*.fls ./*.fdb_latexmk ./*.aux ./*.log ./*.lof ./*.out ./*.synctex.gz ./*.toc
	rm -rf ./_minted-rapport
