#include <iostream>
#include <queue>
#include <bits/stdc++.h>

int counter_compare = 0;
int counter_swap = 0;

struct Node {
    int value;
    Node* parent;
    Node* left;
    Node* right;
    int color;

    Node(int value, Node* parent, Node* left, Node* right, int color) {
        this->value = value;
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->color = color;
    }
};

Node* root = NULL;

Node* insert_key(Node* root, Node* temp) {
    counter_compare++;
    if (root == NULL) {
        return temp;
    }
    counter_compare++;
    if (root->value > temp->value) {
        counter_swap++;
        root->left = insert_key(root->left, temp);
        counter_swap++;
        root->left->parent = root;
    } else {
        counter_swap++;
        root->right = insert_key(root->right, temp);
        counter_swap++;
        root->right->parent = root;
    }

    return root;
}

void left_rotate(Node* temp) {
    Node* right = temp->right;
    counter_swap++;
    temp->right = right->left;
    if (temp->right) {
        counter_swap++;
        temp->right->parent = temp;
    }
    counter_swap++;
    right->parent = temp->parent;
    if (!temp->parent) {
        root = right;
    } else if (temp == temp->parent->left) {
        counter_swap++;
        temp->parent->left = right;
    } else {
        counter_swap++;
        temp->parent->right = right;
    }
    counter_swap++;
    right->left = temp;
    counter_swap++;
    temp->parent = right;
}

void right_rotate(Node* temp) {
    Node* left = temp->left;
    counter_swap++;
    temp->left = left->right;
    counter_compare++;
    if (temp->left) {
        counter_swap++;
        temp->left->parent = temp;
    }
    counter_swap++;
    left->parent = temp->parent;
    counter_compare++;
    if (!temp->parent) {
        root = left;
    } else if (temp == temp->parent->left) {
        counter_compare++;
        counter_swap++;
        temp->parent->left = left;
    } else {
        counter_swap++;
        temp->parent->right = left;
    }
    counter_swap++;
    left->right = temp;
    counter_swap++;
    temp->parent = left;
}

