EXEC=rc
SRCDIR=src
BINDIR=bin
INCLUDEDIR=include
LEVDEVDIR=/usr/include/libevdev-1.0
CC=gcc
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR) -I$(LEVDEVDIR)
LIBS=-levdev -lwiringPi -lwiringPiDev

all : $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o $(SRCDIR)/buzzer.o $(SRCDIR)/controller.o $(SRCDIR)/distance.o $(SRCDIR)/i2cLCD.o $(SRCDIR)/lineFinder.o $(SRCDIR)/obstacle.o $(SRCDIR)/suiveurDeLigne.o
	$(CC) -o $@ $(SRCDIR)/*.o $(LIBS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f bin/*
	rm -f src/*.o