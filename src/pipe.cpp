#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "pipe.h"

Pipe::Pipe() : left(0), right("") {}

void Pipe::setLeft(Base* l) { left = l; }

void Pipe::setRight(string r) { right = r; }

bool Pipe::execute()
{
    int pipe1[2];
    pipe(pipe1);
    
    // Removing leading whitespace
    if (right.at(0) == ' ') {
        unsigned i = 0;
        while (right.at(i) == ' ') {
            i++;
        }
        right = right.substr(i);
    }

    // Removing trailing whitespace
    if (right.at(right.size()-1) == ' ') {
        unsigned i = right.size() - 1;
        while (right.at(i) == ' ') {
            i--;
        }
        right = right.substr(0, i + 1);
    }

    // Conversion to c string, creating char* vector
    char* cmd_cstr = (char*)right.c_str();
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

    int status;

    int saveOut = dup(1);
    if (saveOut == -1) 
    {
        perror("dup out");
        return false;
    }

    int saveIn = dup(0);
    if (saveIn == -1) 
    {
        perror("dup in");
        return false;
    }

    //overwrite standard output -- SAVE OUTPUT
    if (dup2(pipe1[1], 1) == -1) 
    {
        perror("dup2 out");
        return false;
    }

    //overwrite standard input -- SAVE INPUT
    if (dup2(pipe1[0], 0) == -1) 
    {
        perror("dup2 in");
        return false;
    }

    //execute left
    bool leftside = left->execute();

    //restore standard OUTPUT
    if (dup2(saveOut, 1) == -1) 
    {
        perror("restore left");
        return false;
    }

    if (close(pipe1[1]) == -1) 
    {
        perror("close 1");
        return false;
    }

    if (!leftside) 
    {
        return false;
    }

    
    pid_t pid = fork();

    // If error with fork
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    // Child
    if (pid == 0) 
    {
        // Execute right side
        if (execvp(args[0], args) == -1) 
        {
            perror("exec");
            exit(1);
        }
        exit(1);
    }

    // Deallocating
    delete[] args;

    // Parent
    if (pid > 0) 
    {
        if (close(pipe1[0]) == -1) 
        {
            perror("close 0");
            return false;
        }

        //restore standard input
        waitpid(pid, &status, 0);
      
        if (dup2(saveIn, 0) == -1) 
        {
            perror("restore right");
            return false;
        }  
        if (status > 0) // If status returned, execvp failed
            return false;
        else if (WEXITSTATUS(status) == 0) // Success
        {
            // cout << "success" << endl;
            return true;
        }
        else if (WEXITSTATUS(status) == 1)  // fail
        {    
            // cout << "fail" << endl;
            return false;
        }

    }
    // Shouldn't be hit
    // cout << "end of pipe" << endl;
    return false;
}