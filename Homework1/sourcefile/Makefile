LIBRARIES = -framework OpenGL -framework GLUT 

COMPILER = g++
COMPILERFLAGS = -O2

all: a

a: main.o imageFrame.o 
	g++ -o a main.o imageFrame.o -lm

imageFrame.o: imageFrame.cpp imageFrame.h *.h
	g++ -c imageFrame.cpp 

main.o: main.cpp imageFrame.h *.h
	g++ -c main.cpp -lm

clean:
	rm -f *.o a 