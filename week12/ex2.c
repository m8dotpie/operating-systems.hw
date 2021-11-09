#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

int main() {
    int k_link = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    FILE *fout = fopen("ex2.txt", "w");

    if (k_link < 0) {
        printf("Could not read keyboard events symlink.");
        fprintf(fout, "Could not read keyboard events symlink.");
        return 1;
    }

    int reading = 1;

    while (reading) {
        struct input_event event;
        read(k_link, &event, sizeof(struct input_event));

        if (event.type != 1) {
            continue;
        }

        if (event.value == 1) {
            fprintf(fout, "PRESSED 0x%X (%d)\n", event.code, event.code);
            printf("PRESSED 0x%X (%d)\n", event.code, event.code);
        } else if (event.value == 0) {
            fprintf(fout, "RELEASED 0x%X (%d)\n", event.code, event.code);
            printf("RELEASED 0x%X (%d)\n", event.code, event.code);
        }

        fflush(stdout);
    }
}
