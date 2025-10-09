/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** catch
*/

#include "my.h"

void handler(int signum)
{
    if (signum == SIGSEGV) {
        write(STDERR_FILENO, "Segmentation fault\n", 19);
        exit(SIGSEGV);
    } else if (signum == SIGABRT) {
        write(STDERR_FILENO, "Aborted (core dumped)\n", 22);
        exit(SIGABRT);
    }
    if (signum == SIGFPE) {
        write(STDERR_FILENO, "Floating point exception (core dumped)\n", 39);
        exit(SIGFPE);
    }
    if (signum == SIGILL) {
        write(STDERR_FILENO, "Illegal instruction (core dumped)\n", 34);
        exit(SIGILL);

    }
}

void catch_signaux(void)
{
    if (signal(SIGSEGV, handler) || signal(SIGTERM, handler) ||
        signal(SIGINT, handler) || signal(SIGABRT, handler) ||
        signal(SIGFPE, handler) || signal(SIGILL, handler)) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
}
