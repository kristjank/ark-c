IDIR =include
CC=gcc
CFLAGS=-I$(IDIR) -lcurl 

ODIR=obj
LDIR =lib

LIBS=-lm -ljson


_DEPS = function.h arkconstants.h arkmodels.h arkhelpers.h arkapi.h arkcore.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = maindemo.o function.o arkhelpers.o arkapi.o arkcore.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

demomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

