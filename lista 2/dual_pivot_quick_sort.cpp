#include <iostream>
#include <algorithm>

int counter_swap = 0;
int counter_compare = 0;
std::string arg;
int n = 0;

int partition(int* a, int low, int high, int* lp) {
    counter_compare++;
    if (*(a + low) > *(a + high)) {
        counter_swap++;
        std::swap(*(a + low), *(a + high));
    }
    int j = low + 1; //indeks lewego pivota
    int g = high - 1; //indeks prawego pivota
    int k = low + 1; //indeks sprawdzanego elementu
    int p = a[low];
    int q = a[high];
    while (k <= g) {
        if (j - low >= high - g) {
            counter_compare++;
            if (*(a + k) < p) {
                counter_compare++;
                counter_swap++;
                std::swap(*(a + k), *(a + j));
                j++;
            }
            else if (*(a + k) >= q) {
                counter_compare++;
                while (*(a + g) > q && k < g) {
                    counter_compare++;
                    g--;
                }
                counter_swap++;
                std::swap(*(a + k), *(a + g));
                g--;
                counter_compare++;
                if (*(a + k) < p) {
                    counter_swap++;
                    std::swap(*(a + k), *(a + j));
                    j++;
                }
            }
        } else {
            counter_compare++;
            if (*(a + k) >= q) {
                counter_compare++;
                while (*(a + g) > q && k < g) {
                    counter_compare++;
                    g--;
                }
                counter_swap++;
                std::swap(*(a + k), *(a + g));
                g--;
                counter_compare++;
                if (*(a + k) < p) {
                    counter_swap++;
                    std::swap(*(a + k), *(a + j));
                    j++;
                }
            } else if (*(a + k) < p) {
                counter_compare++;
                counter_swap++;
                std::swap(*(a + k), *(a + j));
                j++;
            }
        }
        k++;
    }
    j--;
    g++;
    counter_swap++;
    std::swap(*(a + low), *(a + j));
    counter_swap++;
    std::swap(*(a + high), *(a + g));
    *lp = j;
    if (n < 40 && arg == "print") {
        std::cout << "(pivot 1: " << *(a + *lp) << " pivot 2: " << *(a + g) << ") ";
        for (int i = 0 ; i < n ; i++) {
               std::cout << *(a + i) << " ";
        }
        std::cout << "\n-----------------" << std::endl;
    }
    return g;   
}

void dual_pivot_quick_sort(int *a, int low, int high) {
    counter_compare++;
    if (low < high) {
        int lp, rp;
        rp = partition(a, low, high, &lp);
        dual_pivot_quick_sort(a, low, lp - 1);
        dual_pivot_quick_sort(a, low + 1, rp - 1);
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
