#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(vector<vector<int>> &adj, int v, vector<bool> &visited, vector<int> &finished){
    if(visited[v]) return;
    visited[v] = true;
    for(int u:adj[v]) dfs(adj, u, visited, finished);
    finished.push_back(v);
}

int main(){
    int n;
    cin >> n;
    
    vector<int> cost(n);
    for(int i=0; i<n; i++) cin >> cost[i];
    
    int m;
    cin >> m;
    
    vector<vector<int>> adj(n);
    vector<vector<int>> rev_adj(n);
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }
    
    vector<bool> visited(n, false);
    vector<int> f;
    for(int v=0; v<n; v++) if(not visited[v]) dfs(adj, v, visited, f);
    
    reverse(f.begin(), f.end());
    for(int i=0; i<n; i++) visited[i] = false;
    
    long long total_cost = 0;
    long long count_solutions = 1;
    
    for(int v:f){
        if(visited[v]) continue;
        
        vector<int> scc;
        dfs(rev_adj, v, visited, scc);
                
        int min_cost = cost[scc[0]] + 1;
        int how_many = 1;
        for(int x:scc){
            if(cost[x] == min_cost) how_many++;
            else if(cost[x] < min_cost){
                how_many = 1;
                min_cost = cost[x];
            }
        }
        
        total_cost += min_cost;
        count_solutions = count_solutions * how_many % 1000000007;
    }
    
    cout << total_cost << ' ' << count_solutions << '\n';
    return 0;
}
