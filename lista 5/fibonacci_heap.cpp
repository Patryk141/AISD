#include <iostream>
#include <algorithm>
#include <cstring>

struct node {
    node *child, *parent, *left, *right;
	int key, degree;
	bool mark;

    node(int key) {
        this->child = NULL;
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
        this->key = key;
        this->degree = 0;
        this->mark = false;
    }
};

int counter_compare = 0;

struct fibonacci_heap {
    node* min;
    int size;
    int capacity;

    void insert_to(node* v, node* u) {
        v->right = u->right;
        v->left = u;
        u->right->left = v;
        u->right = v;
    }

    void insert_to_root_list(node* u) {
        insert_to(u, min);
    }

    void remove_from_root_list(node* u) {
        u->left->right = u->right;
	    u->right->left = u->left;
    }

    void link(node*v, node* u) {
        remove_from_root_list(v);
        counter_compare++;
        if (u->child == NULL)
        {
            u->child = v;
            v->parent = u;
            v->left = v->right = v;
        }
        else
        {
            insert_to(v, u->child);
            v->parent = u;
        }
    }

    void consolidate() {
        node* root_list[capacity];
        node* first = min;
        node* u = first;
        int cnt = 0;
        do {
            root_list[cnt++] = u;
            u = u->right;
        } while (u != first);
        node* list[50];
        memset(list, 0, sizeof(list));
        for (int i = 0; i < cnt; i++)
        {
            node *x = root_list[i];
            while (list[x->degree] != NULL)
            {
                node *y = list[x->degree];
                counter_compare++;
                if (x->key > y->key) 
                    std::swap(x, y);
                link(y, x);
                list[x->degree++] = NULL;
            }
            list[x->degree] = x;
        }
        min = NULL;
        for (int i = 0; i < 50; i++) {
            counter_compare++;
            if (list[i] != NULL) {
                counter_compare++;
                if (min == NULL) {
                    min = list[i];
                    list[i]->left = list[i]->right = list[i];
                } else {
                    insert_to_root_list(list[i]);
                    counter_compare++;
                    if (list[i]->key < min->key) 
                        min = list[i];
                }
            }
        }
    }

    void insert(int key) {
        counter_compare++;
        if (min == NULL) {
            min = new node(key);
            min->left = min->right = min;
        } else {
            node *u = new node(key);
            insert_to_root_list(u);
            counter_compare++;
            if (key < min->key)
                min = u;
        }
        size++;
    }

    int extract_min() {
        int res = min->key;
        counter_compare++;
        if (min != NULL) {
            counter_compare++;
            if (size == 1) {
                min = NULL;
            } else {
                counter_compare++;
                if (min->child != NULL) {
                    node *child_list[capacity];
                    node *first = min->child;
                    node *u = first;
                    int cnt = 0;
                    do {
                        child_list[cnt++] = u;
                        u = u->right;
                    } while (u != first);
                    for (int i = 0; i < cnt; i++) {
                        insert_to_root_list(child_list[i]);
                    }
                }
                remove_from_root_list(min);
                min = min->right;
                consolidate();
            }
        }
        size--;
        return res;
    }

    fibonacci_heap(int capacity) {
        this->min = NULL;
        this->size = 0;
        this->capacity = capacity;
    }
};

fibonacci_heap heap_union(fibonacci_heap q1, fibonacci_heap q2) {
    counter_compare++;
    if (q1.min == NULL) {
        return q2;
    }
    counter_compare++;
    if (q2.min == NULL) {
        return q1;
    }

    node* root1 = q1.min;
    node* root2 = q2.min;
    root1->left->right = root2;
    root2->left->right = root1;
    node* temp = root1->left;
    root1->left = root2->left;
    root2->left = temp;

    counter_compare++;
    if (root2->key < root1->key) {
        q1.min = root2;
    }

    q1.size += q2.size;

    return q1;
}

int main(int argc, char const *argv[]) {
    fibonacci_heap H1 = fibonacci_heap(20000);
    fibonacci_heap H2 = fibonacci_heap(20000);

    int n;
    std::cin >> n;

    std::cout << "Elementy pierwszego kopca: " << std::endl;
    
    for (int i = 0; i < n/2; i++) {
        int temp;
        std::cin >> temp;
        std::cout << temp << " ";
        H1.insert(temp);
    }

    std::cout << "\nElementy drugiego kopca: " << std::endl;

    for (int i = n/2; i < n; i++) {
        int temp;
        std::cin >> temp;
        std::cout << temp << " ";
        H2.insert(temp);
    }
    
    counter_compare = 0;

    H1 = heap_union(H1, H2);

    // for (int i = 0; i < n; i++) {
    //     H1.extract_min();
    // }

    // std::cout << n/2 << " " << counter_compare << std::endl;
    
    std::cout << "\nExtract min po wykonaniu operacji union na kopcach:" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << H1.extract_min() << " ";
    }

    std::cout << "\n";

    return 0;
}
