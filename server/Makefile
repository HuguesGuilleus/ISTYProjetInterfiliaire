CC=gcc
OUT=a.out

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: build
	@echo $(OBJ)
	$(CC) -o $(OUT) $(filter-out test.o, $(OBJ))
	./$(OUT)

build: $(OBJ)
	@-getdoc

test: build
	$(CC) -o test $(filter-out main.o, $(OBJ))
	@./test

%.o: %.c
	$(CC) -Wall -c $<

clean:
	rm -f *.o $(OUT) doc.html test
