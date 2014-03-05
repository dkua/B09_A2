#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
        while (!feof(file)) {
            ch = fgetc(file);
            if ((ch == '>') && (ch != EOF)) {
                ch = fgetc(file);
                while ((ch != '<') && (ch != EOF)) {
                    if (!isspace(ch)) {
                        printf("%c", ch);
                    }
                    ch = fgetc(file);
                    if (ch == '<') {
                        printf("\n");
                    }
                }
            }
        }
    }

    return(0);
}
