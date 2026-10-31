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

    mkfifo(FIFO_NAME, 0644);

    printf("waiting for readers...\n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("got a read--type some stuff\n");

    while (fgets(s, sizeof(s), stdin) != NULL) {
        ssize_t num = write(fd, s, strlen(s));
        if (num == -1) {
            perror("write");
        } else {
            printf("speak: wrote %zu bytes\n", num);
        }
    }

    return EXIT_SUCCESS;
}