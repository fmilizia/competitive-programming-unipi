#include <vector>
#include <iostream>
using namespace std;

pair<int,int> vertex_cover(const vector<vector<int>> &adj, int v, int p){
	pair<int,int> ans(0,1);
	
	for(int u:adj[v]) if(u != p){
		auto a = vertex_cover(adj, u, v);
		ans.second += a.first;
		ans.first += a.second;
	}
	
	ans.first = min(ans.first, ans.second);
	return ans;
}

int main(){
	int n;
	cin >> n;
	
	vector<vector<int>> adj(n+1);
	for(int i=0; i<n-1; i++){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	cout << vertex_cover(adj, 1, 0).first << '\n';
	
	return 0;
}
