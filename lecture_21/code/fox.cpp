#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// True if a cycle is found.
// node_type = 0 (unvisited), 1 (opened), 2 (closed)
bool dfs(vector<vector<int>> &adj, int v, vector<int> &node_type, vector<int> &finished){
    if(node_type[v] == 1) return true;
    if(node_type[v] == 2) return false;
    node_type[v] = 1;
    for(int u:adj[v]) if(dfs(adj, u, node_type, finished)) return true;
    finished.push_back(v);
    node_type[v] = 2;
    return false;
}

vector<int> topological_sort(vector<vector<int>> &adj){
    int n = adj.size();
    
    vector<int> ans;
    vector<int> node_type(n, 0);
    for(int i=0; i<n; i++) if(node_type[i] == 0){
        if(dfs(adj, i, node_type, ans)){
            ans.clear();
            return ans;
        }
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(){
    int n;
    cin >> n;
    
    vector<string> name(n);
    for(int i=0; i<n; i++){
        cin >> name[i];
        name[i] = name[i] + '$';
    }
    
    vector<vector<int>> adj('z'-'a'+1);
    
    for(int i=0; i<n-1; i++){
        int p = 0;
        while(name[i][p] != '$' and name[i+1][p] != '$' and name[i][p] == name[i+1][p]) p++;
        if(name[i][p] != name[i+1][p]){
            if(name[i+1][p] == '$'){
                cout << "Impossible\n";
                return 0;
            }
            if(name[i][p] != '$'){
                adj[name[i][p] - 'a'].push_back(name[i+1][p] - 'a');
            }
        }
    }
    
    vector<int> ord = topological_sort(adj);
    if(ord.size() == 0){ // The graph is not acyclic
        cout << "Impossible\n";
    }else{ // The graph is acyclic and ord gives a topological sort
        for(int x:ord) cout << (char)('a' + x);
        cout << '\n';
    }
    
    return 0;
}
