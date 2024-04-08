#include <iostream>
#include <algorithm>
#include <math.h> 

int counter_swap = 0;
int counter_compare = 0;
std::string arg;
int n = 0;

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
            std::swap(*(A + i), *(A + j));
        }
    }
    std::swap(*(A + i), *(A + index_pivot));
    return i;
}

int Select(int *A, int p, int q, int i) {
    counter_compare++;
    if (p == q) {
        return *(A + p);
    }
    int quantity = ceil((q - p + 1.0)/5);
    int *M = new int[quantity];
    for (int j = 0 ; j < quantity - 1 ; j++) {
        insertion_sort(A, p + j*5, p + (j + 1)*5 - 1);
        *(M + j) = *(A + p + j*5 + 5/2);
    }
    int j = quantity - 1;
    insertion_sort(A, p + j*5, q);
    *(M + j) = *(A + (int)ceil((p + j*5 + q)/2.0));
    int x = Select(M, 0, quantity - 1, ceil(quantity/2.0));
    int k = partition(A, p, q, x);
    counter_compare++;
    if (i==k) return x;
    else if (i < k) {
        counter_compare++;
        return Select(A, p, k - 1, i);
    }
    else {
        counter_compare++;
        return Select(A, k, q, i);
    }
}

void dual_pivot_quick_sort(int *a, int low, int high) {
    counter_compare++;
    if (low < high) {
        int lp = (low + high)/3;
        counter_compare++;
        if (lp < low) return;
        int rp = 2*(low + high)/3;
        Select(a, low, high, lp);
        Select(a, lp, high, rp);
        dual_pivot_quick_sort(a, low, lp);
        dual_pivot_quick_sort(a, lp + 1, rp);
        dual_pivot_quick_sort(a, rp + 1, high);
    }
}

int main(int argc, char const *argv[]) {
    std::cin >> n;
    int *a = new int[n];
    arg = *(argv + 1);
    for (int i = 0 ; i < n ; i++) {
        std:: cin >> *(a + i);
    }
    if (arg == "print" && n < 40) {
        std::cout << "Input: " << std::endl;
        for (int i = 0 ; i < n ; i++) {
            std::cout << *(a + i) << " ";
        }
        std::cout << "\n---------------------" << std::endl;
    }

    dual_pivot_quick_sort(a, 0, n - 1);
    
    if (arg == "print") {
        if (n < 40) {
            std::cout << "Output:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(a + i) << " ";
            }
            std::cout << "\n---------------------" << std::endl;
        } else {
            std::cout << "Liczba porównań: " << counter_compare << std::endl;
            std::cout << "Liczba przestawień: " << counter_swap << std::endl;
        }
    } else if (arg == "save") {
        std::cout << counter_compare  << "; " << counter_swap << "; " << n << std::endl;
    }
    return 0;
}