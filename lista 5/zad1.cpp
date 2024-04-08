#include <iostream>

struct node {
    int value;
    int length;
    node* previous;

    node(int value) {
        this->value = value;
        length = 0;
        previous = NULL;
    }

    node() {}
};

int counter_compare = 0;

int lenghtOfSequence = 0;
node* longest;

void lis(node* sequence, int index) {
    int max = 0;
    for (int i = 0; i < index; i++) {
        counter_compare++;
        if (sequence[i].value < sequence[index].value) {
            counter_compare++;
            if (max < sequence[i].length) {
                max = sequence[i].length;
                sequence[index].previous = &sequence[i]; 
            }
        }
    }
    sequence[index].length = max + 1;
    counter_compare++;
    if (lenghtOfSequence < max + 1) {
        lenghtOfSequence = max + 1;
        longest = &sequence[index];
    }
}

int main(int argc, char const *argv[]) {
    int n;
    std::cin >> n;
    std::string arg = argv[1];

    node* sequence = new node[n];

    for (int i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        sequence[i] = node(temp);
        lis(sequence, i);
    }

    if (arg == "print") {
    	for (int i = 0; i < n; i++) {
    	    std::cout << sequence[i].value << " ";
    	}
    
        std::cout << "\nDługość: " << lenghtOfSequence << std::endl;
        
        node* ptr = longest;
        std::string result = "";
        while (ptr != NULL) {
            result = std::to_string(ptr->value) + " " + result;
            ptr = ptr->previous;
        }
        std::cout << result << std::endl;
    } else {
        std::cout << n << " " << counter_compare << std::endl;
    }

    return 0;
}
