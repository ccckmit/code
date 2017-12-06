#include <signal.h>
#include <stdio.h>
#include <windows.h>

void sig_int(int sig) {
    printf("catch a termination signal.\n");
}

int main() {
    signal(SIGINT, &sig_int);
    Sleep(1000*10);
    return 0;
}
