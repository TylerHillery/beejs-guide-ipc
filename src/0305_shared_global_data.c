#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t got_usr1;

void sigusr1_handler(int sig) {
    (void)sig;
    got_usr1 = 1;
}

int main(void) {
    struct sigaction sa = {
        .sa_handler = sigusr1_handler,
        .sa_flags = 0,
    };
    sigemptyset(&sa.sa_mask);

    got_usr1 = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (!got_usr1) {
        printf("PID %d: working hard...\n", getpid());
        sleep(1);
    }

    printf("Done in by SIGUSR1!\n");

    return EXIT_SUCCESS;
}
