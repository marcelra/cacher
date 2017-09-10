# :inoremap <S-Tab> <C-V><Tab>
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/


CC=g++
DBGFLAGS=-O0 -g
LIB=

OBJDIR=obj
INCDIR=inc
SRCDIR=src
BINDIR=bin

DEPS=$(INCDIR)/%.h
INCFLAGS=-I$(INCDIR)
LDFLAGS=

CFLAGS=$(INCFLAGS) $(DBGFLAGS)

LIB_OBJ=IBinarySerializable.o \
        TestSerializable.o \
        SerializableRealVector.o \
        Request.o \
        Response.o \
        Utils.o \
        FifoCommunicator.o \
        Exceptions.o \
        DummyAlgorithm.o \
        DependencyListBase.o \
        Parameter.o


_OBJ_SERVER=server.o $(LIB_OBJ)
_OBJ_CLIENT=client.o $(LIB_OBJ)
_OBJ_TESTSUITE=testsuite.o $(LIB_OBJ)

OBJ_SERVER=$(patsubst %,$(OBJDIR)/%,$(_OBJ_SERVER))
OBJ_CLIENT=$(patsubst %,$(OBJDIR)/%,$(_OBJ_CLIENT))
OBJ_TESTSUITE=$(patsubst %,$(OBJDIR)/%,$(_OBJ_TESTSUITE))

all: server client testsuite

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ_SERVER)
	echo $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) -o $(BINDIR)/server $(LDFLAGS)

client: $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) -o $(BINDIR)/client $(LDFLAGS)

testsuite: $(OBJ_TESTSUITE)
	$(CC) $(OBJ_TESTSUITE) -o $(BINDIR)/testsuite $(LDFLAGS)

clean:
	rm -f $(OBJDIR)/*.o

dbg_makefile:
	echo $(OBJ_SERVER)


