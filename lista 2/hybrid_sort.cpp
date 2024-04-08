#include <iostream>

int counter_swap = 0;
int counter_compare = 0;
std::string arg;
int n = 0;

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
    }  
}

int* merge(int *b, int size_b, int *c, int size_c) {
    int i = 0, j = 0;
    int *a = new int[size_b + size_c];
    for (int i = 0 ; i < size_b ; i++) {
        *(a + i) = *(b + i);
    }
    for (int i = 0 ; i < size_c ; i++) {
        *(a + i + size_b) = *(c + i);
    }
    insertion_sort(a, size_b + size_c);
    if (n < 40 && arg == "print") {
            for (int i = 0 ; i < size_b ; i++) {
                std::cout << b[i] << " ";
            }
            std::cout << std::endl;
            for (int i = 0 ; i < size_c ; i++) {
                std::cout << c[i] << " ";
            }
            std::cout << std::endl;
            for (int i = 0 ; i < size_b + size_c ; i++) {
                std::cout << a[i] << " ";
            }
            std::cout << "\n-----------------" << std::endl;
    }
    return a;
}

int* merge_sort(int *a, int begin , int end) {
    if (begin == end) {
        return (a + begin);
    }
    int mid = begin + (end + 1 - begin) / 2; 
    int *b = new int[mid - begin];
    int *c = new int[end + 1 - mid];
    b = merge_sort(a, begin, mid - 1);
    c = merge_sort(a, mid, end);
    return merge(b, mid - begin, c, end + 1 - mid);
}

int main(int argc, char const *argv[]) {
    std::cin >> n;
    int *a = new int[n];
    int *b = new int[n];
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

    b = merge_sort(a, 0, n - 1);
    
    if (arg == "print") {
        if (n < 40) {
            std::cout << "Output:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(b + i) << " ";
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
