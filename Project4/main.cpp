/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 21.12.2017
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o 150140117
 
 * * * * * * * * * * * * * * * * * */

#include <iostream>  // cout
#include <fstream>  // ifstream
#include <sstream> // stringstream
#include <string> // string, stoi

using namespace std;

typedef enum Color {
    RED=0, BLACK
} Color;

typedef struct Node {
    string name; // key
    char gender;
    int age;
    int num_woman;
    int num_man;
    Color color;
    Node *parent;
    Node *left;
    Node *right;
} Node;

class RBTree {
  private:
    Node *root;
    void rotateLeft(Node*& rotate_around);
    void rotateRight(Node*& rotate_around);
    void treeInsert(Node*& new_node);
    void recursivePrint(Node* root, int depth) const;
    void freeMemory(Node*& root);
    Node* findNthWoman(Node* check, int n) const;
    Node* findNthMan(Node* check, int n) const;
  public:
    RBTree();
    ~RBTree();
    void insert(Node*& new_node);
    string nthWoman(int n) const;
    string nthMan(int n) const;
    void print() const;
};

int main(int argc, const char * argv[]) {
    // Input file name argument must be passed with run command
    if (argc != 2) {
        cout << endl << "Missing arguments to proceed." << endl << endl;
        return 0;
    }
    
    // Get input file name and open the file
    string input_filename(argv[1]);
    ifstream inputFile(input_filename, ifstream::in); // Read
    
    if (!inputFile.is_open()) { // Error while openning the file
        cout << endl << "Error opening input file." << endl << endl;
        return 0;
    }
    
    RBTree tree;
    
    string line;
    while(!inputFile.eof()) {
        getline(inputFile, line); // Read the line
        
        // If line is empty, no need to take action
        if(line.empty()) break;
        
        // Create stringstream to parse with '\t'
        stringstream linestream(line);
        
        string read[3];
    
        // Parse the line
        getline(linestream, read[0], '\t');
        getline(linestream, read[1], '\t');
        linestream >> read[2];
        
        // Create a new node and insert it to the tree
        Node* new_node = new Node;
        new_node->name = read[0];
        new_node->gender = read[1][0];
        new_node->age = stoi(read[2]);
        new_node->num_woman = new_node->num_man = 0;
        
        if (new_node->gender == 'F')
            new_node->num_woman++;
        else
            new_node->num_man++;
        
        tree.insert(new_node);
    }
    
    // Close the input file since it is no longer needed
    inputFile.close();
    
    tree.print();
    cout << "3rd woman: " << tree.nthWoman(3) << endl;
    cout << "4th man: " << tree.nthMan(4) << endl << endl;
    return 0;
}

RBTree::RBTree() {
    root = nullptr;
}

RBTree::~RBTree() {
    freeMemory(root);
}

void RBTree::freeMemory(Node*& root) {
    if (root != nullptr) {
        freeMemory(root->left);
        freeMemory(root->right);
        delete root;
    }
}

void RBTree::treeInsert(Node*& new_node) {
    Node *y = nullptr;
    Node *x = root;
    
    while (x != nullptr) {
        y = x;
        
        if (new_node->gender == 'F')
            y->num_woman++;
        else
            y->num_man++;
        
        if ((new_node->name).compare(x->name) < 0)
            x = x->left;
        else
            x = x->right;
    }
    
    new_node->parent = y;
    
    if (y == nullptr)
        root = new_node;
    else if ((new_node->name).compare(y->name) < 0)
        y->left = new_node;
    else
        y->right = new_node;
    
    new_node->left = nullptr;
    new_node->right = nullptr;
}

void RBTree::rotateLeft(Node*& rotate_around) {
    Node* y = rotate_around->right;
    rotate_around->right = y->left;
    
    if (y->left != nullptr)
        (y->left)->parent = rotate_around;
    
    y->parent = rotate_around->parent;
    
    if (rotate_around->parent == nullptr)
        root = y;
    else if (rotate_around == (rotate_around->parent)->left)
        (rotate_around->parent)->left = y;
    else
        (rotate_around->parent)->right = y;
    
    y->left = rotate_around;
    rotate_around->parent = y;
    
    y->num_woman = rotate_around->num_woman;
    y->num_man = rotate_around->num_man;
    
    if (rotate_around->left != nullptr) {
        rotate_around->num_woman = (rotate_around->left)->num_woman;
        rotate_around->num_man = (rotate_around->left)->num_man;
    } else
        rotate_around->num_woman = rotate_around->num_man = 0;
    
    if (rotate_around->right != nullptr) {
        rotate_around->num_woman += (rotate_around->right)->num_woman;
        rotate_around->num_man += (rotate_around->right)->num_man;
    }
    
    if (rotate_around->gender == 'F')
        rotate_around->num_woman++;
    else
        rotate_around->num_man++;
}

