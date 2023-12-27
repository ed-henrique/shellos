#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void runShell(FILE* fp) {
    int commandMaxLength = 512;
    char* command = (char*) malloc(commandMaxLength * sizeof(char));

    printf("> ");

    while (fgets(command, commandMaxLength, fp) != NULL) {
        command[strcspn(command, "\r\n")] = 0;

        if (!strcmp(command, "exit") || !strcmp(command, "quit")) {
            exit(0);
        }

        if (!strlen(command)) {
            continue;
        }

        int argLimit = 0;

        for (int i = 0; i < strlen(command); i++) {
            if (command[i] == ' ') {
                argLimit++;
            }
        }

        argLimit++;

        int i = 0;
        char** arguments = (char**) malloc(sizeof(char*) * (argLimit + 1));
        char* token = strtok(command, " ");

        do {
            asprintf(&arguments[i++], "%s", token);
            token = strtok(NULL, " ");
        } while (token != NULL);

        arguments[argLimit] = NULL;

        pid_t pid = fork();

        if (pid == -1) {
            fprintf(stderr, "Could not fork child!\n");
            exit(1);
        } else if (pid == 0) {
            if (execvp(arguments[0], arguments) < 0) {
                fprintf(stderr, "Could not execute command!\n");
                exit(1);
            }
        } else {
            wait(NULL);
        }

        printf("\n> ");
        free(token);
        free(arguments);
    }

    free(command);
    printf("\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    switch (argc) {
    case 1:
        runShell(stdin);
        break;
    case 2:
        FILE* fp = fopen(argv[1], "r");

        if (fp == NULL) {
            fprintf(stderr, "Could not open file!\n");
            exit(1);
        }

        runShell(fp);
        break;
    default:
        fprintf(stderr, "Passed %d arguments, but only one is supported!\n", argc - 1);
        exit(1);
    }

    return 0;
}
