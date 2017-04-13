.c.o:   $*.h
	gcc -c -ISOIL -Wno-deprecated $*.c

.cpp.o:	$*.h
	g++	-c -ISOIL -Wno-deprecated $*.cpp

all:	quadtree

quadtree:  quadtree.o winGL.o
	gcc -o $@ $^ -LSOIL -lglut -lGL -lGLU -lSOIL -lm

clean:
	rm *.o *.*~ *~ quadtree
