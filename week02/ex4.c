#include <stdio.h>

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main() {
    int a, b;
    printf("Enter two values to swap: ");
    scanf("%d %d", &a, &b);
    swap(&a, &b);
    printf("Swapped: %d %d\n", a, b);
}
