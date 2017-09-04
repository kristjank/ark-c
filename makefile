IDIR =include
CC=gcc
CFLAGS=-I$(IDIR) -lcurl 

ODIR=obj
LDIR =lib

LIBS=-lm -ljson


_DEPS = function.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = maindemo.o function.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

demomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

