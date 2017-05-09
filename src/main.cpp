// Authors: Austin Tung and Anderson Ju
// Username: atung003 and aju001

#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <unistd.h>
#include <string>
#include <stack>

#include "Base.h"
#include "Cmd.cpp"
#include "Connector.cpp"
#include "And.cpp"
#include "Or.cpp"
#include "Semicolon.cpp"

using namespace std;

bool space(const string& userInput);

void parse(string&, Base*&);

void makeTree(Base*&, vector<char>&, vector<string>&);

Base* makeTreeHelp(vector<char>& connectors, vector<string>& commands);

int main()
{
    string userInput;
    Base* inputs = 0;
    
    for ( ; ; )
    {
        
        cout << "$ ";
        getline(cin, userInput);
        
        
        //Calls parse on user's input
        
        // checks if there is no input, only spaces, or comments
        if (userInput == "" || space(userInput)) {
            continue;
        }

        try {
            parse(userInput, inputs);
            inputs->execute();
        }
        catch(string s) {
            cout << s << endl;
            continue;
        }
        
    }
    
    return 0;
}

bool space(const string& userInput) 
{
    for (unsigned it = 0; it < userInput.size(); it++) 
    {
        if (userInput.at(it) != ' ' && userInput.at(it) != '#') 
        {
            return false;
        }
        else if (userInput.at(it) == '#') 
        {
            return true;
        }
    }

    return true;
}

void parse(string& userInput, Base*& inputs)
{
    bool commentFound = false;
    bool closingTest = false;
    bool commandPushed = false;

    vector<char> connectors;
    vector<string> commands;

    // index on string we are beginning at
    unsigned begin = 0;
    
    //check if the user inputted a comment symbol
    for (unsigned i = 0; i < userInput.size() && commentFound != true; ++i) {  // works
        if (userInput.at(i) == '#') {
            // cout << "#" << endl;
            commentFound = true;
            userInput = userInput.substr(begin, i - begin);
        }
    }
    
    // to get rid of the whitespaces
    if (userInput.at(userInput.size() - 1) == ' ') {
        unsigned i = userInput.size() - 1;
        while (userInput.at(i) == ' ') {
            --i;
        }
        userInput = userInput.substr(0, i + 1);
    }
    
    for (unsigned i = 0; i < userInput.size(); ++i) {
        // if a command was found
        if (commandPushed) {
            while (userInput.at(i) == ' ' && i < userInput.size()) {
                if (i != userInput.size() - 1) {
                    ++i;
                    ++begin;
                }
            }
            commandPushed = false;
        }
        // checking for the semicolon
        if (userInput.at(i) == ';') {
            // cout << ";" << endl;
            connectors.push_back(userInput.at(i));
            commands.push_back(userInput.substr(begin, i - begin));
            begin = i + 1;
            commandPushed = true;
            // semicolon = true;
        }
        // checking for the && symbol and if there is an error if they added && with no right side
        else if (userInput.at(i) == '&' && i < (userInput.size() - 1)) {
            if (userInput.at(i + 1) == '&') {
                // cout << "&" << endl;
                connectors.push_back(userInput.at(i));
                commands.push_back(userInput.substr(begin, i - begin));
                begin = i + 2;
                commandPushed = true;
            }
        }
        // checking for the || symbol and if there is an error if they added || with no right side
        else if (userInput.at(i) == '|' && i < (userInput.size() - 1)) {
            if (userInput.at(i + 1) == '|') {
                // cout << "|" << endl;
                connectors.push_back(userInput.at(i));
                commands.push_back(userInput.substr(begin, i - begin));
                begin = i + 2;
                commandPushed = true;
            }
        }
        else if (!connectors.empty() && !commands.empty() && i == userInput.size() - 1 && userInput.at(userInput.size() - 1) != ';') {
            // cout << "if no semicolon" << endl;
            commands.push_back(userInput.substr(begin, userInput.size()));
            // cout << "after no semicolon" << endl;
        }
    }
    
    if (!connectors.empty() && connectors.back() == ';' && commands.back() == "") {
        cout << "Empty string" << endl;
        connectors.pop_back();
        commands.pop_back();
    }

    // for one command
    // if user inputs no connectors
    if (connectors.size() == 0) {
        commands.push_back(userInput.substr(begin, userInput.size() - begin));
    }
    
    // cout << "for connectors: " << endl;
    // for(unsigned int i = 0; i < connectors.size(); ++i)
    // {
    // cout << connectors.at(i) << endl;
    // }
    // cout << "for commands: " << endl;
    // for(unsigned int i = 0; i < commands.size(); ++i)
    // {
    // cout << commands.at(i) << endl;
    // }
    // cout << "Size of connectors: " << connectors.size() << endl;
    // cout << "Size of commands: " << commands.size() << endl;
    
    makeTree(inputs, connectors, commands);
    
    return;
}

void makeTree(Base*& inputs, vector<char>& connectors, vector<string>& commands)
{
    
    // Remove empty commands
    for (unsigned i = 0; i < commands.size(); i++) {
        if (commands.at(i) == "") {
            commands.erase(commands.begin() + i - 1);
        }
    }
    
    //if only one command with no connectors
    if(commands.size() == 1)
    {
        Base* in = new Cmd(commands.at(0));
        inputs = in;
        in = 0;
        return;
    }
    
    // cout << "helper called" << endl;
    inputs = makeTreeHelp(connectors, commands);
    
    return;
}

Base* makeTreeHelp(vector<char>& connectors, vector<string>& commands) 
{
    // base case, returns a Command
    if (commands.size() == 1 && connectors.empty()) {
        // cout << "base case called" << endl;
        return new Cmd(commands.at(0));
    }
    
    // builds the tree based on the connector type. in the end it returns the 
    // top node
    
    // cout << "semicolon" << endl;
    if (connectors.back() == ';') {
        connectors.pop_back();
        Semicolon* con = new Semicolon();
        
        // cout << "setRight before" << endl;
        con->setRight(new Cmd(commands.back()));
        // cout << "setright after" << endl;
        commands.pop_back();
        
        // cout << "setLeft before" << endl;
        con->setLeft(makeTreeHelp(connectors, commands));
        // cout << "setLeft after" << endl;
        
        // returns top node
        return con;
    }

    // cout << "and" << endl;
    if (connectors.back() == '&')
    {
        connectors.pop_back();
        And* con = new And();
        
        con->setRight(new Cmd(commands.back()));
        commands.pop_back();
        
        con->setLeft(makeTreeHelp(connectors, commands));
        
        // returns top node
        return con;
    }
    
    // cout << "or" << endl;
    if (connectors.back() == '|') 
    {
        connectors.pop_back();
        Or* con = new Or();
        
        con->setRight(new Cmd(commands.back()));
        commands.pop_back();
        
        con->setLeft(makeTreeHelp(connectors, commands));
        
        // returns top node
        return con;
    }
    
    // cout << "reaches" << endl;
    return 0;
}