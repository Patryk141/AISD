#include <stdio.h>
#include <stdlib.h>

struct myStack {
    int size;
    int number_of_elem;
    int* array;
};

struct myStack* createStack(int size) {
    struct myStack* stack = (struct myStack*) malloc(sizeof(struct myStack));
    stack -> size = size;
    stack -> number_of_elem = 0;
    stack -> array = (int*) malloc(size * sizeof(int));
    return stack;
}

void add(struct myStack* stack, int number) {
    if (stack -> number_of_elem != stack -> size) {
        stack -> array[stack -> number_of_elem] = number;
        stack -> number_of_elem++;
    } else {
        printf("Overflow!\n");
    }
}

int get(struct myStack* stack) {
    if (stack -> number_of_elem != 0) {
        int number = stack -> array[stack -> number_of_elem - 1];
        stack -> number_of_elem--;
        return number;
    } else {
        printf("No itemes! ");
        return 0;
    }
}

int main(int argc, char const *argv[]) {
    struct myStack* stack = createStack(100);

    printf("Added items:\n");
    for (int i = 0 ; i < 100 ; i++) {
        printf("%d\n", i);
        add(stack, i);
    }

    printf("Returned items:\n");
    for (int i = 0 ; i < 100 ; i++) {
        printf("%d\n", get(stack));
    }
    
    return 0;
}