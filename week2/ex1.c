#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int i = INT_MAX;
    float f = FLT_MAX;
    double d = DBL_MAX;

    printf("Integer size: %lu\nInteger max value: %d\n", sizeof(i), i);
    printf("Float size: %lu\nFloat max value: %f\n", sizeof(f), f);
    printf("Double size: %lu\nDouble max value: %lf\n", sizeof(f), f);
}
