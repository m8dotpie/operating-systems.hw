#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int active = 1;
    while (active) {
        printf("> ");
        char *cmd;
        scanf("%s", cmd);
        if (!strcmp(cmd, "exit")) {
            active = 0;
            continue;
        } else {
            system(cmd);
        }
    }
}
