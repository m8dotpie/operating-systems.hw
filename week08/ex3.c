#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/resource.h>

#define SIZE 2000 * 1024 * 1024

/* TOP Comment
 * Top is a very handy tool to visualize the values
 * of the used memory, so it is easy to see that
 * the used memory size is increasing every second
 * to the corresponding value, exceeding the value
 * of avaiable physical memory and unloading to 
 * dynamically resized swap.
 * */

int main() {
    for (int i = 0; i < 10; ++i) {
        char* a = (char*)malloc(SIZE * sizeof(char));
        memset(a, 0, SIZE);
        sleep(1);
    }
}
