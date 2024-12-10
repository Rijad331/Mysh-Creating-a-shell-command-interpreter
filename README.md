Introduction:
The presented code represents a basic shell implementation written in the C programming language. A shell is a command-line interface that facilitates user interaction with the operating system and allows you to run commands and manage processes.
The main purpose of this shell is to interpret user input, tokenize commands, and execute them through various mechanisms, including built-in commands and external processes.

Main Components :

1.Header Files 
The code begins by importing the essential C libraries to handle input/output operations, memory management, Boolean expressions, string manipulation, process control, and error handling.
These libraries include <stdio.h>, <stdlib.h>, <stdbool.h>, <string.h>, <sys/wait.h>, <unistd.h>, and <errno.h>.

2.Command Storage 
Structure The commandStorage structure is defined to store information about built-in commands and their corresponding functions.
This structure allows command names to be assigned to specific executable functions, creating a modular and extensible design.

3.Built-in Commands 
•	 myls 
The myls command is used to list the contents of the current directory.
When a user types "myls", the shell uses her execvp function to derive a new process to execute the "ls" command.
The resulting output is displayed in the shell, and any errors during execution are handled and reported accordingly.

•	mygrep
 The mygrep command allows you to easily search for lines that match a specified pattern in a file or input stream.
Similar to Myls, the shell forks a new process and runs the grep command.
Users can specify additional arguments to customize the search.
The shell ensures proper error handling and reports any problems that may occur during execution.

•	mypwd
 The mypwd command prints the current working directory within the shell.
The implementation involves forking a new process to run the pwd command using execvp.
The resulting output is printed to the shell, and any errors that occur during execution are processed and reported.
•	mycd 
The mycd command allows the user to change the current working directory.
The user can specify an optional argument that specifies the path to the desired directory.
If no arguments are given, the shell changes the current directory to the user's home directory.

4.Tokenizer Functions
 A tokenizer function takes a user input string, tokenizes it, and splits it into individual command arguments.The tokens are stored in a dynamically allocated array for further processing.

5.Command Execution Function
 The commandExe function executes a command based on user input.
First, the command entered is checked to see if it is a built-in command. If not, a new process is forked and uses execvp to execute the external command and handle the error accordingly.

6． Main Function 
The main function initializes the shell and enters a loop that continuously reads user input.Dynamically adjust the memory allocated to user input to accommodate varying input lengths.
User input is parsed and executed whenever a newline character occurs, creating an interactive shell experience.
Fully implemented functionality:
 Tokenization: This code includes a tokenizer function that successfully tokenizes user input and separates commands and arguments.

Built-in commands: ``myls'', ``mygrep'', ``mypwd'', ``mycd'' are implemented as built-in commands with associated functionality.
The built-in command was executed successfully, and the corresponding functionality was implemented.

Command Execution: The commandExe function successfully identified and executed the built-in command.
External commands are executed using fork and execvp and provide basic shell functionality.

Dynamic memory allocation: Memory is dynamically allocated  and resized as needed to store user input and tokens.

Partially Implemented Features: 
Error Handling: Basic error handling has been implemented for some scenarios (memory allocation errors, directory change errors, etc.).



Not Implemented Features:
Support for Command-Line Arguments:
 The shell does not handle command-line arguments passed during its execution (int main(int argc, char **argv, char **envp)).

Background processes: Running commands in the background is not supported.

Shell scripts: The shell has no mechanism to read and execute commands from script files.
