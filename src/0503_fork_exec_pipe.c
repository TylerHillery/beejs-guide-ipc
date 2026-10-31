#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pfds[2];

    if ((pipe(pfds)) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    switch ((fork())) {
    case -1: {
        perror("fork");
        return EXIT_FAILURE;
    }
    case -0: {
        /* child process */
        close(pfds[0]);
        if (dup2(pfds[1], STDOUT_FILENO) == -1) {
            perror("dups2");
            _exit(EXIT_FAILURE);
        }
        close(pfds[1]);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        _exit(EXIT_FAILURE);
    }
    default: {
        close(pfds[1]);
        if (dup2(pfds[0], STDIN_FILENO) == -1) {
            perror("dup2");
            return EXIT_FAILURE;
        }

        close(pfds[0]);
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp wc");
        return EXIT_FAILURE;
    }
    }
}