#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/resource.h>

#define SIZE 2000 * 1024 * 1024

/*
 * The output I get shows that my operating system
 * actually does not allow allocating memory starting
 * from some point and ignores any further calls.
 * Reducing the amount of memory allocated works just
 * as it was intended to be.
 * */

int main() {
    for (int i = 0; i < 10; ++i) {
        char* a = (char*)malloc(SIZE * sizeof(char));
        memset(a, 0, SIZE);
        int who = RUSAGE_SELF;
        struct rusage u;
        int r = getrusage(who, &u);
        printf("Memory usage %ld\n", u.ru_maxrss);
        sleep(1);
    }
}
