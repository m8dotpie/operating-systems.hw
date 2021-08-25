#include <stdio.h>
#include <string.h>

// Reverses given string
void reverse(char* to_inverse) {
    size_t len = strlen(to_inverse);
    for (int i = 0; 2 * i + 1 < len; ++i) {
        int j = len - 1 - i; // inversed character index
        to_inverse[i] = to_inverse[i] ^ to_inverse[j]; // a = a ^ b
        to_inverse[j] = to_inverse[i] ^ to_inverse[j]; // b = a ^ b ^ b = a
        to_inverse[i] = to_inverse[i] ^ to_inverse[j]; // a = a ^ b ^ a = b
    }
}

int main() {
    char buffer[512];
    printf("Enter a string to reverse: ");
    scanf("%s", buffer);
    reverse(buffer);
    printf("Reversed string is: %s\n", buffer);
}
