#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define PAGE_SIZE 16

struct frame {
    int number;
    int age;
};

struct {
    int hit_cnt;
    int miss_cnt;
    int size;

    struct frame* frames;
} pager;


void init_pager() {
    pager.hit_cnt = 0;
    pager.miss_cnt = 0;
    pager.frames = (struct frame*)malloc(pager.size * sizeof(struct frame));
    for (int i = 0; i < pager.size; ++i) {
        pager.frames[i].number = 0;
        pager.frames[i].age = 0;
    }
}

int find_frame(int page_ref) {
    for (int i = 0; i < pager.size; ++i) {
        if (pager.frames[i].number == page_ref) {
            return i;
        }
    }
    return -1;
}

void replace_page(int page_ref) {
    int mn = INT32_MAX;
    int ind = 0;
    for (int i = 0; i < pager.size; i++) {
        if (pager.frames[i].age < mn) {
            mn = pager.frames[i].age;
            ind = i;
        }
    }
    pager.frames[ind].number = page_ref;
    pager.frames[ind].age = 0;
}

void check_hit(int page_ref) {
    int index = find_frame(page_ref);
    if (index == -1){
        pager.miss_cnt++;
        replace_page(page_ref);
    } else {
        pager.hit_cnt++;
    }
}

void use_page(int index) {
    for (int i = 0; i < pager.size; i++) {
        pager.frames[i].age >>= 1;
        if (pager.frames[i].number == index) {
            pager.frames[i].age |= 1 << (PAGE_SIZE - 1);
        }
    }
}

int main(){
    printf("Please, enter the number of page frames\n");
    scanf("%d", &pager.size);
    init_pager();

    int page_ref = 0;
    FILE *refs = fopen("input.txt", "r");
    fscanf(refs, "%d", &page_ref);
    while (!feof(refs)) {
        check_hit(page_ref);
        use_page(page_ref);
        fscanf(refs, "%d", &page_ref);
    }
    printf("Hit/Miss ration is: %d/%d\n", pager.hit_cnt, pager.miss_cnt);
    fclose(refs);
    return 0;
}
