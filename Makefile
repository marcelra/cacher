# :inoremap <S-Tab> <C-V><Tab>
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/


CC=g++
DBGFLAGS=-O0 -g
LIB=

OBJDIR=obj
INCDIR=inc
SRCDIR=src
BINDIR=bin

DEPS=
INCFLAGS=-I$(INCDIR)
LDFLAGS=

CFLAGS=$(INCFLAGS) $(DBGFLAGS)

LIB_OBJ=IBinarySerializable.o TestSerializable.o

_OBJ_SERVER=server.o $(LIB_OBJ)
_OBJ_CLIENT=client.o $(LIB_OBJ)

OBJ_SERVER=$(patsubst %,$(OBJDIR)/%,$(_OBJ_SERVER))
OBJ_CLIENT=$(patsubst %,$(OBJDIR)/%,$(_OBJ_CLIENT))

all: server client

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ_SERVER)
	echo $(OBJ_SERVER)
	$(CC) $< -o $(BINDIR)/server $(LDFLAGS)

client: $(OBJ_CLIENT)
	$(CC) $< -o $(BINDIR)/client $(LDFLAGS)

clean:
	rm -f $(OBJDIR)/*.o
