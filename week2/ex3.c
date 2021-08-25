#include <stdio.h>
#include <memory.h>

int main(int argc, char** argv) {
    int n;
    sscanf(argv[1], "%d", &n); // Read number from arguments
    for (int i = 0; i < n; ++i) {
        int spaces_cnt = (n - i - 1); // Number of spaces on current line
        char line[2 * n]; // One extra symbol as terminator
        memset(line, 0, 2 * n); // Clearing initial memory
        memset(line, 32, 2 * n - 1); // Writing spaces everywhere
        memset(line + spaces_cnt, 42, 2 * i + 1); // Writing asterisks where necessary
        printf("%s\n", line); // Printing picture line by line
    }
}
