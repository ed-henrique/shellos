#include <stdio.h>
#include <stdlib.h>

void runShell(FILE* fp) {
    int commandMaxLength = 512;
    char* command = (char*) malloc(commandMaxLength * sizeof(char));

    while (fgets(command, commandMaxLength, fp) != NULL) {
        printf("RESULT:\n%s\n", command);
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
