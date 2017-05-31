#ifndef CMD_H
#define CMD_H

#include <string>
#include <string.h>
#include <vector>

#include "Base.h"

using namespace std;

class Cmd : public Base
{
    private:
        string command;
        
    public:
        Cmd();
        
        Cmd(string command);
        
        bool execute();
        
        string getData();
        
        bool testHelper();
};

#endif