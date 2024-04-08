#include <iostream>

long long counter_compare = 0;
long long counter_swap = 0;

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

void inorder(Node* root) {
    if (root != NULL) {
        std::cout << root->value << " ";
        inorder(root->left);
        inorder(root->right);
    }
}

Node* insert_key(Node* root, int value) {
    counter_compare++;
    if (root == NULL) {
        return new Node(value, NULL, NULL);
    }
    counter_compare++;
    if (root->value > value) {
        counter_swap++;
        root->left = insert_key(root->left, value);
    } else {
        counter_swap++;
        root->right = insert_key(root->right, value);
    }

    return root;
}

Node* min_value(Node* node) {
    Node* curr = node;

    while (curr && curr->left !=NULL) {
        counter_compare++;
        counter_swap++;
        curr = curr->left;
    }

    return curr;
}

Node* delete_key(Node* root, int value) {
    counter_compare++;
    if (root == NULL) {
        return root;
    }

    counter_compare++;
    if (root->value > value) {
        counter_swap++;
        root->left = delete_key(root->left, value);
    } else if (root->value < value) {
        counter_compare++;
        counter_swap++;
        root->right = delete_key(root->right, value);
    } else {
        counter_compare++;
        if (root->left == NULL && root->right == NULL) {
            return root;
        } else if (root->left == NULL) {
            counter_compare++;
            counter_swap++;
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            counter_compare += 2;
            counter_swap++;
            Node* temp = root->left;
            free(root);
            return temp;
        }
        

        Node* temp = min_value(root->right); 
        counter_swap++;
        root->value = temp->value;
        root->right = delete_key(root->right, temp->value);
    }

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
