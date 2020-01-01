#include <iostream>
#include <vector>
using namespace std;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

void dfs(int n, int m, vector<string> &grid, int i, int j){
    if(i < 0 or i >= n  or j < 0 or j >= m) return;
    if(grid[i][j] != 'X') return;
    grid[i][j] = '-';
    for(int z = 0; z < 4; z++) dfs(n, m, grid, i + dx[z], j + dy[z]);
}

int count_x_components(int n, int m, vector<string> &grid){
    int ans = 0;
    
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) if(grid[i][j] == 'X'){
        dfs(n, m, grid, i, j);
        ans++;
    }
    
    return ans;
}

int main(){
    int t;
    for(cin >> t; t > 0; t--){
        int n, m;
        cin >> n >> m;
        vector<string> grid(n);
        for(int i=0; i<n; i++) cin >> grid[i];
        cout << count_x_components(n, m, grid) << '\n';
    }
    return 0;
}
