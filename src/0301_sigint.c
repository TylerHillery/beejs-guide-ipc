#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int sig) {
    (void)sig; /* pretty sure this is just compiler workaround for unused var */
    const char msg[] = "Ahhh! SIGINT!\n";
    write(1, msg, sizeof msg - 1);
}

int main(void) {
    char s[200];
    struct sigaction sa = {
        .sa_handler = sigint_handler,
        .sa_flags = 0,
    };

    sigemptyset(&sa.sa_mask); /* what is this? */

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Enter a string:\n");

    if (fgets(s, sizeof(s), stdin) == NULL) {
        perror("fgets");
    } else {
        printf("You entered: %s\n", s);
    }

    return EXIT_SUCCESS;
}
