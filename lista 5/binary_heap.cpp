#include <iostream>
#include <algorithm>
#include <cmath>

struct node {
    int priority;

    node(int priority) {
        this->priority = priority;
    }
};

int counter_compare = 0;

struct binary_heap {
    node* a;
    int size;
    int capacity;

    int left(int i) {
        return 2*i + 1;
    }

    int right(int i) {
        return 2*(i + 1);
    }

    int parent(int i) {
        return (i - 1)/2;
    }

    int min(int i, int l, int r) {
        int min = i;
        counter_compare++;
        if (l < size) {
            counter_compare++;
            if (a[min].priority > a[l].priority) {
                min = l;
            }
        }
        counter_compare++;
        if (r < size) {
            counter_compare++;
            if (a[min].priority > a[r].priority) {
                min = r;
            }
        }
        return min;
    }

    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = min(i, l, r);
        counter_compare++;
        if (largest != i) {
            std::swap(a[i], a[largest]);
            heapify(largest);
        }
    }

    void insert(node key) {
        size++;
        int i = size - 1;
        while (i > 0 && a[parent(i)].priority > key.priority) {
            counter_compare++;
            a[i] = a[parent(i)];
            i = parent(i);
        }
        a[i] = key;
    }

    node minimum() {
        return a[0];
    }

    node extract_min() {
        counter_compare++;
        if (size < 1) {
            return node(-1);
        } else {
            node min = a[0];
            a[0] = a[size - 1];
            size--;
            heapify(0);
            return min;
        }
    }

    void increase_key(int i, int priority) {
        a[i].priority = priority;
        heapify(i);
    }

    void delete_key(int i) {
        a[i] = a[size];
        size--;
        heapify(i);
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << a[i].priority << " ";
        }
        std::cout << "\n";
    }

    binary_heap(int capacity) {
        a = (node*)malloc(capacity*sizeof(node));
        this->size = 0;
        this->capacity = capacity;
    }
};

binary_heap heap_union(binary_heap q1, binary_heap q2) {
    for (int i = 0; i < q2.size; i++) {
        q1.a[i + q1.size] = q2.a[i];
    }

    q1.size += q2.size;

    for (int i = (int)floor(q1.size/2); i > 0; i--) {
        q1.heapify(i - 1);
    }

    return q1;
}

int main(int argc, char const *argv[]) {
    binary_heap q1 = binary_heap(20000);
    binary_heap q2 = binary_heap(20000);

    int n;
    std::cin >> n;
    
    std::cout << "Elementy pierwszego kopca: " << std::endl;

    for (int i = 0; i < n/2; i++) {
        int temp;
        std::cin >> temp;
        std::cout << temp << " ";
        q1.insert(temp);
    }

    std::cout << "\nElementy drugiego kopca: " << std::endl;

    for (int i = n/2; i < n; i++) {
        int temp;
        std::cin >> temp;
        std::cout << temp << " ";
        q2.insert(temp);
    }

    counter_compare = 0;

    // for (int i = 0; i < n; i++) {
    //     q1.extract_min();
    //     // std::cout  << n << " " <<  i << " " << counter_compare << std::endl;
    //     // counter_compare = 0;
    // }

    q1 = heap_union(q1, q2);

    // std::cout  << n/2 << " " << counter_compare << std::endl;

    std::cout << "\nExtract min po wykonaniu operacji union na kopcach:" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << q1.extract_min().priority << " ";
    }

    std::cout << "\n";

    return 0;
}
