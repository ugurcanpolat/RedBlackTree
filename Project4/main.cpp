/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 21.12.2017
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o 150140117
 
 * * * * * * * * * * * * * * * * * */

#include <iostream> // cout
#include <fstream> // ifstream
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
  public:
    RBTree();
    void insert(Node*& new_node);
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
    }
    
    // Close the input file since it is no longer needed
    inputFile.close();
    return 0;
}

RBTree::RBTree() {
    root = nullptr;
}

void RBTree::treeInsert(Node*& new_node) {
}

void RBTree::rotateLeft(Node*& rotate_around) {
}

void RBTree::rotateRight(Node*& rotate_around) {
}

void RBTree::insert(Node*& new_node) {
    treeInsert(new_node);
    new_node->color = RED;
    while (new_node != root && (new_node->parent)->color == RED) {
        Node *parent = new_node->parent;
        Node *grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle->color == RED) {
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
            if (uncle->color == RED) {
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
