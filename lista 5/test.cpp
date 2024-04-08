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
                if (x->key > y->key) std::swap(x, y);
                link(y, x);
                list[x->degree++] = NULL;
            }
            list[x->degree] = x;
        }
        min = NULL;
        for (int i = 0; i < 50; i++)
        {
            if (list[i] != NULL)
            {
                if (min == NULL)
                {
                    min = list[i];
                    list[i]->left = list[i]->right = list[i];
                }
                else
                {
                    insert_to_root_list(list[i]);
                    if (list[i]->key < min->key) min = list[i];
                }
            }
        }
    }

    void insert(int key) {
        if (min == NULL) {
            min = new node(key);
            min->left = min->right = min;
        } else {
            node *u = new node(key);
            insert_to_root_list(u);
            if (key < min->key) min = u;
        }
        size++;
    }

    int extract_min() {
        int res = min->key;
        if (min != NULL) {
            if (size == 1) {
                min = NULL;
            } else {
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

int main(int argc, char const *argv[]) {
    fibonacci_heap H = fibonacci_heap(1000);

    int a1[10] = {10, 14, 8, 3, 9, 7, 16, 4, 1, 2};
    int a2[5] = {7, 16, 4, 1, 2};

    for (int i = 0; i < 10; i++) {
        H.insert(a1[i]);
    }

    for (int i = 0; i < 10; i++) {
        std::cout << H.extract_min() << " ";
    }
    std::cout << "\n";

    return 0;
}
