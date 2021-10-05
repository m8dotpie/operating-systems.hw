#include <stdio.h> 
#include <stdlib.h>
int main() {
    char **s = (char**)malloc(256 * sizeof(char*));
    char foo[] = "Hello World"; 
    *s = foo;
    printf("s is %s\n", *s);
    s[0] = foo;
    printf("s[0] is %s\n",s[0]); return(0);
}
