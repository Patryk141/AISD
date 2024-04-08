#include <stdio.h>
#include <stdlib.h>

struct myQueue {
    int size;
    int number_of_elem;
    int* array;
};

struct myQueue* createQueue(int size) {
    struct myQueue* queue = (struct myQueue*) malloc(sizeof(struct myQueue));
    queue -> size = size;
    queue -> number_of_elem = 0;
    queue -> array = (int*) malloc(size * sizeof(int));
    return queue;
}

void add(struct myQueue* queue, int number) {
    if (queue -> number_of_elem != queue->size) {
        *(queue -> array + queue->number_of_elem) = number;
        queue -> number_of_elem++;
    } else {
        printf("Overflow!\n");
    }
}

int get(struct myQueue* queue) {
    if (queue -> number_of_elem != 0) {
        int number = *(queue->array);
        for (int i = 0; i < queue -> number_of_elem - 1 ; i++) {
            *(queue->array + i) = *(queue->array + i + 1);
        }
        queue -> number_of_elem--;
        *(queue -> array + queue -> number_of_elem) = 0;
        return number;
    } else {
        printf("No itemes! ");
        return 0;
    }
}

int main(int argc, char const *argv[]) {
    struct myQueue* queue = createQueue(100);

    printf("Added items:\n");
    for (int i = 0 ; i < 100 ; i++) {
        printf("%d\n", i);
        add(queue, i);
    }

    printf("Returned items:\n");
    for (int i = 0 ; i < 100 ; i++) {
        printf("%d\n", get(queue));
    }

    return 0;
}