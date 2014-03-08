#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
    int i;
    FILE *file;
    extern void process(FILE *file);

    if (argc == 1) {
        process(stdin);
    } else {
        for (i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-") == 0) {
                process(stdin);
            } else if ((file = fopen(argv[i], "r")) == NULL) {
                perror(argv[i]);
                return(1);
            } else {
                process(file);
                fclose(file);
            }
        }
    }
    return(0);
}


void process(FILE *file) {
    int ch;
    while ((ch = getc(file)) != EOF) {
        if (ch == '>') {
            while ((ch = fgetc(file)) != EOF) {
                if (ch == '<') {
                    break;
                }
                putchar(ch);
            }
        }
    }
}
