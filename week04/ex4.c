#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*
 * This function splits the given string into
 * the set of words using spaces as delimeters
 * */
char** split(char* raw_cmd) {
    char** res = malloc(256 * sizeof(char*));
    int i = 0;
    res[i] = strtok(raw_cmd, " ");
    while (res[i] != NULL) {
        res[++i] = strtok(NULL, " ");
    }
    return res;
}

int main() {
    int active = 1;
    while (active) {
        printf("> ");
        char *raw_cmd;
        scanf("%[^\n]%*c", raw_cmd);
        char **cmd = split(raw_cmd);
        if (!strcmp(cmd[0], "exit")) {
            active = 0;
            continue;
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                if (execvp(cmd[0], cmd)) {
                    active  = 0;
                    printf("Command not found: %s\n", cmd[0]);
                    // Deactivate dead or invalid forks
                }
            }
        }
        wait(NULL);
        // We wait in order not to mess with the prompt
        // Since the result of the child can appear after
        // the prompt ("> ") was printed, the shell 
        // becomes a mess, so only way to fix this is
        // to make the prompt wait for a child process to finish
        // This fix is task specific since we execute everything
        // in the background
    }
}
