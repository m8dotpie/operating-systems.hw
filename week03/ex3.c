#include <stdio.h>
#include <stdlib.h>

struct Node {
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
            current->next = newNode;
            newNode->value = value;
        }
    }
}

void delete_node(int index) {
    if (index >= size) {
        return;
    }
    if (index == 0) {
        if (begin != NULL) {
            struct Node* temp = begin;
            begin = begin->next;
            free(temp);
        }
        return;
    }
    struct Node *current = begin;
    int current_index = 0;
    while (current_index != index - 1) {
        current = current->next;
        current_index++;
    }
    if (current->next == end) {
        free(end);
        end = current;
        current->next = NULL;
    } else {
        struct Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
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
