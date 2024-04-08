#include <iostream>
#include <math.h> 

int counter_compare = 0;
int counter_swap = 0;
int n = 0;
int w;

void insertion_sort(int *a, int p, int q) {
    for (int j = p + 1 ; j < q + 1 ; j++) {
        int key = a[j];
        int i = j - 1;
        counter_compare++;
        while (i >= p && *(a + i) > key) {
            counter_swap++;
            *(a + i + 1) = *(a + i);
            i--;
            counter_compare++;
        }
        counter_swap++;
        *(a + i + 1) = key;
    }
}

int partition(int *A, int p, int q, int x) {
    int i = p;
    int tmp = -1;
    while (tmp < 0 && i < q) {
        counter_compare++;
        if (*(A + i) > x) {
            tmp = *(A + i);
        } else {
            i++;
        }
    }
    int index_pivot = i;
    for (int j = i + 1 ; j <= q ; j++) {
        counter_compare++;
        if (*(A + j) <= x) {
            i++;
            counter_swap++;
            std::swap(*(A + i), *(A + j));
        }
    }
    counter_swap++;
    std::swap(*(A + i), *(A + index_pivot));
    return i;
}

int Select(int *A, int p, int q, int i) {
    // counter_compare++;
    if (p == q) {
        return *(A + p);
    }
    int quantity = ceil((q - p + 1.0)/w);
    int *M = new int[quantity];
    for (int j = 0 ; j < quantity - 1 ; j++) {
        insertion_sort(A, p + j*w, p + (j + 1)*w - 1);
        *(M + j) = *(A + p + j*w + w/2);
    }
    int j = quantity - 1;
    insertion_sort(A, p + j*w, q);
    *(M + j) = *(A + (int)ceil((p + j*w + q)/2.0));
    int x = Select(M, 0, quantity - 1, ceil(quantity/2.0));
    int k = partition(A, p, q, x);
    counter_compare++;
    if (i==k) return x;
    else if (i < k) return Select(A, p, k - 1, i);
    else return Select(A, k, q, i);
}

int main(int argc, char const *argv[]) {
    w = std::stoi(*(argv + 1));
    std::string arg = *(argv + 2);
    std::cin >> n;
    int k;
    std::cin >> k;
    int *A = new int[n];
    for (int i = 0 ; i < n ; i++) {
        std:: cin >> *(A + i);
    }

    if (arg == "print") {
        if (n < 50) {
            std::cout << "Tablica początkowa:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(A + i) << " ";
            }
            int result = Select(A, 0, n - 1, k);
            std::cout << "\nTablica końcowa:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(A + i) << " ";
            }
            insertion_sort(A, 0, n - 1);
            std::cout << "\nPosortowana tablica:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(A + i) << " ";
            }
            std::cout << "\n---------------------" << std::endl;
            std::cout << k << " statystyka pozycyjna: " << result << std::endl;
        } else {
            Select(A, 0, n - 1, k);
            std::cout << "Liczba porównań: " << counter_compare << std::endl;
            std::cout << "Liczba przestawień: " << counter_swap << std::endl;
        }
    } else if (arg == "save") {
        Select(A, 0, n - 1, k);
        std::cout << counter_compare  << "; " << counter_swap << "; " << n << std::endl;
    }
    return 0;
}