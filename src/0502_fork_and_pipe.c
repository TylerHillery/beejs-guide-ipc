#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pfds[2];
    char buf[30];

    if ((pipe(pfds)) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (!fork()) {
        printf(" CHILD: writing to the pipe\n");
        write(pfds[1], "test", 5);
        exit(EXIT_SUCCESS);
    } else {
        printf("PARENT: reading from pipe\n");
        read(pfds[0], buf, 5);
        printf("PARENT: read\"%s\"\n", buf);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}