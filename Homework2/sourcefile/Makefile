LIBRARIES = -framework OpenGL -framework GLUT 

COMPILER = g++
COMPILERFLAGS = -O2

all: a

a: main.o imageFrame.o matrix.o
	g++ -o a main.o imageFrame.o matrix.o -lm

imageFrame.o: imageFrame.cpp imageFrame.h *.h
	g++ -c imageFrame.cpp 

main.o: main.cpp imageFrame.h *.h
	g++ -c main.cpp -lm
	
matrix.o: matrix.cpp matrix.h *.h
	g++ -c matrix.cpp 

clean:
	rm -f *.o a 