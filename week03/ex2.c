#include <stdio.h>

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void bubble_sort(int *a, int n, int (*cnt)(int, int)) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[i]) {
                swap(&a[i], &a[j]);
            }
        }
    }
}

void print_arr(int *arr, int n) {
    for (int i = 0; i < 10; ++i) {
        printf("%d\n", arr[i]);
    }
}

int cmp(int a, int b) {
    return a < b;
}

int main() {
    int a[10] = {3, 4, 5, 1, 1, 0, -1, -10, 5, -100};
    print_arr(a, 10);
    bubble_sort(a, 10, &cmp);
    print_arr(a, 10);
}
