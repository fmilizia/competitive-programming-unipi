#include <iostream>
#include <vector>
using namespace std;

struct Chain;
struct Vertex;
struct Edge;

struct RmqSegmentTree{    
    int left_extreme, right_extreme;
    vector<int> vec;
    
    void make_tree(int v, int l, int r, const vector<int> &vals){
        if(l == r) vec[v] = vals[l];
        else{
            make_tree(2*v, l, (l+r)/2, vals);
            make_tree(2*v+1, (l+r)/2+1, r, vals);
            vec[v] = max(vec[2*v], vec[2*v+1]);
        }
    }
    
    void build(int left_extreme, int right_extreme, const vector<int> &vals){        
        this->left_extreme = left_extreme;
        this->right_extreme = right_extreme;
        vec = vector<int>(4*(right_extreme - left_extreme + 1));
        make_tree(1, left_extreme, right_extreme, vals);
    }
        
    void change(int v, int l, int r, int pos, int val){
        if(pos < l or r < pos) return;
        if(l < r){
            change(2*v, l, (l+r)/2, pos, val);
            change(2*v+1, (l+r)/2+1, r, pos, val);
            vec[v] = max(vec[2*v], vec[2*v+1]);
        }else{
            vec[v] = val;
        }
    }
    
    int rmq(int v, int l, int r, int from, int to){
        if(to < l or from > r) return 0;
        if(from <= l and r <= to) return vec[v];
        return max(rmq(2*v, l, (l+r)/2, from, to), rmq(2*v+1, (l+r)/2+1, r, from, to));
    }
    
    void change(int pos, int val){
        change(1, left_extreme, right_extreme, pos, val);
    }
    int rmq(int from, int to){
        int ans = rmq(1, left_extreme, right_extreme, from, to);
        return ans;
    }
};




struct Vertex{
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
    RmqSegmentTree st;
    
    void append_vertex(Vertex *vert){v.push_back(vert);}
    void build(){ // Build the data structure
        int n = v.size();
                
        vector<int> costs;
        costs.reserve(n);
        
        if(father == nullptr) costs.push_back(0);
        
        for(auto x:v){
            for(auto e:x->adj) if(e.to->depth < x->depth) 
                costs.push_back(e.cost);
        }
                        
        st.build(0, n-1, costs);
    }
    
    void change(int position, int val){
        st.change(position, val);
    }
    
    int query(int l, int r){
        int ans = st.rmq(l,r);
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
        if(command == "CHANGE"){
            int i, ti;
            cin >> i >> ti;
            
            Edge &e = edges[i - 1]; // Off by one
            Vertex *x = e.to;
            Vertex *y = e.from;
            if(x->depth > y->depth) swap(x, y); // Now x is the father of y
            
            y->chain->change(y->chain_position, ti);
        }else if(command == "QUERY"){
            int a, b;
            cin >> a >> b;
            
            Vertex *x = &vertices[a];
            Vertex *y = &vertices[b];
            
            int ans = 0; // I assume the costs are positive
            
            while(x != y){
                if(x->chain == y->chain){
                    if(x->depth > y->depth) swap(x, y); // Now y is furthest down in the tree
                    ans = max(ans, y->chain->query(x->chain_position + 1, y->chain_position));
                    y = x;
                }else{
                    if(y->chain->father == nullptr) swap(x, y);
                    else if(not (x->chain->father == nullptr) and (y->chain->father->depth < x->chain->father->depth)) swap(x,y);
                    ans = max(ans, y->chain->query(0, y->chain_position));
                    y = y->chain->father;
                }
            }
            
            cout << ans << '\n';
        }
    }
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
