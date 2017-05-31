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
#include "Cmd.h"
#include "Connector.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"
#include "Parentheses.h"

using namespace std;

bool space(const string& userInput);

void parse(string&, Base*&);

void makeTree(Base*&, vector<char>&, vector<string>&);

Base* makeTreeHelp(Base*& Dec, vector<char>& connectors, vector<string>& commands);

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
    bool commandPushed = false;
    bool bracketFound = false;
    
    int closePar = 0;
    int openPar = 0;

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
        else if (userInput.at(i) == '(') { // checks for open parentheses
            ++openPar;
        }
        else if (userInput.at(i) == ')') { // checks for close parentheses
            ++closePar;
        }
    }
    
    string error = "Error. Parentheses do not match up."; // error messages
    
    if (openPar != closePar) { // throws an error if the open and close parentheses don't match up
        throw error;
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
        
        else if (userInput.at(i) == '[') 
        {
            i++;
            while (!bracketFound && i < userInput.size())
            {
                if (userInput.at(i) == ']') 
                {
                    bracketFound = true;
                }
                else {
                    i++;
                }
            }
            if (!bracketFound)
            {
                string s = "Error no closing ']' was found";
                throw s;
            }
            bracketFound = false;
        }
        // checking for the semicolon
        if (userInput.at(i) == ';') {
            /* if i find a semicolon at the end of the user input then I need to 
            push a blank string into commands so that it won't seg fault
            */
            // cout << ";" << endl;
            connectors.push_back(userInput.at(i));
            commands.push_back(userInput.substr(begin, i - begin));
            // if (userInput.at(i) == userInput.at(userInput.size() - 1) && userInput.at(userInput.size() - 1) == ';') {
            //     commands.push_back("");
            // }
            begin = i + 1;
            commandPushed = true;
            
            // semicolon = true;
        }
        // checking for the && symbol and if there is an error if they added && with no right side
        else if (userInput.at(i) == '&' && i < (userInput.size() - 1)) {
            if (userInput.at(i + 1) == '&') {
                // cout << "&" << endl;
                connectors.push_back(userInput.at(i));
                string andCmd = userInput.substr(begin, i - begin);
                if (andCmd != "") {
                // commands.push_back(userInput.substr(begin, i - begin));
                    commands.push_back(andCmd);
                    begin = i + 2;
                    commandPushed = true;
                }
            }
        }
        // checking for the ( symbol
        else if (userInput.at(i) == '(') {
            begin = i + 1; // increments to the first letter of the command following
            connectors.push_back(userInput.at(i));
        }
        else if (userInput.at(i) == ')') {
            connectors.push_back(userInput.at(i));
            // begin = i + 1;  
            string parenthesesCmd = userInput.substr(begin, i - begin);
            // empty string command
            if (parenthesesCmd != "") {
                commandPushed = true;
                // commands.push_back(userInput.substr(begin, i - begin));
                commands.push_back(parenthesesCmd);
                begin = i + 1;
            }
        }
        // checking for the || symbol and if there is an error if they added || with no right side
        else if (userInput.at(i) == '|' && i < (userInput.size() - 1)) {
            if (userInput.at(i + 1) == '|') {
                // cout << "|" << endl;
                connectors.push_back(userInput.at(i));
                string orCmd = userInput.substr(begin, i - begin);
                
                // commands.push_back(userInput.substr(begin, i - begin));
                
                if (orCmd != "") {
                    begin = i + 2;
                    commandPushed = true;
                    commands.push_back(orCmd);
                }
            }
        }
        else if (!connectors.empty() && !commands.empty() && i == userInput.size() - 1 && userInput.at(userInput.size() - 1) != ';') {
            // cout << "if no semicolon" << endl;
            commands.push_back(userInput.substr(begin, userInput.size()));
            // cout << "after no semicolon" << endl;
        }
        // else if (!connectors.empty() && !commands.empty() && i == userInput.size() - 1 && userInput.at(userInput.size() - 1) != ')') {
        //     // cout << "if no semicolon" << endl;
        //     commands.push_back(userInput.substr(begin, userInput.size()));
        //     // cout << "after no semicolon" << endl;
        // }
    }
    
    if (!connectors.empty() && (connectors.back() == ';' || connectors.back() == ')') && commands.back() == "") {
        // cout << "Empty string" << endl;
        connectors.pop_back();
        commands.pop_back();
    }
    
    int semiCounter = 0;
    int andCounter = 0;
    int orCounter = 0;
    for (unsigned i = 0; i < connectors.size(); ++i) {
        if (connectors.at(i) == ';') {
            ++semiCounter;
        }
        if (connectors.at(i) == '&') {
            ++andCounter;
        }
        if (connectors.at(i) == '|') {
            ++orCounter;
        }
    }
    // cout << "semi: " << semiCounter << endl;
    // cout << "And: " << andCounter << endl;
    // cout << "Or: " << orCounter << endl;
    if (((semiCounter > 0 && (andCounter > 0 || orCounter > 0)) || semiCounter > 1) && connectors.back() == ';') {
        cout << "remove semicolon" << endl;
            connectors.pop_back();
        }

    // for one command
    // if user inputs no connectors
    if (connectors.size() == 0) {
        commands.push_back(userInput.substr(begin, userInput.size() - begin));
    }
    
    //testing purposes
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
    // cout << "goes into makeTree" << endl;
    
    // Remove empty commands
    for (unsigned i = 0; i < commands.size(); i++) {
        if (commands.at(i) == "") {
            commands.erase(commands.begin() + i - 1);
        }
    }
    
    // cout << "after for loop in makeTree" << endl;
    
    // ignores the () when checking for empty arguements.
    // unsigned connectS = connectors.size();
    // for (unsigned i = 0; i < connectors.size(); i++)
    // {
    //     cout << "no arguments within parentheses" << endl;
    //     if (connectors.at(i) == '(' || connectors.at(i) == ')')
    //     {
    //         connectS--;
    //     }
    // }
    // if (commands.size() <= connectS || commands.empty()) {
    //     string error = "Error. No arguments passed into connector.";
    //     throw error;
    // }
    
    
    //if only one command with no connectors
    if(commands.size() == 1)
    {
        // cout << "one command" << endl;
        Base* in = new Cmd(commands.at(0));
        inputs = in;
        in = 0;
        return;
    }
    
    // cout << "helper called" << endl;
    Base* Dec = NULL;
    
    inputs = makeTreeHelp(Dec, connectors, commands);
    
    while(!connectors.empty())
    {
        Dec = inputs;
        inputs = makeTreeHelp(Dec, connectors, commands);
    }
    
    return;
}

