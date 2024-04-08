#include <iostream>

int counter_swap = 0;
int counter_compare = 0;
std::string arg;

void insertion_sort(int *a, int n) {
    for (int j = 1 ; j < n ; j++) {
        int key = a[j];
        int i = j - 1;
        counter_compare++;
        while (i > - 1 && *(a + i) > key) {
            counter_swap++;
            *(a + i + 1) = *(a + i);
            i--;
            counter_compare++;
        }
        counter_swap++;
        *(a + i + 1) = key;
        if (n < 40 && arg == "print") {
            for (int i = 0 ; i < n ; i++) {
                std::cout << a[i] << " ";
            }
            std::cout << std::endl;
        }
    }  
}

int main(int argc, char const *argv[]) {
    int n = 0;
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

    insertion_sort(a, n);
    
    if (arg == "print") {
        if (n < 40) {
            std::cout << "---------------------" << std::endl;
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
