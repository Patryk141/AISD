#include <iostream>
#include <algorithm>

int counter_compare = 0;
int counter_swap = 0;
int n = 0;

int lomuto_partition(int *A, int p, int q) {
    int x = *(A + p);
    int i = p;
    for (int j = p + 1 ; j <= q ; j++) {
        counter_compare++;
        if (*(A + j) <= x) {
            i++;
            counter_swap++;
            std::swap(*(A + i), *(A + j));
        }
    }
    counter_swap++;
    std::swap(*(A + i), *(A + p));               
    return i;
}

void quick_sort(int *a, int p, int q) {
    counter_compare++;
    if (p < q) {
        int r = lomuto_partition(a, p, q);
        quick_sort(a, p, r - 1);
        quick_sort(a, r + 1, q);
    }
}

int RandPartition(int *A, int p, int q) {
    int i = p + rand()%(q - p) + 1;
    counter_swap++;
    std::swap(*(A + i), *(A + p));
    return lomuto_partition(A, p, q);
}

int RandSelect(int *A, int p, int q, int k) {
    counter_compare++;
    if (p == q) return *(A + p);
    int r = RandPartition(A, p, q);
    int i = r - p + 1;
    counter_compare++;
    if (i == k) return *(A + r);
    counter_compare++;
    if (i < k) return RandSelect(A, r + 1, q, k - i);
    else return RandSelect(A, p, r - 1, k);
}

int main(int argc, char const *argv[]) {
    std::string arg = *(argv + 1);
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
            int result = RandSelect(A, 0, n - 1, k);
            std::cout << "\nTablica końcowa:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(A + i) << " ";
            }
            quick_sort(A, 0, n - 1);
            std::cout << "\nPosortowana tablica:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(A + i) << " ";
            }
            std::cout << "\n---------------------" << std::endl;
            std::cout << k << " statystyka pozycyjna: " << result << std::endl;
        } else {
            RandSelect(A, 0, n - 1, k);
            std::cout << "Liczba porównań: " << counter_compare << std::endl;
            std::cout << "Liczba przestawień: " << counter_swap << std::endl;
        }
    } else if (arg == "save") {
        RandSelect(A, 0, n - 1, k);
        std::cout << counter_compare  << "; " << counter_swap << "; " << n << std::endl;
    }
    return 0;
}
