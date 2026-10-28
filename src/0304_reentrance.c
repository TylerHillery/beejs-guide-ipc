#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t count;

void sigint_handler(int sig) {
    (void)sig; /* pretty sure this is just compiler workaround for unused var */
    count = 123;
}

void increment(void) {
    int next_count = count + 1;

    printf("Count is %d, next should be %d\n", count, next_count);

    // Sleep to slow down time to demo the problem
    sleep(2);
    count++;

    if (count == next_count) {
        puts("Everything is swell!");
    } else {
        printf("%d != %d! Aaa! ERROR DOES NOT COMPUTE!\n", count, next_count);
    }
}

int main(void) {
    struct sigaction sa = {
        .sa_handler = sigint_handler,
        .sa_flags = 0,
    };

    sigemptyset(&sa.sa_mask); /* what is this? */

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    increment();

    return EXIT_SUCCESS;
}
