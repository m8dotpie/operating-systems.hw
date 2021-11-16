#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);

    int proc_cnt, res_cnt;
    scanf("%d%d", &proc_cnt, &res_cnt);

    int E[res_cnt], A[res_cnt], C[proc_cnt][res_cnt], R[proc_cnt][res_cnt];
    int terminated[proc_cnt];

    for (int i = 0; i < res_cnt; ++i) {
        scanf("%d", &E[i]);
    }
    for (int i = 0; i < res_cnt; ++i) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < proc_cnt; ++i) {
        terminated[i] = 0;
        for (int j = 0; j < res_cnt; ++j) {
            scanf("%d", &C[i][j]);
        }
    }
    for (int i = 0; i < proc_cnt; ++i) {
        for (int j = 0; j < res_cnt; ++j) {
            scanf("%d", &R[i][j]);
        }
    }

    int deadlock = 0;
    while (proc_cnt && !deadlock) {
        deadlock = 1;
        for (int i = 0; i < proc_cnt; ++i) {
            if (terminated[i]) {
                continue;
            }
            int block = 0;
            for (int j = 0; j < res_cnt; ++j) {
                if (C[i][j] + A[j] < R[i][j]) {
                    block = 1;
                }
            }
            if (!block) {
                deadlock = 0;
                for (int j = 0; j < res_cnt; ++j){
                    A[j] += C[i][j];
                }
                terminated[i] = 1;
                break;
            } 
        }
    }

    int cnt = 0;
    for (int i = 0; i < proc_cnt; ++i) {
        if (!terminated[i]) {
            cnt++;
            printf("Process %d deadlocked\n", i);
        }
    }
    printf("Number of deadlocked processes: %d\n", cnt);
}
