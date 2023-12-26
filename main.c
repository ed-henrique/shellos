#include <stdio.h>
#include <stdlib.h>

void runShell() {
    while (1) {
        printf("> ");

        int commandMaxLength = 512;
        char* command = (char*) malloc(commandMaxLength * sizeof(char));

        fgets(command, commandMaxLength, stdin);

        printf("%s", command);
        free(command);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        runShell();
    }

    return 0;
}
