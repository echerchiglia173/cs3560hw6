CC = g++
CFLAGS = -Wall


all: build

build: main.o game.o othello.o
	$(CC) $(CFLAGS) main.o game.o othello.o

.cc.o: #compile all .cc to .o
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o a.out
