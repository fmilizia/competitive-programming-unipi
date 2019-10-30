#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Chain;
struct Vertex;
struct Edge;



struct Vertex{
    int id;
    
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
    set<int> blacks;
    
    void append_vertex(Vertex *vert){v.push_back(vert);}
    void build(){ // Build the data structure
    }
    
    void change(int position){
        if(blacks.count(position)) blacks.erase(position);
        else blacks.insert(position);
    }
    
    Vertex* query(int r){
        if(blacks.empty()) return nullptr;
        int f = *blacks.begin();
        if(f <= r) return v[f];
        return nullptr;
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
    
    int n, q; 
    cin >> n >> q;
    
    vector<Vertex> vertices(n + 1); // Vertices numbered from 1 to n
    for(int i=1; i<=n; i++) vertices[i].id = i;
    
    for(int i=0; i<n-1; i++){
        int a, b; cin >> a >> b;
        vertices[a].adj.emplace_back(&vertices[a], &vertices[b]);
        vertices[b].adj.emplace_back(&vertices[b], &vertices[a]);
    }
    
    traverse_tree(&vertices[1], nullptr);
    heavy_light_decomposition(&vertices[1], nullptr, new Chain());
        
    for(int qq = 0; qq < q; qq++){
        int command;
        cin >> command;
        if(command == 0){
            int i;
            cin >> i;
            
            Vertex *x = &vertices[i];            
            x->chain->change(x->chain_position);
        }else if(command == 1){
            int v;
            cin >> v;
            
            Vertex *y = &vertices[v];
            
            int ans = -1;
            
            while(y != nullptr){
                Vertex *a = y->chain->query(y->chain_position);
                if(a != nullptr) ans = a->id;
                y = y->chain->father;
            }
            
            cout << ans << '\n';
        }
    }

    

    return 0;
}
