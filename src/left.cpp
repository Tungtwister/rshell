#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "left.h"

Left::Left() : left(0), right("") {}

void Left::setLeft(Base* l) { left = l;}

void Left::setRight(string r) { right = r; }

bool Left::execute() 
{
    // Removing leading whitespace
    // if (right.at(0) == ' ') {
        int i = 0;
        while (right.at(i) == ' ') {
            i++;
        }
        right = right.substr(i);
    // }

    // Removing trailing whitespace
    // if (right.at(right.size() - 1) == ' ') { 
        int a = right.size() - 1;
        while (right.at(a) == ' ') {
            a--;
        }
        right = right.substr(0, a + 1);
    // }

	// saves stdinput buffer
	int save = dup(0);
	
	// Opens file for input
	int file = open(right.c_str(), O_RDWR);
	
	// return error if file does not open
	if (file == -1) 
	{
		perror("Could not open file");
		return false;
	}

	// closes previous input
	close(0);
	dup2(file, 0);

	// execute left command
	bool wow = left->execute();

	// Restore std output conditions
	close(0);
	dup2(save, 0);
	
	return wow;
}