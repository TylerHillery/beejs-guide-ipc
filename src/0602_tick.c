#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define FIFO_NAME "american_maid"

int main(void) {
    char s[300];
    int fd;
    ssize_t num;

    mkfifo(FIFO_NAME, 0644);
    printf("waiting for writers...\n");
    fd = open(FIFO_NAME, O_RDONLY);
    printf("got a writer\n");

    do {
        if ((num = read(fd, s, sizeof s - 1)) == -1) {
            perror("read");
        } else {
            s[num] = '\0';
            s[strcspn(s, "\n")] = '\0';
            printf("tic: read %zd bytes: \"%s\"\n", num, s);
        }
    } while (num > 0);

    return EXIT_SUCCESS;
}
