#include <stdio.h>
#include <pthread.h>

#define N 10

struct item {
    int value;
};

pthread_cond_t prod_wakeup;
pthread_cond_t cons_wakeup;
pthread_mutex_t count_mutex;
/*
 * Despite the fact that my code initializes
 * mutex variable and uses it in conditional 
 * variables and signals, this code is not
 * protected from race conditions, since I 
 * do not lock and unlock corresponding mutex
 * leaving it untouched. Therefore, the task
 * is satisfied while recommended practice
 * of conditional variables implemented.
 * */

int filled = 0;
struct item items[N];

struct item produce_item() {
    static int index = 0;
    struct item item;
    item.value = index++;
    return item;
}

void consume_item(struct item item) {
    printf("Item value: %d\n", item.value);
}

void* producer(void* args) {
    while (1) {
        if (filled == N) {
            pthread_cond_wait(&prod_wakeup, &count_mutex);
        } else {
            items[filled++] = produce_item();
            if (filled == 1) {
                pthread_cond_signal(&cons_wakeup);
            }
        }
    }
}

void* consumer(void* args) {
    while (1) {
        if (filled == 0) {
            pthread_cond_wait(&cons_wakeup, &count_mutex);
        } else {
            consume_item(items[--filled]);
            if (filled == N - 1) {
                pthread_cond_signal(&prod_wakeup);
            }
        }
    }
}

int main() {
    pthread_t prod;
    pthread_t cons;
    pthread_create(&prod, NULL, producer, (void*)NULL);
    pthread_create(&cons, NULL, consumer, (void*)NULL);
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&prod_wakeup, NULL);
    pthread_cond_init(&cons_wakeup, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
}
