#include <iostream>
#include <stdexcept>
using namespace std;

bool evenOnes(int n) {
    if (n == 0) {
        return true;
    }
    return ((n % 2 == 0) == evenOnes(n/2));
}

struct Node {
    Node(int val, Node* next = nullptr)
        : next(next), val(val) {}
    Node* next;
    int val;
};
    
Node* sumLists(Node* a, Node* b) {
    if (a == nullptr && b == nullptr) {
        return nullptr;
    }
    Node* nextA = (a != nullptr ? a->next : nullptr);
    Node* nextB = (b != nullptr ? b->next : nullptr);
    int val = 0;
    if (a != nullptr) {
        val += a->val;
    }
    if (b != nullptr) {
        val += b->val;
    }
    return new Node(val, sumLists(nextA, nextB));
}

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
    if (root == nullptr) {
        throw invalid_argument("received nullptr");
    }
    int maximum = root->data;
    if (root->left != nullptr) {
        int submax1 = max(root->left);
        if (submax1 > maximum) {
            maximum = submax1;
        }
    }
    if (root->right != nullptr) {
        int submax2 = max(root->right);
        if (submax2 > maximum) {
            maximum = submax2;
        }
    }
    return maximum;
}

bool palindrome(char* start, int length) {
    if (length <= 1) {
        return true;
    }
    return (start[0] == start[length-1]) && palindrome(start+1, length - 2);
}

int towers(int numDisks, char start, char space, char end) {
    if (numDisks == 1) {
        return 1;
    }
    return towers(numDisks-1, start, end, space)
        + 1
        + towers(numDisks-1, space, start, end);
}

void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; 
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
   } 
   cout << 'c'; 
}

int main() {
    //========================1=======
    cout << evenOnes(1) << endl;
    cout << evenOnes(100) << endl;
    cout << evenOnes(0) << endl;

    //========================2=======
    Node* an = new Node(1);
    an->next = new Node(2);
    an->next->next = new Node(6);
    an->next->next->next = new Node(3);
    
    Node* bn = new Node(0);
    bn->next = new Node(10);

    Node* cn = sumLists(an,bn);

    Node* cursor = cn;
    while (cursor != nullptr) {
        cout << cursor->val << endl;
        cursor = cursor->next;
    }

    //========================3=======
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << max(&f) << endl;

    //========================4=======
    char s[] = "racecar";
    cout << palindrome(s,7) << endl;

    //========================5=======
    cout << towers(1, 'a', 'b', 'c') << endl;
    cout << towers(2, 'a', 'b', 'c') << endl;
    cout << towers(3, 'a', 'b', 'c') << endl;
    cout << towers(4, 'a', 'b', 'c') << endl;
    cout << towers(5, 'a', 'b', 'c') << endl;
    cout << towers(6, 'a', 'b', 'c') << endl;
    cout << towers(7, 'a', 'b', 'c') << endl;
    cout << towers(8, 'a', 'b', 'c') << endl;
    cout << towers(9, 'a', 'b', 'c') << endl;
    cout << towers(10, 'a', 'b', 'c') << endl;
    //========================6=======

    mystery(0);
    cout << endl;
    mystery(1);
    cout << endl;
    mystery(2);
    cout << endl;
    mystery(3);
    cout << endl;
    mystery(4);
    cout << endl;
    mystery(5);
    cout << endl;
    mystery(6);
    cout << endl;
    mystery(7);
    cout << endl;
    mystery(8);
    cout << endl;
    mystery(9);
    cout << endl;
    mystery(10);
    cout << endl;


}

