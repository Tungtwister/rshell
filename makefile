CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic -g
PARAMS=main.o Cmd.o AND.o OR.o SemiColon.o

all: $(PARAMS)
	mkdir -p ./bin
	$(CC) $(CC_FLAGS) $(PARAMS) -o ./bin/rshell
	rm *o

main.o: src/main.cpp
	$(CC) $(CC_FLAGS) src/main.cpp -c

Cmd.o: src/Command.cpp
	$(CC) $(CC_FLAGS) src/Cmd.cpp -c

Connector.o: src/Connector.cpp
	$(CC) $(CC_FLAGS) src/Connector.cpp -c

AND.o: src/AND.cpp
	$(CC) $(CC_FLAGS) src/AND.cpp -c

OR.o: src/OR.cpp
	$(CC) $(CC_FLAGS) src/OR.cpp -c

Semicolon.o: src/SemiColon.cpp
	$(CC) $(CC_FLAGS) src/Semicolon.cpp -c

clean:
	rm -rf bin
