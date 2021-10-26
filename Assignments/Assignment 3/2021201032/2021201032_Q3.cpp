#include<iostream>
#include<string>
#define MAX_SIZE 10
using namespace std;

// Node of Trie
class Node {
public:
    char data;
    // For 26 letters
    Node* children[26];
    bool isTerminal, found;
    // Constructor
    Node(char c);
};

Node::Node(char c) {
    data = c;
    isTerminal = found = false;
    for (int i = 0; i < 26; i++) {
        children[i] = NULL;
    }
}

class Trie {
public:
    Node* root;
    Trie();
    // Inserts the given word into trie
    void insert(string word);
};

Trie::Trie() {
    root = new Node('\0');
}

void Trie::insert(string word) {
    Node* temp = root;
    for (char letter : word) {
        int index = letter - 'a';
        // Not present
        if (temp->children[index] == NULL) {
            Node* letterNode = new Node(letter);
            temp->children[index] = letterNode;
        }
        temp = temp->children[index];
    }
    // Make the last letter as terminal
    temp->isTerminal = true;
}

// Grid of size 10x10
char grid[MAX_SIZE][MAX_SIZE];
// Max no.of words = 10 and max length of each word = 10
// char words[MAX_SIZE][MAX_SIZE];
string words[MAX_SIZE];

// No.of rows, columns, words in the list
int r, c, x;

int xloc[4] = { 0, 1, -1, 0 };
int yloc[4] = { 1, 0, 0, -1 };

// DFS Helper: Returns if a cell is valid cell or not
bool valid(int i, int j) {
    return i >= 0 && j >= 0 && i < r&& j < c;
}

void DFS(Node* temp, int i, int j) {
    int cell = grid[i][j];
    // Making cell visited
    grid[i][j] = '#';
    // Node is terminal (.i.e. valid word)
    if (temp->isTerminal) {
        temp->found = true;
    }
    // Checking adjacent cells
    for (int k = 0; k < 4; k++) {
        int a = i + xloc[k], b = j + yloc[k];
        // Valid adjacent cell
        if (valid(a, b)) {
            int index = grid[a][b] - 'a';
            // Unvisited && adjacent cell character is children of that node
            if (grid[a][b] != '#' && temp->children[index] != NULL) {
                DFS(temp->children[index], a, b);
            }
        }
    }
    // Making cell unvisited
    grid[i][j] = cell;
}

void printWords(string ans, Node* temp) {
    if (temp->isTerminal && temp->found) {
        cout << ans << " ";
    }
    for (int i = 0; i < 25; i++) {
        if (temp->children[i] != NULL) {
            printWords(ans + char(i + 97), temp->children[i]);
        }
    }
}

int main() {
    // Trie object
    Trie t;
    // Reading no.of rows and columns
    cin >> r >> c;
    // Reading the values of grid
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }
    // Reading no.of words in the list
    cin >> x;
    // Storing all the words and inserting them into trie
    for (int i = 0; i < x; i++) {
        cin >> words[i];
        t.insert(words[i]);
    }

    // Finding the common words
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int index = grid[i][j] - 'a';
            Node* temp = t.root;
            // Character present in that node
            if (temp->children[index] != NULL) {
                DFS(temp->children[index], i, j);
            }
        }
    }
    printWords("", t.root);
    return 0;
}