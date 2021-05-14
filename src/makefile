IDIR =../include
CC=gcc
CFLAGS= -g -I $(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm -lstdc++

_DEPS = escalonador.hpp kernel.hpp gerenciador_es.hpp gerenciador_mem.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o escalonador.o kernel.o gerenciador_es.o gerenciador_mem.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

so: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 