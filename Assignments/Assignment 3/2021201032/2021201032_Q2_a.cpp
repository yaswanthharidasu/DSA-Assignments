#include <iostream>
#include <climits>
#include <vector>
#include <list>
using namespace std;
typedef pair<int, int> pd;

// ======================================= Class : Heap =============================================

class Heap {
    // Array that stores vertex and it's distance.
    vector<pd> arr;

    int parent(int index);

    int leftChild(int index);

    int rightChild(int index);

    void swap(pd& a, pd& b);

    void heapifyDown(int index);

    void heapifyUp(int index);


public:
    Heap();

    int size();

    bool empty();

    void push(int vertex, int distance);

    pd pop();

};

Heap::Heap() {
}

int Heap::size() {
    return arr.size();
}

bool Heap::empty() {
    return arr.empty();
}

int Heap::parent(int index) {
    return (index - 1) / 2;
}

int Heap::leftChild(int index) {
    return (2 * index + 1);
}

int Heap::rightChild(int index) {
    return (2 * index + 2);
}

void Heap::swap(pd& a, pd& b) {
    pd temp = a;
    a.first = b.first;
    a.second = b.second;
    b.first = temp.first;
    b.second = temp.second;
}

void Heap::heapifyDown(int index) {
    int leftIndex = leftChild(index);
    int rightIndex = rightChild(index);

    int smallestIndex = index;
    // Comparing with left child
    if (leftIndex < size() && arr[leftIndex].second < arr[smallestIndex].second) {
        smallestIndex = leftIndex;
    }
    // Comparing with right child
    if (rightIndex < size() && arr[rightIndex].second < arr[smallestIndex].second) {
        smallestIndex = rightIndex;
    }
    // Found smaller element in children
    if (smallestIndex != index) {
        swap(arr[smallestIndex], arr[index]);
        heapifyDown(smallestIndex);
    }
}

void Heap::heapifyUp(int index) {
    // If not root
    if (index) {
        int parentIndex = parent(index);
        // Parent is greater than child
        if (arr[parentIndex].second > arr[index].second) {
            swap(arr[parentIndex], arr[index]);
            heapifyUp(parentIndex);
        }
    }
}

void Heap::push(int source, int distance) {
    arr.push_back(make_pair(source, distance));
    heapifyUp(size() - 1);
}

pd Heap::pop() {
    // No elements in heap
    pd temp;
    if (size() == 0)
        return temp;
    temp = arr[0];
    // Replace the first element with last element
    arr[0] = arr[size() - 1];
    arr.pop_back();
    // Heapify
    heapifyDown(0);
    return temp;
}

// ============================================== Class : Graph =========================================================

class Graph {

    list<pd>* graph;
    int vertices;
    int edges;

public:

    Graph(int vertices, int edges) {
        this->vertices = vertices;
        this->edges = edges;
        graph = new list<pd>[vertices];
    }

    void addEdge(int i, int j, int weight, bool undirected = true) {
        graph[i].push_back(make_pair(weight, j));
        if (undirected)
            graph[j].push_back(make_pair(weight, i));
    }

    void dijkstras(int source) {
        vector<int> distance(vertices, INT_MAX);
        vector<int> parent(vertices, -1);
        vector<bool> visited(vertices, false);
        Heap h;
        distance[source] = 0;
        // Pushing source and distance
        h.push(source, 0);
        visited[source] = true;

        while (!h.empty()) {
            pd top = h.pop();
            int src = top.first;
            int dist = top.second;
            visited[src] = true;

            // Explore adjacent vertices
            for (auto it : graph[src]) {
                int edge_weight = it.first;
                int adj = it.second;
                if (!visited[adj]) {
                    if (dist + edge_weight < distance[adj]) {
                        // Update weight and push into heap
                        distance[adj] = dist + edge_weight;
                        h.push(adj, distance[adj]);
                        parent[adj] = src;
                    }
                    else if (dist + edge_weight == distance[adj] && src < parent[adj]) {
                        h.push(adj, distance[adj]);
                        parent[adj] = src;
                    }
                }
            }
        }

        for (int i = 0; i < vertices; i++) {
            if (i == source)
                continue;
            int src = i;
            cout << src << " ";
            while (parent[src] != -1) {
                cout << parent[src] << " ";
                src = parent[src];
            }
            cout << endl;
        }
    }
};


int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    for (int i = 0; i < m; i++) {
        int a, b, wt;
        cin >> a >> b >> wt;
        g.addEdge(a, b, wt);
    }

    int src;
    cin >> src;

    g.dijkstras(src);

    return 0;
}
