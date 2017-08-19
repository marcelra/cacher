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



all:
	make server
	make client
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CLFAGS)


server: obj/server.o
	$(CC) $< -o $(BINDIR)/server $(LDFLAGS)

client: obj/client.o
	$(CC) $< -o $(BINDIR)/client $(LDFLAGS)

clean:
	rm -f $(OBJDIR)/*.o 
