#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "append.h"

Append::Append() : left(0), right("") {}

void Append::setLeft(Base* l) { left = l;}

void Append::setRight(string r) { right = r; }

bool Append::execute() {
    // Removing leading whitespace
    if (right.at(0) == ' ') {
        unsigned i = 0;
        while (right.at(i) == ' ') {
            i++;
        }
        right = right.substr(i);
    }

    // Removing trailing whitespace
    if (right.at(right.size() - 1) == ' ') { 
        unsigned i = right.size() - 1;
        while (right.at(i) == ' ') {
            i--;
        }
        right = right.substr(0, i+1);
    }

	// saves stdinput buffer
	int save = dup(1);
	
	// Opens file for input
	int file = open(right.c_str(), O_CREAT|O_APPEND|O_RDWR);
	
	// return error if file does not open
	if (file == -1) 
	{
		perror("Could not open file");
		return false;
	}

	// closes previous input
	close(1);
	dup2(file, 1);

	// execute left command
	bool wow = left->execute();

	// Restore std output conditions
	close(1);
	dup2(save, 1);
	
	return wow;
}