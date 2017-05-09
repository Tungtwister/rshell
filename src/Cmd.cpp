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
string Cmd::getData() 
{
    return command;
}

bool Cmd::execute() 
{
    // get rid of whitespace
    // cout << "command exec" << endl;
    if (command.at(0) == ' ') {
        unsigned it = 0;
        while (command.at(it) == ' ') {
            it++;
        }
        command = command.substr(it);
    }

    // Removing trailing whitespace
    if (command.at(command.size()-1) == ' ') {
        unsigned it = command.size()-1;
        while (command.at(it) == ' ') {
            it--;
        }
        command = command.substr(0, it+1);
    }

    // check to see if exit is called
    if (command == "exit")
        exit(0);

    // // Test Command Check
    // if (command.at(0) == '[' && command.at(command.size() - 1) == ']') {
    //     command.replace(0, 1, "test ");
    //     command.erase(command.size() - 1);
    // }

    // if (command == "test" || command == "test ") {
    //     cout << "(FALSE)" << endl;
    //     return false;
    // }
    // else if (command.substr(0, 5) == "test ") {
    //     return testEvaluate(); 
    // }

    // Conversion to c string, creating char* vector
    char* cmd_cstr = (char*)this->command.c_str();
    vector<char*> arguments;
    char* p;
    p = strtok(cmd_cstr, " ");
    while (p != NULL) {
        if (p != '\0')
            arguments.push_back(p);
        
        p = strtok(NULL, " ");
    }
    // cout << "Arguments: " << endl;
    // for (int i = 0; i < arguments.size(); ++i) {
    //     cout << arguments.at(i) << endl;
    // }

    // Char* array to be passed to execvp()
    char** args = new char*[arguments.size()+1];

    for (unsigned i = 0; i < arguments.size(); i++) {
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
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec");
            exit(1);
        }
    }

    // Deallocating char** b/c no longer needed
    delete[] args;

    // Parent process
    if (pid > 0) {
        waitpid(pid, &status, 0);
        if (status > 0) // If status returned, execvp failed
            return false;
        else if (WEXITSTATUS(status) == 0)  // Successful execution
            return true;
        else if (WEXITSTATUS(status) == 1)  // Unsuccessful execution
            return false;
        
    }

    // Shouldn't be hit
    return false;
}