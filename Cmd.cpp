#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include <string.h>

#include "Cmd.h"
#include "Base.h"

using namespace std;

// Constructors
Cmd::Cmd()
{
    
}

Cmd::Cmd(string command)
{
    this->command = command;
}

// returns command
string Cmd::getCmd()
{
    return command;
}

bool Cmd::execute() 
{
    
    // Removing leading whitespace
    if (command.at(0) == ' ') 
    {
        unsigned it = 0;
        while (command.at(it) == ' ') 
        {
            it++;
        }
        command = command.substr(it);
    }

    // Removing trailing whitespace
    if (command.at(command.size()-1) == ' ') 
    {
        unsigned it = command.size()-1;
        while (command.at(it) == ' ') 
        {
            it--;
        }
        command = command.substr(0, it+1);
    }

    // Exit check
    if (command == "exit") 
    {
        exit(0);
    }
    
    // Conversion to c string, creating char* vector
    char* cmd_cstr = (char*)this->command.c_str();
    vector<char*> arguments;
    char* tmp_cstr;
    tmp_cstr = strtok(cmd_cstr, " ");
    while (tmp_cstr != NULL) {
        if (tmp_cstr != '\0')
            arguments.push_back(tmp_cstr);
        
        tmp_cstr = strtok(NULL, " ");
    }

    // Char* array to be passed to execvp()
    char** args = new char*[arguments.size()+1];

    for (unsigned i = 0; i < arguments.size(); i++) 
    {
        args[i] = arguments.at(i);
    }
    args[arguments.size()] = NULL;

    int status; // Create location in memory for which waitpid status info 
                // is stored in
    pid_t pid = fork(); // Fork() so execvp() doesn't quit program

    // If error with fork
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    // Child process, calls execvp()
    if (pid == 0) 
    {
        if (execvp(args[0], args) == -1) 
        {
            perror("exec");
            exit(1);
        }
    }

    // Deallocating char** b/c no longer needed
    delete[] args;

    // Parent process
    if (pid > 0) 
    {
        waitpid(pid, &status, 0);
        if (status > 0) // If status returned, execvp failed
            return false;
        else if (WEXITSTATUS(status) == 0)  // Successful execution
            return true;
        else if (WEXITSTATUS(status) == 1)  // Unsuccessful execution
            return false;
        
    }

    // shouldn't get to here
    return false;
    
}