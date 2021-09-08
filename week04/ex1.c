#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int n = 7; // Creating the variable
    pid_t x = fork(); // We are forking our current process
    if (x < 0) {
        return EXIT_FAILURE;
    } else if (x == 0) {
        printf("Hello from child %d - n = %d\n", getpid(), n);
        // Every child will print the same result for n
        // The reason for that is that our fork is a clone
        // without mutations
    } else {
        printf("Hello from parent %d - n = %d\n", getpid(), n);
        // Parent has the same value for n as well
    }
}
