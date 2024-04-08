#include <iostream>
#include <random>
#include <algorithm>

int lomuto_partition(int *a, int p, int q) {
    int x = *(a + p);
    int i = p;
    for (int j = p + 1 ; j <= q ; j++) {
        if (*(a + j) <= x) {
            i++;
            std::swap(*(a + i), *(a + j));
        }
    }
    std::swap(*(a + i), *(a + p));
    return i;
}

void quick_sort(int *a, int p, int q) {
    if (p < q) {
        int r = lomuto_partition(a, p, q);
        quick_sort(a, p, r - 1);
        quick_sort(a, r + 1, q);
    }
}

int main(int argc, char const *argv[]) {
    int n = std::stoi(argv[1]);
    int *a = new int[n];
    std::string arg = argv[2];
    std::mt19937 mt(time(0));
    std::uniform_int_distribution<> random{0, 2*n - 1};
    std::uniform_int_distribution<> ran{1, n};
    std::cout << n << std::endl;
    std::cout << ran(mt) << std::endl;

    for (int i = 0 ; i < n ; i++) {
        *(a + i) = random(mt);
    }
    
    if (arg == "a") {
        quick_sort(a, 0, n - 1);
    } else if (arg == "d") {
        quick_sort(a, 0, n - 1);
        for (int i = 0 ; i < n/2 ; i++) {
            std::swap(*(a + i), *(a + n - 1 - i));
        }
    }

    for (int i = 0 ; i < n ; i++) {
        std::cout << *(a + i) << std::endl;
    }

    return 0;
}
