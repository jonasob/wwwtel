LIBS = -ltcpip
EXES = nph-textout.cgi send.cgi setup.cgi nph-backend.cgi frontend.cgi
LIBPATH = ../lib/
INCPATH = ../include/

all: $(EXES)
	mv $(EXES) ../bin

nph-textout.cgi: nph-textout.o
	gcc -o nph-textout.cgi nph-textout.o -L$(LIBPATH) $(LIBS) -I$(INCPATH)

send.cgi: send.o
	gcc -o send.cgi send.o -L$(LIBPATH) $(LIBS) -I$(INCPATH)

frontend.cgi: frontend.o
	gcc -o frontend.cgi frontend.o -L$(LIBPATH) $(LIBS) -I$(INCPATH)

setup.cgi: setup.o
	gcc -o setup.cgi setup.o -L$(LIBPATH) $(LIBS) -I$(INCPATH)

nph-backend.cgi: nph-backend.o
	gcc -o nph-backend.cgi nph-backend.o -L$(LIBPATH) $(LIBS) -I$(INCPATH)

.c.o:
	gcc -c $< -I$(INCPATH)
