#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void runShell(FILE* fp) {
    const int argLimit = 25;
    int commandMaxLength = 512;
    char* command = (char*) malloc(commandMaxLength * sizeof(char));

    while (fgets(command, commandMaxLength, fp) != NULL) {
        int i = 0;
        char* path;
        char* arguments[argLimit];
        command[strcspn(command, "\r\n")] = 0;
        char* token = strtok(command, " ");

        asprintf(&path, "/bin/%s", token);

        while (token != NULL) {
            token = strtok(NULL, " ");
            asprintf(&arguments[i++], "%s", token);
        }

        if (fork() == 0) {
            if (i > 1) {
                execl(path, command, arguments, NULL);
            } else {
                execl(path, command, NULL);
            }
        }

        printf("\n");
        free(path);
        free(token);
    }

    free(command);
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
