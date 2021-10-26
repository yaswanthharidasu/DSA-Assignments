#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <stdlib.h>
#include <algorithm>
using namespace std;

// Node of Trie
class Node {
public:
	char data;
	// For 26 letters
	Node* children[26];
	bool isTerminal;
	string word;
	// Constructor
	Node(char c);
};

Node::Node(char c) {
	data = c;
	isTerminal = false;
	for (int i = 0; i < 26; i++) {
		children[i] = NULL;
	}
	word = "";
}

class Trie {
private:
	Node* root;

public:
	Trie();
	// Inserts the given word into trie
	void insert(string word);
	// Searches for the given word
	int search(string word);
	// Find autocomplete words
	vector<string> autoComplete(string word);
	// Find autocorrect words 
	vector<string> autoCorrect(string word);

	void levenshteinDistance(Node* temp, char letter, string word, vector<int>& previousRow, vector<string>& result, int maxDist);
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
	temp->word = word;
}

int Trie::search(string word) {
	Node* temp = root;
	for (char letter : word) {
		int index = letter - 'a';
		// Letter is not found in children
		if (temp->children[index] == NULL)
			return 0;
		temp = temp->children[index];
	}
	// Returning true if it is terminal
	return temp->isTerminal ? 1 : 0;
}

vector<string> Trie::autoComplete(string word) {
	Node* temp = root;
	vector<string> result;
	// Traversing in the trie
	for (char letter : word) {
		int index = letter - 'a';
		if (temp->children[index] == NULL) {
			return result;
		}
		temp = temp->children[index];
	}

	// Finding words begin with the given word
	stack<pair<Node*, string>> st;
	st.push(make_pair(temp, word));

	while (!st.empty()) {
		Node* tmp = st.top().first;
		string word = st.top().second;
		st.pop();
		if (tmp->isTerminal)
			result.push_back(word);
		for (int i = 25; i >= 0; i--) {
			if (tmp->children[i] == NULL) {
				continue;
			}
			st.push(make_pair(tmp->children[i], word + char(i + 97)));
		}
	}
	return result;
}

vector<string> Trie::autoCorrect(string word) {
	vector<string>result;
	vector<int> currentRow(word.length() + 1);
	for (int i = 0; i < currentRow.size(); i++) {
		currentRow[i] = i;
	}

	Node* temp = root;
	for (int i = 0; i < 26; i++) {
		if (temp->children[i] != NULL)
			levenshteinDistance(temp->children[i], char(i + 97), word, currentRow, result, 3);
	}
	return result;
}

void Trie::levenshteinDistance(Node* temp, char letter, string word, vector<int>& previousRow, vector<string>& result, int maxDist) {
	vector<int> currentRow;
	currentRow.push_back(previousRow[0] + 1);
	int length = word.length() + 1;
	for (int i = 1; i < length; i++) {
		int distance;
		if (word[i - 1] == letter) {
			distance = previousRow[i - 1];
		}
		else {
			distance = min({ previousRow[i - 1], previousRow[i], currentRow[i - 1] }) + 1;
		}
		currentRow.push_back(distance);
	}

	if (currentRow.back() <= maxDist && temp->word != "") {
		result.push_back(temp->word);
	}
	if (*min_element(currentRow.begin(), currentRow.end()) <= maxDist) {
		for (int i = 0; i < 26; i++) {
			if (temp->children[i] != NULL)
				levenshteinDistance(temp->children[i], char(i + 97), word, currentRow, result, 3);
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector<string> words(n);
	Trie t;
	for (int i = 0; i < n; i++) {
		cin >> words[i];
		t.insert(words[i]);
	}
	int ai;
	string ti;
	cin >> ai >> ti;
	if (ai == 1) {
		cout << t.search(ti);
	}
	else if (ai == 2) {
		vector<string> result = t.autoComplete(ti);
		cout << result.size() << endl;
		for (auto it : result)
			cout << it << endl;
	}
	else if (ai == 3) {
		vector<string> result = t.autoCorrect(ti);
		cout << result.size() << endl;
		for (auto it : result)
			cout << it << endl;
	}
}