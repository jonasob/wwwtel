LIBS = bsd.o cgi.o
INCPATH = ../include/

all: libtcpip.so

libtcpip.so: $(LIBS)
	ar r libtcpip.so $(LIBS)

.c.o:
	gcc -c $< -I$(INCPATH)