void RBTree::rotateRight(Node*& rotate_around) {
    Node* y = rotate_around->left;
    rotate_around->left = y->right;
    
    if (y->right != nullptr)
        (y->right)->parent = rotate_around;
    
    y->parent = rotate_around->parent;
    
    if (rotate_around->parent == nullptr)
        root = y;
    else if (rotate_around == (rotate_around->parent)->left)
        (rotate_around->parent)->left = y;
    else
        (rotate_around->parent)->right = y;
    
    y->right = rotate_around;
    rotate_around->parent = y;
    
    y->num_woman = rotate_around->num_woman;
    y->num_man = rotate_around->num_man;
    
    if (rotate_around->left != nullptr) {
        rotate_around->num_woman = (rotate_around->left)->num_woman;
        rotate_around->num_man = (rotate_around->left)->num_man;
    } else
        rotate_around->num_woman = rotate_around->num_man = 0;
    
    if (rotate_around->right != nullptr) {
        rotate_around->num_woman += (rotate_around->right)->num_woman;
        rotate_around->num_man += (rotate_around->right)->num_man;
    }
    
    if (rotate_around->gender == 'F')
        rotate_around->num_woman++;
    else
        rotate_around->num_man++;
}

void RBTree::insert(Node*& new_node) {
    treeInsert(new_node);
    new_node->color = RED;
    
    while (new_node != root && (new_node->parent)->color == RED) {
        Node *parent = new_node->parent;
        Node *grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            Color uncleColor = (uncle == nullptr) ? BLACK : RED;
            if (uncleColor == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                new_node = grandparent;
            } else {
                if (new_node == parent->right) {
                    new_node = parent;
                    rotateLeft(new_node);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(grandparent);
            }
        } else {
            Node* uncle = grandparent->left;
            Color uncleColor = (uncle == nullptr) ? BLACK : RED;
            if (uncleColor == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                new_node = grandparent;
            } else {
                if (new_node == parent->left) {
                    new_node = parent;
                    rotateRight(new_node);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color = BLACK;
}

Node* RBTree::findNthWoman(Node* check, int n) const {
    if (check == nullptr)
        return nullptr;
    
    int r = 0;
    if (check->left != nullptr)
        r = (check->left)->num_woman;

    if(check->gender == 'F')
        r++;
    
    if (n == r) {
        if (check->gender != 'F') {
            Node* temp = check;
            check = findNthWoman(check->left, n);
            
            if (check == nullptr)
                return findNthWoman(temp->right, n);
        }
        return check;
    }
    else if (n < r)
        return findNthWoman(check->left, n);
    else
        return findNthWoman(check->right, n-r);
}

Node* RBTree::findNthMan(Node* check, int n) const {
    if (check == nullptr)
        return nullptr;
    
    int r = 0;
    if (check->left != nullptr)
        r = (check->left)->num_man;
    
    if(check->gender == 'M')
        r++;
    
    if (n == r) {
        if (check->gender != 'M') {
            Node* temp = check;
            check = findNthMan(check->left, n);
            
            if (check == nullptr)
                return findNthMan(temp->right, n);
        }
        return check;
    }
    else if (n < r)
        return findNthMan(check->left, n);
    else
        return findNthMan(check->right, n-r);
}

string RBTree::nthWoman(int n) const {
    Node* NthWoman = findNthWoman(root, n);
    return NthWoman->name;
}

string RBTree::nthMan(int n) const {
    Node* NthMan = findNthMan(root, n);
    return NthMan->name;
}

void RBTree::recursivePrint(Node *root, int depth) const {
    if (root->left != nullptr)
        recursivePrint(root->left, depth+2);
    
    if (root->parent != nullptr) {
        for(int i = 0; i < depth; i++)
            cout << "\t";
        
        if(root == (root->parent)->left)
            cout << "┌───";
        
        else if(root == (root->parent)->right)
            cout << "└───";
    }
    
    if(root->color == RED)
        cout << "(R)";
    else
        cout << "(B)";
    cout << root->name << '-' << root->age << '-' << root->gender << endl;
    
    if (root->right != nullptr)
        recursivePrint(root->right, depth+2);
}

void RBTree::print() const {
    if (root == nullptr)
        return;
    
    recursivePrint(root, 0);
    cout << endl << endl;
}
