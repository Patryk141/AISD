#include <iostream>
#include <queue>
#include <bits/stdc++.h>

int counter_compare = 0;
int counter_swap = 0;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int value, Node* left, Node* right) {
        this->value = value;
        this->left = left;
        this->right = right;
    }
};

Node* right_rotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    counter_swap++;
    y->right = x;
    counter_swap++;
    return y;
}

Node* left_rotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    counter_swap++;
    y->left = x;
    counter_swap++;
    return y;
}

Node* splay(Node* root, int value) {
    counter_compare++;
    if (root == NULL || root->value == value) {
        return root;
    }
    counter_compare++;
    if (root->value > value) {
        counter_compare++;
        if (root->left == NULL) {
            return root;
        } 
        counter_compare++;
        if (root->left->value > value) {
            counter_swap++;
            root->left->left = splay(root->left->left, value);
            root = right_rotate(root);
        } else if (root->left->value < value) {
            counter_compare++;
            counter_swap++;
            root->left->right = splay(root->left->right, value);
            counter_compare++;
            if (root->left->right != NULL) {
                root->left = left_rotate(root->left);
            }
        }
        return (root->left == NULL) ? root : right_rotate(root);
    } else {
        counter_compare++;
        if (root->right == NULL) {
            return root;
        }
        counter_compare++;
        if (root->right->value > value) {
            counter_swap++;
            root->right->left = splay(root->right->left, value);
            counter_compare++;
            if (root->right->left != NULL) {
                root->right = right_rotate(root->right);
            }
        } else if (root->right->value < value) {
            counter_compare++;
            counter_swap++;
            root->right->right = splay(root->right->right, value);
            root = left_rotate(root);
        }
        return (root->right == NULL) ? root : left_rotate(root);
    }
}

Node* insert_key(Node* root, int value) {
    counter_compare++;
    if (root == NULL) {
        return new Node(value, NULL, NULL);
    }

    root = splay(root, value);

    Node* temp;
    counter_compare++;
    if (root->value > value) {
        temp = new Node(value, root->left, root);
        counter_swap++;
        root->left = NULL;
    } else {
        temp = new Node(value, root, root->right);
        counter_swap++;
        root->right = NULL;
    }
    return temp;
}

Node* delete_key(Node* root, int value) {
    Node* temp;
    counter_compare++;
    if (!root) {
        return NULL;
    }

    root = splay(root, value);
    counter_compare++;
    if (value != root->value) {
        return root;
    }
    counter_compare++;
    if (!root->left) {
        temp = root;
        counter_swap++;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, value);
        counter_swap++;
        root->right = temp->right;
    }
    free(temp);
    return root;
}

int tree_height(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if (left_height >= right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }   
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
  printf("[%d]\n", root->value);
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
    Node* root = NULL;
    
    if (arg == "print") {
        left_trace = (char*)malloc(n*sizeof(char));
        right_trace = (char*)malloc(n*sizeof(char));

        for (int i = 0; i < n; i++) {
            std::cout << "\ninsert: " << a[i] << std::endl;
            std::cout << "\n";
            root = insert_key(root, a[i]);

            for(int i=0; i<=n; i++){
                left_trace[i]=' ';
                left_trace[i]=' ';
            }
            print_BST(root, tree_height(root), '-');
        }

        for (int i = 0; i < 20; i++) {
            std::cout << "\ndelete: " << a[i] << std::endl;
            std::cout << "\n";
            root = delete_key(root, a[i]);

            for(int i=0; i<=n; i++){
                left_trace[i]=' ';
                left_trace[i]=' ';
            }
            print_BST(root, tree_height(root), '-');
        }
    } else {
        for (int i = 0; i < n; i++) {
            root = insert_key(root, a[i]);
        }
        std::cout << n << " " << counter_compare << " " << counter_swap << " " << tree_height(root) << std::endl;
    }
    return 0;
}
