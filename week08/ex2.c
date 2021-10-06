#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

#define SIZE 2000 * 1024 * 1024

/* VM_STAT Comment
 * This predefined size was enough to 
 * make the system to load the data to the
 * disk, since to the tenth operation the 
 * size of allocated memory exceeds twenty GB
 * while I have only 8 GB of RAM. However, 
 * so is zero, since memory is never accessed.
 * */

int main() {
    for (int i = 0; i < 10; ++i) {
        char* a = (char*)malloc(SIZE * sizeof(char));
        memset(a, 0, SIZE);
        sleep(1);
    }
}
