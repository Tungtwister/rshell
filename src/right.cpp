#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "right.h"

Right::Right() : left(0), right("") {}

void Right::setLeft(Base* l) { left = l;}

void Right::setRight(string r) { right = r; }

bool Right::execute() {
	// Removing leading whitespace
	// if (right.at(0) == ' ') {
	    int i = 0;
	    while (right.at(i) == ' ') {
	        i++;
	    }
	    right = right.substr(i);
    // }

    // Removing trailing whitespace
    // if (right.at(right.size() - 1)) {
    int a = right.size() - 1;
    while (right.at(a) == ' ') {
        a--;
    }
    right = right.substr(0, a + 1);
    // }

	// saves stdinput buffer
	int save = dup(1);
	
	// Opens file for input
	int file = open(right.c_str(), O_CREAT|O_RDWR);
	
	// return error if file does not open
	if (file == -1) 
	{
		perror("Could not open file");
		return false;
	}

	// closes the previous input
	close(1);
	dup2(file, 1);

	// execute left command
	bool wow = left->execute();

	// Restore std output conditions
	close(1);
	dup2(save, 1);
	
	return wow;
}