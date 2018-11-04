#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int input, output, n;
    off_t size, i;
    char buf;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <source> <destination>\n", argv[0]);
        exit(1);
    }

    if ((input = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(2);
    }

    if ((output = creat(argv[2], 0666)) < 0) {
        perror(argv[2]);
        exit(3);
    }

    if ((size = lseek(input, (off_t)0, SEEK_END)) < 0) {
        perror(argv[1]);
        exit(4);
    }

    for (i = size-1; i >= 0; i--) {
        if ((lseek(input, i, SEEK_SET)) < 0) {
            perror(argv[1]);
            exit(5);
        }

        if (read(input, &buf, 1) != 1) {
            perror(argv[1]);
            exit(6);
        }

        if (write(output, &buf, 1) != 1) {
            perror(argv[2]);
            exit(7);
        }
    }

    if (close(input) < 0) {
        perror(argv[1]);
        exit(8);
    }

    if (close(output) < 0) {
        perror(argv[2]);
        exit(9);
    }

    return 0;
}