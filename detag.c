#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *file;

    if (argc < 2) {
        fprintf(stderr, "usage: %s file [-b bytes]\n", argv[0]);
        return(1);
    }

    for (char **arg = ++argv; *arg; ++arg) {
        if ((file = fopen(*arg, "r")) == NULL) {
            perror(*arg);
            return(1);
        }

        char ch;
        int nonempty;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '>') {
                nonempty = 0;
                while ((ch = fgetc(file)) != EOF) {
                    if (ch == '<') {
                        if (nonempty != 0) {
                            printf("\n");
                        }
                        break;
                    }
                    if (ch != '\n') {
                        printf("%c", ch);
                        nonempty = 1;
                    }
                }
            }
        }
    }

    return(0);
}

