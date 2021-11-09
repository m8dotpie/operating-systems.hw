#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <inttypes.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

#define BINDS_CNT 3

struct bind {
    char *msg;
    char *name;
    unsigned int *keys;
    unsigned int hotkey_len;
};

void init_binds(struct bind* binds) {
    binds[0].msg = "I passed the exam!";
    binds[1].msg = "Get some cappucino!";
    binds[2].msg = "I love operating systems course!";

    binds[0].hotkey_len = 2;
    binds[1].hotkey_len = 3;
    binds[2].hotkey_len = 3;

    binds[0].keys = malloc(2 * sizeof(unsigned int));
    binds[1].keys = malloc(3 * sizeof(unsigned int));
    binds[2].keys = malloc(2 * sizeof(unsigned int));

    binds[0].keys[0] = 25;
    binds[0].keys[1] = 46;

    binds[1].keys[0] = 46;
    binds[1].keys[1] = 30;
    binds[1].keys[2] = 25;

    binds[2].keys[0] = 18;
    binds[2].keys[1] = 21;
    binds[2].keys[2] = 24;

    binds[0].name = "P + C";
    binds[1].name = "C + A + P";
    binds[2].name = "I + L + O";
}

int main() {
    struct bind binds[BINDS_CNT];
    init_binds(binds);

    int k_link = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    FILE *fout = fopen("ex3.txt", "w");

    if (k_link < 0) {
        printf("Could not read keyboard events symlink.");
        fprintf(fout, "Could not read keyboard events symlink.");
        return 1;
    }

    for (int i = 0; i < BINDS_CNT; ++i) {
        printf("%s -> \"%s\"\n", binds[i].name, binds[i].msg);
    }


    unsigned int *bind_code = malloc(6 * sizeof(unsigned int));
    unsigned int bind_size = 0;
    int reading = 1;

    while (reading) {
        struct input_event event;
        read(k_link, &event, sizeof(struct input_event));

        if (event.type != 1) {
            continue;
        }

        if (event.value == 1) {
            bind_code[bind_size++] = event.code;

            for (int i = 0; i < BINDS_CNT; ++i) {
                if (binds[i].hotkey_len == bind_size) {
                    int differs = 0;

                    for (int k = 0; k < bind_size; ++k) {
                        if (binds[i].keys[k] != bind_code[k]) {
                            differs = 1;
                            break;
                        }
                    }

                    if (!differs) {
                        printf("%s\n", binds[i].msg);
                        fprintf(fout, "%s\n", binds[i].msg);
                    }
                }
            }
        } else if (event.value == 0) {
            memset(bind_code, 0, 6 * sizeof(unsigned int));
            bind_size = 0;
        }
        fflush(stdout);
    }
}
