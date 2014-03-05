#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv) {
    int c;
    int create_missing = 1;

    while ((c = getopt(argc, argv, "p:")) != -1) {
        switch (c) {
            case 'p':
                create_missing = 0;
                break;
            case '?':
                fprintf(stderr, "usage: %s [-p] path ...\n", argv[0]);
                return(1);
        }
    }

    if (argc < 2) {
        fprintf(stderr, "usage: %s [-p] path ...\n", argv[0]);
        return(1);
    }

    long size = pathconf(".", _PC_PATH_MAX);
    char root[size];
    getcwd(root, (size_t)size);
    for (char **arg = ++argv; *arg; ++arg) {
        chdir(root);
        if (strcmp(*arg, "-p") == 0) {
            continue;
        }
        if (create_missing == 0) {
            char *dir;
            dir = strtok(*arg, "/");
            while (dir != NULL) {
                if (mkdir(dir, 0777) == -1) {
                    if (errno == EEXIST) {
                        break;
                    } else {
                        perror(dir);
                        return(1);
                    }
                }
                chdir(dir);
                dir = strtok(NULL, "/");
            }
        } else {
            if (mkdir(*arg, 0777) == -1) {
                if (errno == EEXIST) {
                    break;
                } else {
                    perror(*arg);
                    return(1);
                }
            }
        }
    }
    return(0);
}
