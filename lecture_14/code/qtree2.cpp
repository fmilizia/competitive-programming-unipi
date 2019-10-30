#include <iostream>
#include <vector>
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
    int cost;
    Edge(Vertex *from, Vertex *to, int cost): from(from), to(to), cost(cost) {}
};

struct Chain{
    vector<Vertex*> v;
    Vertex *father;
    vector<int> prefix_sum;
    
    void append_vertex(Vertex *vert){v.push_back(vert);}
    void build(){ // Build the data structure
        int n = v.size();
                
        prefix_sum.reserve(n);
        
        if(father == nullptr) prefix_sum.push_back(0);
        
        for(auto x:v){
            for(auto e:x->adj) if(e.to->depth < x->depth) 
                prefix_sum.push_back(e.cost);
        }
                        
        for(int i=1; i<n; i++) prefix_sum[i] += prefix_sum[i-1];
    }
        
    int query(int l, int r){
        int ans = prefix_sum[r];
        if(l > 0) ans -= prefix_sum[l-1];
        return ans;
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

void solve_testcase(){
    int n; cin >> n;
    vector<Vertex> vertices(n + 1); // Vertices numbered from 1 to n
    for(int i=1; i<=n; i++) vertices[i].id = i;
    vector<Edge> edges;
    edges.reserve(n - 1);
    for(int i=0; i<n-1; i++){
        int a, b, c; cin >> a >> b >> c;
        vertices[a].adj.emplace_back(&vertices[a], &vertices[b], c);
        vertices[b].adj.emplace_back(&vertices[b], &vertices[a], c);
        edges.emplace_back(&vertices[a], &vertices[b], c);
    }
    
    traverse_tree(&vertices[1], nullptr);
    heavy_light_decomposition(&vertices[1], nullptr, new Chain());
        
    string command = "";
    while(command != "DONE"){
        cin >> command;
        if(command == "KTH"){
            int a, b, k;
            cin >> a >> b >> k;
            k--;
            
            if(k == 0) {cout << a << '\n'; continue;}
            
            Vertex *x = &vertices[a];
            Vertex *y = &vertices[b];
            
            int dist = 0;
            while(x != y){
                if(x->chain == y->chain){
                    if(x->depth > y->depth) swap(x, y); // Now y is furthest down in the tree
                    dist += y->chain_position - x->chain_position;
                    y = x;
                }else{
                    if(y->chain->father == nullptr) swap(x, y);
                    else if(not (x->chain->father == nullptr) and (y->chain->father->depth < x->chain->father->depth)) swap(x,y);
                    dist += y->chain_position + 1;
                    y = y->chain->father;
                }
            }
            
            x = &vertices[a];
            y = &vertices[b];
            
            int up_x = k;
            int up_y = dist - k;
            
            while(up_y > 0){
                if(x->chain == y->chain){
                    if(x->depth > y->depth) {swap(x, y); swap(up_x, up_y);} // Now y is furthest down in the tree
                    y = y->chain->v[y->chain_position - up_y];
                    up_y = 0;
                }else{
                    if(y->chain->father == nullptr) {swap(x, y); swap(up_x, up_y);}
                    else if(not (x->chain->father == nullptr) and (y->chain->father->depth < x->chain->father->depth)) {swap(x, y); swap(up_x, up_y);}
                    
                    int jump = y->chain_position + 1;
                    if(jump <= up_y){
                        up_y -= jump;
                        y = y->chain->father;
                    }else{
                        y = y->chain->v[y->chain_position - up_y];
                        up_y = 0;
                    }
                }
            }
            
            cout << y->id << '\n';
        }else if(command == "DIST"){
            int a, b;
            cin >> a >> b;
            
            Vertex *x = &vertices[a];
            Vertex *y = &vertices[b];
            
            int ans = 0;
            
            while(x != y){
                if(x->chain == y->chain){
                    if(x->depth > y->depth) swap(x, y); // Now y is furthest down in the tree
                    ans += y->chain->query(x->chain_position + 1, y->chain_position);
                    y = x;
                }else{
                    if(y->chain->father == nullptr) swap(x, y);
                    else if(not (x->chain->father == nullptr) and (y->chain->father->depth < x->chain->father->depth)) swap(x,y);
                    ans += y->chain->query(0, y->chain_position);
                    y = y->chain->father;
                }
            }
            
            cout << ans << '\n';
        }
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int t; cin >> t;
    for(int i=1; i<=t; i++){
        solve_testcase();
    }
    return 0;
}
