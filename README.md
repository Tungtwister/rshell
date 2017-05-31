UCR CS100 rshell
===

Authors
--------
Austin Tung - atung003@ucr.edu

Anderson Ju - aju001@ucr.edu

Repository
--------
http://github.com/Tungtwister/rshell.git

Licensing Information
--------
GNU GENERAL PUBLIC LICENSE
Version 3, 29 June 2007

Summary
--------
***rshell*** is a command shell program, created with the intent of having the 
ability to implement BASH commands. rshell prints a command prompt (i.e. $) 
then reads in a command on one line. Commands have the following form:
```
executable [ argumentList ] [ connector cmd ]
```
Valid connectors include:
```
&& , || , ;
```
If a command includes a # symbol, then everything occuring after the # is 
regarded as a comment and not executed.

Running rshell
--------
To run rshell, enter these commands in the following order:
```
1. git clone https://github.com/snguy057/rshell.git
2. cd rshell
3. make
4. ./bin/rshell
```
You will now be able to run BASH commands using ***rshell***

Connector Descriptions
--------
&& Connector: if a command is followed by this connector, then the next command 
   executes only if the first one succeeds.
|| Connector: if a command is followed by this connector, then the next command 
   executes only if the first one fails.
; Connector: if a command is followed by this connector, then the next command 
   is always executed.

Test Scripts
--------
Our project includes a series of test scripts designed to ensure proper 
functionality of our program. In order to run any of these scripts, first 
navigate to the tests/ directory, then enter the following command:
```
./<name_of_script>
```
where <name_of_script> can be replaced by any of the scripts listed below:

```
single_command.sh      #tests single commands
multi_command.sh       #tests commands with connectors (&&, ||, and/or ;)
commented_command.sh   #tests commands containing comments
exit.sh                #tests exit and commands with exit
test.sh                #test Test commands
precedence.sh          #test commands with parentheses
```

known bugs
--------
1. Having an empty command following a connector (ex: echo dog &&, echo dog ||) causes the program to fail
2. The echo command does not support escape characters (e.g. '\n', '\t')
3. The program does not ignore quotes (e.g. echo "cat")
4. The program handles left to right commands (e.g. echo dog || echo cat || echo fish) and outputs 'dog' and 'fish' , while in bash the example outputs 'dog' only. It does not handle echo dog || echo cat as the right failing and that carries on to the echo cat || echo fish, where echo fish would work since echo cat failed beforehand
5. Certain combinations of the Test command combined with parentheses and the OR connector causes the second command to be unrecognized (e.g. (test) || echo dog))
