CC = g++
CFLAGS = -Wall


all: build document

build: main.o game.o othello.o
	$(CC) $(CFLAGS) main.o game.o othello.o

.cc.o: #compile all .cc to .o
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o a.out

document: Doxyfile
	doxygen Doxyfile

# creates config file, must set input and output for code or defaults to where config file is at.
Doxyfile:
	doxygen -g
