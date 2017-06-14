CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic -g
PARAMS=main.o Cmd.o Connector.o And.o Or.o Semicolon.o Parentheses.o left.o right.o append.o pipe.o

all: $(PARAMS)
	mkdir -p ./bin
	$(CC) $(CC_FLAGS) $(PARAMS) -o ./bin/rshell
	rm *o

main.o: src/main.cpp
	$(CC) $(CC_FLAGS) src/main.cpp -c

Cmd.o: src/Cmd.cpp
	$(CC) $(CC_FLAGS) src/Cmd.cpp -c
	
Connector.o: src/Connector.cpp
	$(CC) $(CC_FLAGS) src/Connector.cpp -c

And.o: src/And.cpp
	$(CC) $(CC_FLAGS) src/And.cpp -c

Or.o: src/Or.cpp
	$(CC) $(CC_FLAGS) src/Or.cpp -c

Semicolon.o: src/Semicolon.cpp
	$(CC) $(CC_FLAGS) src/Semicolon.cpp -c

Parentheses.o: src/Parentheses.cpp
	$(CC) $(CC_FLAGS) src/Parentheses.cpp -c
	
left.o: src/left.cpp
	$(CC) $(CC_FLAGS) src/left.cpp -c

right.o: src/right.cpp
	$(CC) $(CC_FLAGS) src/right.cpp -c
	
append.o: src/append.cpp
	$(CC) $(CC_FLAGS) src/append.cpp -c
	
pipe.o: src/pipe.cpp
	$(CC) $(CC_FLAGS) src/pipe.cpp -c

clean:
	rm -rf bin
