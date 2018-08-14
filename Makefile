DIRS = lib src
EXEDIR = /usr/local/bin
GROUP = root
OWNER = root

all:
	for dir in $(DIRS);\
	do cd $$dir; make; cd ..;\
	done;

clean:
	for dir in $(DIRS);\
	do cd $$dir; rm -f *.o *.so *.a *.~*; cd ..;\
	done;

install:
	install -s -g $(GROUP) -o $(OWNER) -m 755 bin/program $(EXEDIR)
