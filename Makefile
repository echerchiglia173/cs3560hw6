CC = g++
CFLAGS = -Wall


all: build document

build: main.o game.o othello.o
	$(CC) $(CFLAGS) main.o game.o othello.o

.cc.o: #compile all .cc to .o
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o a.out
	rm -rf html latex
	#removes html and latex directory/folder

#compiles the document file relies on Doxyfile configure.
#if it is not present it makes one.
doc: Doxyfile
	doxygen Doxyfile

# creates config file, must set input and output for code and documen.
# Else it  defaults to where config file is at for the sourcd code and output of the document.
Doxyfile:
	doxygen -g
