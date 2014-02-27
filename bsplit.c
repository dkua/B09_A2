#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int amount = 10;
    FILE *file;
    FILE *new_file;
    int c;

    if (argc < 2) {
        fprintf(stderr, "usage: %s [file] [option]\n", argv[0]);
        return 1;
    } else if (argc >= 2) {
        while (--argc > 0 && (*++argv)[0] == '-') {
            while ((c = *++argv[0])) {
                switch (c) {
                    case 'b':
                        amount = *argv[argc];
                        break;
                }
            }
        }
    }

    unsigned char buffer[amount];

    file = fopen(argv[1], "rb");
    fread(buffer, sizeof(buffer)+1, 1, file);

    new_file = fopen("xaa", "wb");
    fwrite(buffer, sizeof(buffer)+1, 1, new_file);

    return 0;
}
