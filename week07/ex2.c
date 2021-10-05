#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int *a = (int*)malloc(n * sizeof(n));
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        printf("%d ", a[i]);
    }
    free(a);
}
