#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int c;
    int amount = 10;
    FILE *file;

    while ((c = getopt(argc, argv, "b:")) != -1) {
        switch (c) {
            case 'b':
                amount = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "usage: %s file [-b bytes]\n", argv[0]);
                return(1);
        }
    }

    if (argc < 2) {
        fprintf(stderr, "usage: %s file [-b bytes]\n", argv[0]);
        return(1);
    }

    if ((file = fopen(argv[1], "rb")) == NULL) {
        perror(argv[1]);
        return(1);
    }

    char name[4] = {'x', 'a', 'a', '\0'};
    int numfiles = 0;
    while (1) {
        char buffer[amount];
        FILE *newfile;
        if (fread(buffer, sizeof(buffer), 1, file) == 0) {
            break;
        }
        if (numfiles < 676) {
            name[1] = numfiles / 26 + 'a';
            name[2] = numfiles % 26 + 'a';
        } else {
            break;
        }
        if ((newfile = fopen(name, "wb")) == NULL) {
            perror(name);
            exit(1);
        }
        fwrite(buffer, sizeof(buffer), 1, newfile);
        fclose(newfile);
        numfiles++;
    }

    fclose(file);

    return(0);
}
