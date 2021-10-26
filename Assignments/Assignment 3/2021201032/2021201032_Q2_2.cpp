#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, 1, 0, -1 };

bool valid(int i, int j, int r, int c) {
    return i >= 0 && j >= 0 && i < r&& j < c;
}

struct node {
    vector<string> paths;
};
struct node distances[21];

void DFS(int index, vector<vector<int>>& graph, vector<bool>& visited, string path, int dist, int start) {
    visited[index] = true;
    if (index > start) {
        distances[dist].paths.push_back(path);
        // cout<<dist<<endl;
        // cout<<path<<endl;
    }
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        if (graph[index][i] != 0 && !visited[i]) {
            // cout << endl;
            DFS(i, graph, visited, path + " " + to_string(i), dist + graph[index][i], start);
        }
    }
    visited[index] = false;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    for (int i = 0; i < m; i++) {
        int a, b, wt;
        cin >> a >> b >> wt;
        graph[a][b] = graph[b][a] = wt;
    }
    int k;
    cin >> k;
    for (int i = 0; i < n - 1; i++) {
        DFS(i, graph, visited, to_string(i), 0, i);
    }
    for(int i=0; i<21; i++){
        vector<string> ans = distances[i].paths;
        for(int j=0; j<ans.size(); j++){
            cout<<ans[j]<<endl;
            k--;
            if(k==0)
                break;
        }
        if(k==0)
            break;
    }
}

