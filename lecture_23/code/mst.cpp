#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct UnionFind{
    vector<int> lab;
    UnionFind(int n){
        lab.resize(n);
        for(int i=0; i<n; i++) lab[i] = i;
    }
    
    int find(int v){
        if(lab[v] == v) return v;
        return lab[v] = find(lab[v]);
    }
    bool same(int u, int v){
        return find(u) == find(v);
    }
    void join(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return;
        lab[u] = v;
    }
};

struct Edge{
    int from, to;
    int cost;
    Edge(int from, int to, int cost): from(from), to(to), cost(cost) {}
    bool operator < (const Edge &other) const {
        return cost < other.cost;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges;
    
    for(int i=0; i<m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        
        edges.emplace_back(a, b, c);
    }
    
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    long long ans = 0;
    for(Edge e:edges){
        if(uf.same(e.from, e.to)) continue;
        ans += e.cost;
        uf.join(e.from, e.to);
    }
    
    cout << ans << '\n';
    return 0;
}
