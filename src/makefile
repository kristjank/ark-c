IDIR =include
CC=gcc
CFLAGS=-I$(IDIR) -lcurl 

ODIR=obj
LDIR=lib

LIBS=-ljson -lcunit

#MAINFILE
_DEPS = function.h arkconstants.h arkmodels.h arkhelpers.h arkapi.h arkcore.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = maindemo.o function.o arkhelpers.o arkapi.o arkcore.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


#TEST
_DEPS_TEST = function.h arkconstants.h arkmodels.h arkhelpers.h arkapi.h arkcore.h
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ_TEST = arkapi_test.o function.o arkhelpers.o arkapi.o arkcore.o
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: mainark test

mainark: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test:  $(OBJ_TEST)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

