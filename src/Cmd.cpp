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
    
    
    // Check for test Command
    if (command.at(0) == '[' && command.at(command.size() - 1) == ']') 
    {
        command.replace(0, 1, "test ");
        command.erase(command.size() - 1);
    }

    if (command == "test" || command == "test ") 
    {
        cout << "(FALSE)" << endl;
        return false;
    }
    else if (command.substr(0, 5) == "test ") 
    {
        return testEvaluate(); 
    }
    
    
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


// Helper that executes the test command
bool Cmd::testEvaluate() 
{
    // clears test and trailing whitespace
    if (command.size() > 4 && command.at(4) == ' ') 
    {
        unsigned i = 4;
        while (i < command.size() && command.at(i) == ' ') 
        {
            i++;
        }
        if (i < command.size()) 
        {
            command = command.substr(i);   
        }
        else 
        {
            cout << "(FALSE)" << endl;
            return false;
        }
    }

    if (command.at(command.size() - 1) == ' ') 
    {
        unsigned i = command.size() - 1;    
        while (command.at(i) == ' ') 
        {
            i--;
        }
        command = command.substr(0, i + 1);
    }

    string flag = command.substr(0, 2);

    struct stat s;

    // checks for a flag
    if (flag.at(0) == '-') 
    {
        // Clears whitespace after the flag 
        if (2 < command.size() && command.at(2) == ' ') 
        {
            unsigned i = 2;
            while (i < command.size() && command.at(i) == ' ') 
            {
                i++;
            }
            command = command.substr(i);
        }
        
        // Checks for a valid flag.
        if (flag != "-f" && flag != "-d" && flag != "-e") 
        {
            string er = "Invalid flag passed into the test."; 
            throw er;
            return false;
        }  

        if (stat(command.c_str(), &s) == -1) 
        {
            cout << "(FALSE)" << endl;
            return false;
        }

        // Flag is -f
        if (flag == "-f") 
        {
            if (S_ISREG(s.st_mode)) 
            {
                cout << "(TRUE)" << endl;
                return true;
            }
            cout << "(FALSE)" << endl;
            return false;
        }
        // Flag is -d 
        else if (flag == "-d") 
        {
            if (S_ISDIR(s.st_mode)) 
            {
                cout << "(TRUE)" << endl;
                return true;
            }
            cout << "(FALSE)" << endl;
            return false;
        }
        // Flag for -e
        else if (flag == "-e") 
        {
            cout << "(TRUE)" << endl;
            return true;
            
        }
    }

    // No flag
    if (stat(command.c_str(), &s) == -1) 
    {
        cout << "(FALSE)" << endl;
        return false;
    }
    
    cout << "(TRUE)" << endl;
    return true;
    
}