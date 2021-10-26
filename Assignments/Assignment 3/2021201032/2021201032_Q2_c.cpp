#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, 1, 0, -1 };

bool valid(int i, int j, int r, int c) {
    return i >= 0 && j >= 0 && i < r&& j < c;
}

void DFS(int i, int j, vector<vector<char>>& grid, vector<vector<int>>& dist) {
    // cout << i << " " << endl;
    if (dist[i][j] != INT_MAX) {
        return;
    }
    char cell = grid[i][j];
    grid[i][j] = '$';
    for (int k = 0; k < 4; k++) {
        int a = i + x[k], b = j + y[k];
        if (valid(a, b, grid.size(), grid[0].size()) && grid[a][b] == '.') {
            DFS(a, b, grid, dist);
            if (dist[a][b] != INT_MAX)
                dist[i][j] = min(dist[i][j], dist[a][b] + 1);
        }
    }
    grid[i][j] = cell;
}


int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<char>> grid(m, vector<char>(n));
    vector<pair<int, int>> locations;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'R' || grid[i][j] == 'A') {
                locations.push_back(make_pair(i, j));
            }
        }
    }
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    vector<int> rDist;
    dist[1][0] = 0;
    int minRdist = INT_MAX;
    for (auto it : locations) {
        int i = it.first, j = it.second;
        DFS(i, j, grid, dist);
        if (grid[i][j] == 'R') {
            // rDist.push_back(dist[i][j]);
            minRdist = min(minRdist, dist[i][j]);
        }
        // cout << grid[i][j] << " " << i << " " << j << " " << dist[i][j] << endl;
    }
    int aDist = dist[m - 2][n - 2];
    if (aDist == INT_MAX) {
        cout << "NO" << endl;
    }
    else {
        if (minRdist < aDist) {
            cout << "NO" << endl;
        }
        else {
            cout << "YES" << endl;
            cout << aDist << endl;
        }
    }
}