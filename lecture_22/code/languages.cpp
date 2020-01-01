#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<int>> &adj, int v, vector<bool> &visited){
    if(visited[v]) return;
    visited[v] = true;
    
    for(int u:adj[v]) dfs(adj, u, visited);
}

int main(){
    int n, m;
    cin >> n >> m;
    // Employees numbered 0...n-1; languages numbered n...n+m-1.
    
    vector<vector<int>> adj(n+m);
    
    for(int i=0; i<n; i++){
        int k; cin >> k;
        adj[i].reserve(k);
        for(int j=0; j<k; j++){
            int language;
            cin >> language;
            language += n - 1;
            
            adj[i].push_back(language);
            adj[language].push_back(i);
        }
    }
    
    int components = 0;
    vector<bool> visited(n+m, false);
    for(int i=0; i<n; i++) if(not visited[i]){
        dfs(adj, i, visited);
        components++;
    }
    
    int visited_languages = 0;
    for(int i=n; i<n+m; i++) if(visited[i]) visited_languages++;
    
    if(visited_languages > 0) cout << components - 1 << '\n';
    else cout << components << '\n';
    
    return 0;
}
