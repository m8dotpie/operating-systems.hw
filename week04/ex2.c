#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
/*
 * As a result of a command pstree
 * I get a tree of all processes as 
 * subtree of a specified parent
 * So multiple calls will let me see
 * how processes are created and added
 * into the tree
 * */
int main() {
    for (int i = 0; i < 5; ++i) {
        fork();
    }
    sleep(5);
}
