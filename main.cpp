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

void parse(string&, Base*&);

void makeTree(Base*&, vector<char>&, vector<string>&);

int main()
{
    string userInput;
    Base* inputs = 0;
    
    for( ; ; )
    {
        
        cout << "$ ";
        getline(cin, userInput);
        
        
        //Calls parse on user's input
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

void parse(string& userInput, Base*& inputs)
{
    bool commentFound = 0;
    // bool openingQuote = 0;
    bool closingQuote = 0;
    // bool semicolon = 0;
    // bool AND = 0;
    // bool OR = 0;
    bool closingTest = 0;
    bool commandPushed = 0;
    unsigned openPar = 0; // Counter for opening parentheses
    unsigned closePar = 0;  // Counter for closing parentheses

    vector<char> connectors;
    vector<string> commands;

    // index on string we are beginning at
    unsigned begin = 0;
    
    //for one command
    commands.push_back(userInput.substr(begin, userInput.size() - begin));
    
    makeTree(inputs, connectors, commands);
    
    return;
}

void makeTree(Base*& inputs, vector<char>& connectors, vector<string>& commands)
{
    if(commands.size() == 1)
    {
        Base* in = new Cmd(commands.at(0));
        inputs = in;
        in = 0;
        return;
    }
    
    return;
}
