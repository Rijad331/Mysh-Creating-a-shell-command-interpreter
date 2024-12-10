// MyShell task done by GROUP L


// Import necessary libraries for input/output, memory management, boolean expressions,
// string manipulation, process control, and error handling.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

// Define a struct to store built-in commands and their corresponding functions.
struct commandStorage {
    char *cmd_name; // Command name (string), e.g., "cd"
    void (*cmd_func)(char **args); // Pointer to the associated function, e.g., changeDir
};

// Implement the directory change function.
void changeDir(char **args) {
    // Check if the second argument (path) is empty; if so, change the current directory to the root.
    char* root = getenv("home");
    if (args[1] == NULL) {
        chdir(root);
    } else {
        // Display an error message if the directory change with chdir was not successful.
        if (chdir(args[1]) != 0) {
            printf("Directory change error\n");
        }
    }
}

// Implement the shell exit method.
void exitShell(char **args) {
    // Use exit(0) to successfully exit the program/shell.
    exit(0);
}

// Store commands and their associated functions in a struct/array.
struct commandStorage commands[] = {
    {"mycd", changeDir},
    {"exit", exitShell},
};

// Tokenize user input for command execution.
char** tokenizer(char *input) {
    int storageSize = 0;
    int inputSize = 32;

    // Allocate memory for tokens storage.
    char **tokensList = malloc(inputSize * sizeof(char*));

    // Check for memory allocation errors and exit if encountered.
    if (!tokensList) {
        perror("Memory allocation error\n");
        exit(1);
    }

    // Define delimiters for tokenization (whitespace and newline).
    char *delimiters = " \n";

    // Tokenize the input and store tokens in the storage.
    char *token = strtok(input, delimiters);
    while (token != NULL) {
        tokensList[storageSize] = token;
        storageSize++;
        token = strtok(NULL, delimiters);
    }

    // Set the last element of the storage to a null pointer and return the tokens.
    tokensList[storageSize] = NULL;
    return tokensList;
}

// Execute commands based on user input.
void commandExe(char **args) {
    int i = 0;
    while (i < 4) {
        // Check if the first argument of user input matches the name of a command in the struct.
        if (strcmp(args[0], commands[i].cmd_name) == 0) {
            commands[i].cmd_func(args);
            return;
        }
        i++;
    }

    // Fork to create a new process.
    pid_t cPid = fork();

    // If the child pid is 0, execute certain commands.
    if (cPid == 0) {
        // Use execve to execute commands like ls, pwd, grep, and custom commands.
        // Display an error message if the command is not found.
        execvp(args[0], args);
        printf("Command not found\n");
        exit(1);
    } else if (cPid > 0) {
        // Wait for the termination of the process.
        int status;
        waitpid(cPid, &status, 0);
    } else {
        // Display an error message if the fork fails.
        printf("Fork failed");
    }
}

// Main function for the shell program.
int main(int argc, char **argv, char **envp) {
    int c;
    char *usrInput = NULL;
    size_t usrInputSize = 100;
    size_t inputIndex = 0;

    // Allocate memory for user input.
    usrInput = (char*)malloc(usrInputSize * sizeof(char));

    // Check for memory allocation errors and exit if encountered.
    if (usrInput == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    // Main loop to read user input character by character.
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '\n':
                // Parse and execute user input when a newline character is encountered.
                usrInput[inputIndex] = '\0'; // Null-terminate the string.
                char **tokens = tokenizer(usrInput);

                // If the first token is not empty/null, execute the corresponding command.
                if (tokens[0] != NULL) {
                    commandExe(tokens);
                    printf("[mysh#] ");
                }

                // Reset for the next input.
                inputIndex = 0;
                break;
            default:
                // Resize memory if needed for user input.
                if (inputIndex >= usrInputSize - 1) {
                    usrInputSize *= 2;
                    usrInput = realloc(usrInput, usrInputSize * sizeof(char));

                    // Check for memory reallocation errors and exit if encountered.
                    if (usrInput == NULL) {
                        printf("Memory reallocation error\n");
                        exit(1);
                    }
                }

                usrInput[inputIndex++] = c;
                break;
        }
    }
    return 0;
}