void rb_insert(Node* pt) {
    root = insert_key(root, pt);

    Node* parent_pt = NULL;
    Node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != 0) && (pt->parent->color == 1)) {
        counter_compare++;
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        counter_compare++;
        if (parent_pt == grand_parent_pt->left) {
            Node* uncle_pt = grand_parent_pt->right;
            counter_compare++;
            if (uncle_pt != NULL && uncle_pt->color == 1) {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            } else {
                counter_compare++;
                if (pt == parent_pt->right) {
                    left_rotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                
                right_rotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        } else {
            Node* uncle_pt = grand_parent_pt->left;
            counter_compare++;
            if ((uncle_pt != NULL) && (uncle_pt->color == 1)) {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            } else {
                counter_compare++;
                if (pt == parent_pt->left) {
                    right_rotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                left_rotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
    }
    root->color = 0;
}

int tree_height(Node* root) {
    counter_compare++;
    if (root == NULL) {
        return 0;
    } else {
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        counter_compare++;
        if (left_height >= right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }   
}

Node* search(int value) {
    Node* temp = root;
    while (temp != NULL) {
        counter_compare++;
        counter_compare++;
        if (value < temp->value) {
            counter_compare++;
            if (temp->left == NULL) {
                break;
            } else {
                counter_swap++;
                temp = temp->left;
            }
        } else if (value == temp->value) {
            counter_compare++;
            break;
        } else {
            counter_compare++;
            if (temp->right == NULL) {
                break;
            } else {
                counter_swap++;
                temp = temp->right;
            }
        }
    }
    return temp;
}

Node* successor(Node* x) {
    Node* temp = x;
    
    while (temp->left != NULL) {
        counter_compare++;
        temp = temp->left;
    }
    return temp;
}

Node* BSTreplace(Node* x) {
    counter_compare++;
    if (x->left != NULL && x->right != NULL) {
        return successor(x->right);
    }
    counter_compare++;
    if (x->left == NULL && x->right == NULL) {
        return NULL;
    }
    counter_compare++;
    if (x->left != NULL) {
        return x->left; 
    } else {
        return x->right;
    }
}

Node* sibling(Node* x) {
    counter_compare++;
    if (x->parent == NULL) {
        return NULL;
    }
    counter_compare++;
    if (x == x->parent->left) {
        return x->parent->right;
    } else {
        return x->parent->left;
    }
}

void swapValues(Node* u, Node* v) {
    int temp = u->value;
    counter_swap++;
    u->value = v->value;
    counter_swap++;
    v->value = temp;
}

void fixDoubleBlack(Node* x) {
    counter_compare++;
    if (x == root) {
        return;
    }

    Node* siblin = sibling(x);
    Node* parent = x->parent;
    counter_compare++;
    if (siblin == NULL) {
        fixDoubleBlack(parent);
    } else {
        counter_compare++;
        if (siblin->color == 1) {
            parent->color = 1;
            siblin->color = 0;
            counter_compare++;
            if (siblin == siblin->parent->left) {
                right_rotate(parent);
            } else {
                left_rotate(parent);
            }
            fixDoubleBlack(x);
        } else {
            counter_compare++;
            if ((siblin->left != NULL && siblin->left->color == 1) || (siblin->right != NULL && siblin->right->color == 1)) {
                counter_compare++;
                if (siblin->left != NULL && siblin->left->color == 1) {
                    counter_compare++;
                    if (siblin == siblin->parent->left) {
                        siblin->left->color = siblin->color;
                        siblin->color = parent->color;
                        right_rotate(parent);
                    } else {
                        siblin->left->color = parent->color;
                        right_rotate(siblin);
                        left_rotate(parent);
                    }
                } else {
                    counter_compare++;
                    if (siblin == siblin->parent->left) {
                        siblin->right->color = parent->color;
                        left_rotate(siblin);
                        right_rotate(parent);
                    } else {
                        siblin->right->color = siblin->color;
                        siblin->color = parent->color;
                        left_rotate(parent);
                    }
                }
                parent->color = 0;
            } else {
                siblin->color = 1;
                counter_compare++;
                if (parent->color == 0) {
                    fixDoubleBlack(parent);
                } else {
                    parent->color = 0;
                }
            }
        }
    }
}

void deleteNode(Node* v) {
    Node* u = BSTreplace(v);

    bool uvBlack = ((u == NULL || u->color == 0) && (v->color == 0));
    Node* parent = v->parent;
    counter_compare++;
    if (u == NULL) {
        counter_compare++;
        if (v == root) {
            root = NULL;
        } else {
            counter_compare++;
            if (uvBlack) {
                fixDoubleBlack(v);
            } else {
                counter_compare++;
                if (sibling(v) != NULL) {
                    sibling(v)->color = 1;
                }
            }
            counter_compare++;
            if (v == v->parent->left) {
                counter_swap++;
                parent->left = NULL;
            } else {
                counter_swap++;
                parent->right = NULL;
            }
        }
        free(v);
        return;
    }
    counter_compare++;
    if (v->left == NULL || v->right == NULL) {
        counter_compare++;
        if (v == root) {
            counter_swap++;
            v->value = u->value;
            counter_swap++;
            v->left = v->right = NULL;
            free(u);
        } else {
            counter_compare++;
            if (v == v->parent->left) {
                counter_swap++;
                parent->left = u;
            } else {
                counter_swap++;
                parent->right = u;
            }
            free(v);
            counter_swap++;
            u->parent = parent;
            counter_compare++;
            if (uvBlack) {
                fixDoubleBlack(u);
            } else {
                u->color = 0;
            }
        }
        return;
    }
    swapValues(u, v);
    deleteNode(u);
}

void delete_key(int value) {
    counter_compare++;
    if (root == NULL) {
        return;
    }

    Node* v = search(value);
    Node* u;
    counter_compare++;
    if (v->value != value) {
        return;
    }

    deleteNode(v);
}

// global variables used in `print_BST`
char* left_trace; // needs to be allocaded with size
char* right_trace; // needs to be allocaded with size


void print_BST( Node* root, int depth,char prefix){
  if( root == NULL ) return;
  if( root->left != NULL ){
    print_BST(root->left, depth+1, '/');
  }
  if(prefix == '/') left_trace[depth-1]='|';
  if(prefix == '\\') right_trace[depth-1]=' ';
  if( depth==0) printf("-");
  if( depth>0) printf(" ");
  for(int i=0; i<depth-1; i++)
    if( left_trace[i]== '|' || right_trace[i]=='|' ) {
      printf("| ");
    } else {
      printf("  ");
    }
  if( depth>0 ) printf("%c-", prefix);
  if(root->color == 1) printf("\x1b[0;31m[%d]\x1b[0;39m\n", root->value);
  else printf("[%d]\n", root->value);
  left_trace[depth]=' ';
  if( root->right != NULL ){
    right_trace[depth]='|';
    print_BST(root->right, depth+1, '\\');
  }
}


int main(int argc, char const *argv[]) {
    int n;
    std::string arg = argv[1];
    std::cin >> n;
    int *a = new int[n];
    for (int i = 0 ; i < n ; i++) {
        std:: cin >> a[i];
    }
    if (arg == "print") {
        left_trace = (char*)malloc(n*sizeof(char));
        right_trace = (char*)malloc(n*sizeof(char));

        for (int i = 0; i < n; i++) {
            std::cout << "\ninsert: " << a[i] << std::endl;
            std::cout << "\n";
            Node* temp = new Node(a[i], NULL, NULL, NULL, 1);
            rb_insert(temp);

            for(int i=0; i<=n; i++){
                left_trace[i]=' ';
                left_trace[i]=' ';
            }
            print_BST(root, tree_height(root), '-');
        }
        
        for (int i = 0; i < 20; i++) {
            std::cout << "\ndelete: " << a[i] << std::endl;
            std::cout << "\n";
            delete_key(a[i]);
            for(int i=0; i<=n; i++){
                left_trace[i]=' ';
                left_trace[i]=' ';
            }
            print_BST(root, tree_height(root), '-');
        }
            
    } else {
        for (int i = 0; i < n; i++) {
            Node* temp = new Node(a[i], NULL, NULL, NULL, 1);
            rb_insert(temp);
        }
        std::cout << n << " " << counter_compare << " " << counter_swap << " " << tree_height(root) << std::endl;
    }
        
    return 0;
}
