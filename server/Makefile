CC=gcc
OUT=

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)


build: $(OBJ)
	@-getdoc

test: build
	$(CC) -o test $(filter-out "main.o", $(OBJ))
	@./test

%.o: %.c
	$(CC) -Wall -c $<

clean:
	rm -f *.o $(OUT) doc.html
