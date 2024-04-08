#include <iostream>

int counter_compare = 0;

bool BinarySearch(int *A, int p, int q, int v) {
    counter_compare++;
    if (p == q) return false;
    counter_compare++;
    if (v < *(A + (p + q)/2)) BinarySearch(A, p, (p + q)/2, v);
    counter_compare++;
    if (v > *(A + (p + q)/2)) BinarySearch(A, (p + q)/2 + 1, q, v);
    else return true;
}

int main(int argc, char const *argv[]) {
    std::string par = *(argv + 1);
    std::string arg = *(argv + 2);
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;
    int *A = new int[n];
    for (int i = 0 ; i < n ; i++) {
        std:: cin >> *(A + i);
    }
    if (par == "begin") {
        k = k%(n/100);
    } 
    if (par == "middle") {
        k = k%(n/5) + 4*n/10;
    } 
    if (par == "end") {
        k = k%(n/100) + 99*n/100;
    }
    if (par == "outofrange") {
        k = -1;
    }

    if (arg == "print") {
        if (n < 50) {
            std::cout << "Tablica początkowa:" << std::endl;
            for (int i = 0 ; i < n ; i++) {
                std::cout << *(A + i) << " ";
            }
            bool result;
            if (k > n) {
                result = BinarySearch(A, 0, n - 1, k);
            } else {
                result = BinarySearch(A, 0, n - 1, *(A + k - 1));
            }
            std::cout << "\n---------------------" << std::endl;
            std::cout << "Szukana wartość: " << *(A + k - 1) << std::endl;
            std::cout << "Wynik: " << result << std::endl;
        } else {
            if (k > n) {
                BinarySearch(A, 0, n - 1, k);
            } else {
                BinarySearch(A, 0, n - 1, *(A + k - 1));
            }
            std::cout << "Liczba porównań: " << counter_compare << std::endl;
        }
    } else if (arg == "save") {
        if (k > n) {
            BinarySearch(A, 0, n - 1, k);
        } else {
            BinarySearch(A, 0, n - 1, *(A + k - 1));
        }
        std::cout << counter_compare  << "; " << n << std::endl;
    }
    return 0;
}
