#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct myList {
    struct elem *first;
};

struct elem {
    int number;
    struct elem *next;
};

struct myList* createList() {
    struct myList* list = (struct myList*) malloc(sizeof(struct myList));
    list -> first = 0;
    return list;
}

void add(struct myList* list, int num) {
    struct elem* new = (struct elem*) malloc(sizeof(struct elem));
    new -> number = num;
    new -> next = 0;
    if (list -> first == 0) {
        list -> first = new;
    } else {
        struct elem* temp = list -> first;
        while (temp -> next) {
            temp = temp -> next;
        }
        temp -> next = new;
    }
}

void delete(struct myList* list, int nr) {
    if (nr == 1) {
        struct elem* temp = list -> first;
        list -> first = temp -> next;
        free(temp);
    } else if (nr > 1) { 
        int counter = 1;
        struct elem* temp = list -> first;
        while (temp) {
            if (counter + 1 == nr) {
                break;
            }
            temp = temp -> next;
            counter++;
        }
        struct elem* del = temp -> next;
        temp -> next = temp -> next -> next;
        free(del);
    }
}

int get(struct myList* list, int nr) {
    if (nr > 0) {
        int counter = 0;
        struct elem* temp = list -> first;
        while (temp) {
            if (counter + 1 == nr) {
                break;
            }
            temp = temp -> next;
            counter++;
        }
        return temp -> number;
    } else {
        printf("Incorrect range!\n");
        return 0;
    }
}

void merge(struct myList* list1, struct myList* list2) {
    struct elem* temp = list1 -> first;
    while (temp -> next) {
        temp = temp -> next;
    }
    temp -> next = list2 -> first;
    free(list2);
}

int main(int argc, char const *argv[])
{
    struct myList* list1 = createList();
    struct myList* list2 = createList();
    struct myList* list3 = createList();

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