Base* makeTreeHelp(Base*& Dec, vector<char>& connectors, vector<string>& commands) 
{
    // base case, returns a Command
    // cout << "goes into makeTreeHelp" << endl;
    if (commands.size() == 1 && connectors.empty()) {
        // cout << "base case called" << endl;
        return new Cmd(commands.at(0));
    }
    // else if (commands.size() == 1 && connectors.size() == 1) {
    //     return new Cmd(commands.at(0));
    // }
    
    // builds the tree based on the connector type. in the end it returns the 
    // top node
    
    // cout << "semicolon" << endl;
    if (connectors.back() == ';') {
        connectors.pop_back();
        Semicolon* con = new Semicolon();
        
        // cout << "setRight before" << endl;
        if (Dec == NULL) {
            con->setRight(new Cmd(commands.back()));
            // cout << "setright after" << endl;
            commands.pop_back();
        }
        else {
            con->setRight(Dec);
            Dec = NULL;
        }
        
        // cout << "setLeft before" << endl;
        con->setLeft(makeTreeHelp(Dec, connectors, commands));
        // cout << "setLeft after" << endl;
        
        
        Dec = con;
        // returns top node
        return Dec;
    }

    // cout << "and" << endl;
    if (connectors.back() == '&')
    {
        connectors.pop_back();
        And* con = new And();
        if(Dec == NULL) {
            con->setRight(new Cmd(commands.back()));
            commands.pop_back();
        }
        else
        {
            con->setRight(Dec);
            Dec = NULL;
        }
        
        con->setLeft(makeTreeHelp(Dec, connectors, commands));
        Dec = con;
        
        // returns top node
        return Dec;
    }
    
    // cout << "or" << endl;
    if (connectors.back() == '|') 
    {
        connectors.pop_back();
        Or* con = new Or();
        
        if (Dec == NULL) {
            con->setRight(new Cmd(commands.back()));
            commands.pop_back();
        }
        else {
            con->setRight(Dec);
            Dec = NULL;
        }
        
        con->setLeft(makeTreeHelp(Dec, connectors, commands));
        Dec = con;
        
        // returns top node
        return Dec;
    }
    
    // cout << "()" << endl;
    if (connectors.back() == ')') {
        // cout << "goes in parentheses" << endl;
        stack<string> commandStack;
        stack<char> connectorStack;
        vector<char> copyConnector;
        vector<string> copyCommand;
        int counter = 1;
        
        connectors.pop_back();
        
        // the if statement is incase of nested parentheses
        if (connectors.back() != ')') {
            commandStack.push(commands.back());
            commands.pop_back();
        }
        
        // nested parentheses
        while (counter != 0) {
            //open parentheses
            if (connectors.back() == '(') {
                --counter;
                connectorStack.push(connectors.back());
                connectors.pop_back();
            }
            //close parentheses
            else if (connectors.back() == ')') {
                ++counter;
                connectorStack.push(connectors.back());
                connectors.pop_back();
                if (connectors.back() != ')') {
                    commandStack.push(commands.back());
                    commands.pop_back();
                }
            }
            //if no parentheses
            else {
                connectorStack.push(connectors.back());
                connectors.pop_back();
                if (connectors.back() != ')') {
                    commandStack.push(commands.back());
                    commands.pop_back();
                }
            }
        }
        // this removes an open parentheses '(' from the connector stack
        connectorStack.pop();
        
        // if (!commands.empty()) {
        //     commandStack.push(commands.back());
        //     commands.pop_back();
        // }
        
        int connectorStackSize = connectorStack.size();
        int commandStackSize = commandStack.size();
        
        // puts the elements of connector stack into the copy connector vector to be passed into the makeTreeHelp
        for (int i = 0; i < connectorStackSize; ++i) {
            copyConnector.push_back(connectorStack.top());
            connectorStack.pop();
        }
        
        // puts the elements of command stack into the copy command vector to be passed into the makeTreeHelp
        for (int j = 0; j < commandStackSize; ++j) {
            copyCommand.push_back(commandStack.top());
            commandStack.pop();
        }
        
        // cout << "for copy connectors: " << endl;
        // for(unsigned int i = 0; i < copyConnector.size(); ++i)
        // {
        // cout << copyConnector.at(i) << endl;
        // }
        // cout << "for copy commands: " << endl;
        // for(unsigned int i = 0; i < copyCommand.size(); ++i)
        // {
        // cout << copyCommand.at(i) << endl;
        // }
        // cout << "Size of copy connectors: " << copyConnector.size() << endl;
        // cout << "Size of copy commands: " << copyCommand.size() << endl;
        
        Parentheses* con = new Parentheses(makeTreeHelp(Dec, copyConnector, copyCommand));
        
        // Base* tree = makeTreeHelp(copyConnector, copyCommand);
        
        Dec = con;
        
        while (!connectors.empty()) {
            Dec = makeTreeHelp(Dec, connectors, commands);
        }
        
        // cout << "return Dec" << endl;
        return Dec;
        
    }
    
    // cout << "reaches end of maketree" << endl;
    return 0;
}