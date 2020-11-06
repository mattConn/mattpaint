CC=gcc
BIN=mattpaint

$(BIN): *.c
	gcc $^ -o $@ -lSDL2

check:
	./$(BIN)

clean:
	rm $(BIN)
