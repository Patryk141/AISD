#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct elem {
    int number;
    struct elem *previous, *next;
};

struct elem *createList() {
    struct elem *list = (struct elem *) malloc(sizeof(struct elem));
    return list;
}

void add(struct elem *list, int num) {
    if (list -> next == 0) {
        list -> number = num;
        list -> next = list;
        list -> previous = list;
    } else {
        struct elem *new = (struct elem *) malloc(sizeof(struct elem));
        new -> number = num;
        struct elem *temp = list -> previous;
        temp -> next = new;
        new -> next = list;
        new -> previous = temp;
        list -> previous = new;
    }
}

void delete(struct elem *list, int nr) {
    if (nr > 0) {
        struct elem *temp = list;
        int counter = 1;
        while (nr != counter) {
            temp = temp -> next;
            counter++;
        }
        temp -> previous -> next = temp -> next;
        temp -> next -> previous = temp -> previous;
        free(temp);
    } else {
        printf("Incorrect range!\n");
    }
}

int get(struct elem *list, int nr) {
    if (nr > 0) {
        struct elem *temp = list;
        int counter = 1;
        while (nr != counter) {
            temp = temp -> next;
            counter++;
        }
        return temp -> number;
    } else {
        printf("Incorrect range!\n");
        return 0;
    }
}

void merge(struct elem *list1, struct elem *list2) {
    struct elem *temp1 = list1 -> previous;
    struct elem *temp2 = list2 -> previous;
    temp1 -> next = list2;
    list2 -> previous = temp1;
    temp2 -> next = list1;
    list1 -> previous = temp2;
}

int main(int argc, char const *argv[]) {
    struct elem *list1 = createList();
    struct elem *list2 = createList();
    struct elem *list3 = createList();
    
    for (int i = 0 ; i < 100000 ; i++) {
        add(list1, i);
    }

    clock_t t = clock();
    double time_taken, sum = 0;
    srand(time(NULL));
    int r = rand()%10000;

    for (int i = 0 ; i < 100 ; i++) {
        t = clock();
        get(list1, 10000);
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC;
        sum += time_taken;
    }

    printf("Average access time to element 10000 %lf sec\n", sum/100);
    sum = 0;

    for (int i = 0 ; i < 100 ; i++) {
        t = clock();
        get(list1, r);
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC;
        r = rand()%10000;
        sum += time_taken;
    }
    printf("Average access time to random element %lf sec\n", sum/100);

    for (int i = 0 ; i < 10 ; i++) {
        add(list2, i);
        add(list3, i+100);
    }

    merge(list2, list3);
    printf("List after merger:\n");
    for (int i = 0 ; i < 20 ; i++) {
        printf("%d\n", get(list2, i + 1));
    }

    return 0;
}
