#include <stdio.h>
#include <pthread.h>

#define N 10

typedef struct {
    int id;
    pthread_t thread;
} thread_info;

void* worker(void* args) {
    thread_info* thread = args;
    printf("Hello from thread %d\n", thread->id);
    pthread_exit(NULL);
}

int main() {
    thread_info threads[N];
    for (int i = 0; i < N; ++i) {
        threads[i].id = i;
        if (pthread_create(&threads[i].thread, NULL, worker, (void*)&threads[i]) != 0) {
            printf("Thread creation unsuccessful\n");
        }
        pthread_join(threads[i].thread, NULL);
    }
}
