#include <stdio.h>
#include <memory.h>

void rsu_triangle(int n) {
    for (int i = 0; i < n; ++i) {
        int spaces_cnt = (n - i - 1);
        char line[2 * n];
        memset(line, 0, 2 * n);
        memset(line, 32, 2 * n - 1);
        memset(line + spaces_cnt, 42, 2 * i + 1);
        printf("%s\n", line);
    }
}

void square(int n) {
    for (int i = 0; i < n; ++i) {
        char line[n + 1];
        memset(line, 0, n + 1);
        memset(line, 42, n);
        printf("%s\n", line);
    }
}

void rsl_triangle(int n) {
    for (int i = 0; i < n; ++i) {
        char line[n + 1];
        memset(line, 0, n + 1);
        memset(line, 42, i + 1);
        printf("%s\n", line);
    }
}

void rsr_triangle(int n) {
    for (int i = 0; i < n; ++i) {
        char line[n + 1];
        memset(line, 0, n + 1);
        if (n & 1 && n / 2 == i) {
            memset(line, 42, n / 2 - 1);
        }
        if (i < n / 2) {
            memset(line, 42, i + 1);
        } else {
            memset(line, 42, n - i);
        }
        printf("%s\n", line);
    }
}

int main(int argc, char** argv) {
    int n, type;
    sscanf(argv[1], "%d", &n); // Read number from arguments
    sscanf(argv[2], "%d", &type); // Read number from arguments
    if (type == 1) {
        rsu_triangle(n);
    } else if (type == 2) {
        square(n);
    } else if (type == 3) {
        rsl_triangle(n);
    } else if (type == 4) {
        rsr_triangle(n);
    } 
}
