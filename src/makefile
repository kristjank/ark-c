IDIR =include
CC=gcc
CFLAGS=-I$(IDIR) -lcurl 

ODIR=obj
LDIR=lib

LIBS=-ljson -lcunit

#MAIN
_DEPS = arkconstants.h arkhelpers.h arkmodels.h arkclient.h arkapiaccounts.h arkapibase.h arkapiblocks.h arkapidelegates.h arkapifees.h arkapinetworks.h arkapipeers.h arkapitransactions.h arkapivoters.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = demomain.o arkhelpers.o arkclient.o arkclient.o arkapiaccounts.o arkapibase.o arkapiblocks.o arkapidelegates.o arkapifees.o arkapinetworks.o arkapipeers.o arkapitransactions.o arkapivoters.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


#TEST
_DEPS_TEST = arkconstants.h arkhelpers.h arkmodels.h arkclient.h arkapiaccounts.h arkapibase.h arkapiblocks.h arkapidelegates.h arkapifees.h arkapinetworks.h arkapipeers.h arkapitransactions.h arkapivoters.h
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ_TEST = demotest.o arkhelpers.o arkclient.o arkapiaccounts.o arkapibase.o arkapiblocks.o arkapidelegates.o arkapifees.o arkapinetworks.o arkapipeers.o arkapitransactions.o arkapivoters.o
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: arkmain arktest

arkmain: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

arktest:  $(OBJ_TEST)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

