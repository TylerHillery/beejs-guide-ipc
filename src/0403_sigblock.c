#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
    sigset_t mask, oldmask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    puts("Try to ^C out of here! You can't for 5 seconds!");
    sleep(5);

    puts("Ok, now you can.");
    sigprocmask(SIG_SETMASK, &oldmask, NULL);

    puts("If you hit ^C, this won't print.");
}