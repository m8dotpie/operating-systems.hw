#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *prev;
    struct Node *next;
    int value;
};

struct Node *begin = NULL;
struct Node *end = NULL;
int size = 0;

void print_list() {
    struct Node *current = begin;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void __append(int value) {
    if (end == NULL || begin == NULL) {
        begin = end = (struct Node*)malloc(sizeof(struct Node));
    } else {
        end->next = (struct Node*)malloc(sizeof(struct Node));
        end->next->prev = end;
        end = end->next;
    }
    end->value = value;
    return;
}

void insert_node(int value, int before) {
    size++;
    if (end == NULL || begin == NULL) {
        __append(value);
    } else {
        struct Node* current = begin;
        while (current != NULL && current->value != before) {
            current = current->next;
        } 
        if (current == NULL) {
            __append(value);
        } else if (current->next == NULL) {
            __append(value);
        } else {
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            newNode->value = value;
        }
    }
}

void delete_node(int index) {
    if (index >= size) {
        return;
    }
    struct Node *current = begin;
    int current_index = 0;
    while (current_index != index) {
        current = current->next;
        current_index++;
    }
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        begin = NULL;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        end = NULL;
    }
    free(current);
}

int main() {
    insert_node(3, 0);
    print_list();
    insert_node(4, 3);
    print_list();
    insert_node(5, 4);
    print_list();
    delete_node(1);
    print_list();
    delete_node(1);
    print_list();
    delete_node(0);
    print_list();
}
