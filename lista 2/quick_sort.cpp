#include <iostream>
#include <algorithm>

int counter_swap = 0;
int counter_compare = 0;
std::string arg;
int n = 0;

int lomuto_partition(int *a, int p, int q) {
    int x = *(a + p);
    int i = p;
    for (int j = p + 1 ; j <= q ; j++) {
        counter_compare++;
        if (*(a + j) <= x) {
            i++;
            counter_swap++;
            std::swap(*(a + i), *(a + j));
        }
    }
    counter_swap++;
    std::swap(*(a + i), *(a + p));
    if (n < 40 && arg == "print") {
        std::cout << "(pivot: " << *(a + i) << ") ";
        for (int i = 0 ; i < n ; i++) {
               std::cout << *(a + i) << " ";
        }
        std::cout << "\n-----------------" << std::endl;
    }
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
        

int main(int argc, char const *argv[]) {
    arg = *(argv + 1);
    std::cin >> n;
    int *a = new int[n];
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

    quick_sort(a, 0, n - 1);
    
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
