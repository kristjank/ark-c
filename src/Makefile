IDIR =include
CC=gcc
CFLAGS=-I$(IDIR) -lcurl -g3 -gdwarf-2 -DDEBUG -g 

ODIR=obj
LDIR=lib

LIBS=-ljson -lcunit lib/libARKCrypto.a

#MAIN
_DEPS = arkconstants.h arkhelpers.h arkmodels.h arkclient.h arkapiaccounts.h arkapibase.h arkapiblocks.h arkapidelegates.h arkapinetworks.h arkapipeers.h arkapitransactions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = demomain.o arkhelpers.o arkclient.o arkclient.o arkapiaccounts.o arkapibase.o arkapiblocks.o arkapidelegates.o arkapinetworks.o arkapipeers.o arkapitransactions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


#TEST
_DEPS_TEST = arkconstants.h arkhelpers.h arkmodels.h arkclient.h arkapiaccounts.h arkapibase.h arkapiblocks.h arkapidelegates.h arkapinetworks.h arkapipeers.h arkapitransactions.h
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS_TEST))

_OBJ_TEST = demotest.o arkhelpers.o arkclient.o arkapiaccounts.o arkapibase.o arkapiblocks.o arkapidelegates.o arkapinetworks.o akapipeers.o arkapitransactions.o
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ_TEST))

#CRYPTO
_DEPS_CRYPTO = arkconstants.h arkhelpers.h arkmodels.h arkclient.h arkapiaccounts.h arkapibase.h arkapiblocks.h arkapidelegates.h arkapinetworks.h arkapipeers.h arkapitransactions.h
DEPS_CRYPTO = $(patsubst %,$(IDIR)/%,$(_DEPS_CRYPTO))

_OBJ_CRYPTO = democrypto.o arkhelpers.o arkclient.o arkapiaccounts.o arkapibase.o arkapiblocks.o arkapidelegates.o arkapinetworks.o arkapipeers.o arkapitransactions.o
OBJ_CRYPTO = $(patsubst %,$(ODIR)/%,$(_OBJ_CRYPTO))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: arkmain arktest arkcrypto

arkmain: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS) 

arktest:  $(OBJ_TEST)
	gcc -o $@ $^ $(CFLAGS) $(LIBS) 

arkcrypto: $(OBJ_CRYPTO)
	gcc -o $@ $^ $(CFLAGS) $(LIBS) 


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f arkmain
	rm -f arktest
	rm -f arkcrypto
