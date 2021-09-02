#include <stdio.h>

void print_arr(int *arr, int n);

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void quick_sort(int *a, int n, int (*cmp)(int, int)) {
    if (n == 2) {
        if (!cmp(a[0], a[1])) {
            swap(&a[0], &a[1]);
        }
    }
    if (n <= 2) {
        return;
    }
    int m = n / 2;
    int la[n], ra[n];
    int it1 = 0, it2 = 0;
    for (int i = 0; i < n; ++i) {
        if (cmp(a[i], a[m]) || a[i] == a[m]) {
            la[it1++] = a[i];
        } else {
            ra[it2++] = a[i];
        }
    }
    if (it1 != n && it2 != n) {
        quick_sort(la, it1, cmp);
        quick_sort(ra, it2, cmp);
    }
    for (int i = 0; i < n; ++i) {
        if (i < it1) {
            a[i] = la[i];
        } else {
            a[i] = ra[i - it1];
        }
    }
    return;
}

void print_arr(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int cmp(int a, int b) {
    return a < b;
}

int main() {
    int a[10] = {3, 4, 5, 1, 1, 0, -1, -10, 5, -100};
    print_arr(a, 10);
    quick_sort(a, 10, &cmp);
    print_arr(a, 10);
}
