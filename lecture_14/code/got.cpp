#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Chain;
struct Vertex;
struct Edge;



struct Vertex{
    int color;
    
    vector<Edge> adj;
    Vertex *heavy_child;
    int chain_position; // 0-based.
    Chain *chain;
    
    int depth;
    bool heavy;
};

struct Edge{
    Vertex *from;
    Vertex *to;
    Edge(Vertex *from, Vertex *to): from(from), to(to) {}
};

struct Chain{
    vector<Vertex*> v;
    Vertex *father;
    vector<pair<int,int>> cells;
    
    void append_vertex(Vertex *vert){v.push_back(vert);}
    void build(){ // Build the data structure
        int n = v.size();
        cells.clear();
        cells.reserve(n);
        for(int i=0; i<n; i++) cells.emplace_back(v[i]->color, i);
        sort(cells.begin(), cells.end());
    }
        
    bool query(int l, int r, int c){
        auto it = lower_bound(cells.begin(), cells.end(), make_pair(c, l));
        if(it == cells.end()) return false;
        return (it->first == c) and (it->second <= r);
    }
};


int traverse_tree(Vertex *v, Vertex *father){ // Compute depths and heavy vertices. Returns the subtree-size of v
    if(father == nullptr) v->depth = 0;
    else v->depth = father->depth + 1;
    
    int sz = 1;
    int curr_max = 0;
    v->heavy_child = nullptr;
    
    for(auto u:v->adj) if(u.to != father){
        int s = traverse_tree(u.to, v);
        if(s > curr_max){
            curr_max = s;
            v->heavy_child = u.to;
        }
        sz += s;
    }
    
    if(v->heavy_child != nullptr) v->heavy_child->heavy = true;
    return sz;
}

void heavy_light_decomposition(Vertex *v, Vertex *father, Chain *current_chain){
    v->chain = current_chain;
    current_chain->append_vertex(v);
    if(not v->heavy) v->chain_position = 0; else v->chain_position = father->chain_position + 1;
        
    for(auto u:v->adj) if(u.to != father){
        if(u.to == v->heavy_child) heavy_light_decomposition(u.to, v, current_chain);
        else heavy_light_decomposition(u.to, v, new Chain());
    }
    
    if(not v->heavy){
        current_chain->father = father;
        current_chain->build();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    while(cin >> n >> m){
        vector<Vertex> vertices(n + 1); // Vertices numbered from 1 to n
        for(int i=1; i<=n; i++) cin >> vertices[i].color;
        
        for(int i=0; i<n-1; i++){
            int a, b; cin >> a >> b;
            vertices[a].adj.emplace_back(&vertices[a], &vertices[b]);
            vertices[b].adj.emplace_back(&vertices[b], &vertices[a]);
        }
        
        traverse_tree(&vertices[1], nullptr);
        heavy_light_decomposition(&vertices[1], nullptr, new Chain());
            
        for(int qq = 0; qq < m; qq++){
            int a, b, c;
            cin >> a >> b >> c;
            Vertex *x = &vertices[a];
            Vertex *y = &vertices[b];
            
            bool found = false;
            
            while(x != y){
                if(x->chain == y->chain){
                    if(x->depth > y->depth) swap(x, y); // Now y is furthest down in the tree
                    found = found or y->chain->query(x->chain_position, y->chain_position, c);
                    y = x;
                }else{
                    if(y->chain->father == nullptr) swap(x, y);
                    else if(not (x->chain->father == nullptr) and (y->chain->father->depth < x->chain->father->depth)) swap(x,y);
                    found = found or y->chain->query(0, y->chain_position, c);
                    y = y->chain->father;
                }
            }
            if(x->color == c) found = true;
            
            if(found) cout << "Find\n"; else cout << "NotFind\n";
        }
        cout << '\n';
    }
    return 0;
}
