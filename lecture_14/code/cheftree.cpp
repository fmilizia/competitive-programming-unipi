#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
using namespace std;

const long long INF = 2e9 + 1;

struct Fenwick{ //0-based, valid positions from 0 to n-1.
    int n;
    vector<int> v;
    void build(int n){
        this->n = n;
        v = vector<int>(n+1, 0);
    }
    void update(int pos, int val){
        for(pos++; pos <= n; pos += pos&-pos) v[pos] += val;
    }
    int query(int pos){
        if(pos >= n) pos = n - 1;
        int ans = 0;
        for(pos++; pos > 0; pos -= pos&-pos) ans += v[pos];
        return ans;
    }
};


struct MaxSegmentTree{
    int left_extreme, right_extreme;
    vector<pair<long long,int>> vec;
    vector<long long> must_propagate;
    
    void make_tree(int v, int l, int r, const vector<int> &vals){
        if(l == r) vec[v] = make_pair(vals[l], l);
        else{
            make_tree(2*v, l, (l+r)/2, vals);
            make_tree(2*v+1, (l+r)/2+1, r, vals);
            vec[v] = max(vec[2*v], vec[2*v+1]);
        }
    }
    
    void build(int left_extreme, int right_extreme, const vector<int> &vals){
        this->left_extreme = left_extreme;
        this->right_extreme = right_extreme;
        vec = vector<pair<long long,int>>(4*(right_extreme - left_extreme + 1));
        must_propagate = vector<long long>(4*(right_extreme - left_extreme + 1),0);
        
        make_tree(1, left_extreme, right_extreme, vals);
    }
    
    void propagate(int v){
        vec[2*v].first += must_propagate[v];
        must_propagate[2*v] += must_propagate[v];
        vec[2*v+1].first += must_propagate[v];
        must_propagate[2*v+1] += must_propagate[v];
        must_propagate[v] = 0;
    }
    
    void inc(int v, int l, int r, int from, int to, long long val){
        if(to < l or r < from) return;
        if(from <= l and r <= to){
            vec[v].first += val;
            must_propagate[v] += val;
        }else{
            propagate(v);
            inc(2*v, l, (l+r)/2, from, to, val);
            inc(2*v+1, (l+r)/2+1, r, from, to, val);
            vec[v] = max(vec[2*v], vec[2*v+1]);
        }
    }
    
    pair<long long,int> rmq(int v, int l, int r, int from, int to){
        if(to < l or from > r) return make_pair(-2*INF, -1);
        if(from <= l and r <= to) return vec[v];
        propagate(v);
        return max(rmq(2*v, l, (l+r)/2, from, to), rmq(2*v+1, (l+r)/2+1, r, from, to));
    }
    
    void inc(int from, int to, long long val){
        inc(1, left_extreme, right_extreme, from, to, val);
    }
    pair<long long,int> rmq(int from, int to){
        return rmq(1, left_extreme, right_extreme, from, to);
    }
};


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

int id = 0;

struct Chain{
    int mid;
    vector<Vertex*> v;
    Vertex *father;
    
    MaxSegmentTree st;
    Fenwick f;
    
    void append_vertex(Vertex *vert){v.push_back(vert);}
    void build(){ // Build the data structure
        mid = id++;
        int n = v.size();
        vector<int> c(n);
        for(int i=0; i<n; i++) c[i] = v[i]->color;
        
        st.build(0, n-1, c);
        f.build(n);
    }
    
    void add(int l, int r, int w){
        st.inc(l, r, w);
    }
    
    int query(int l, int r, long long c){
        int pos; long long val;
        tie(val, pos) = st.rmq(l, r);
        while(val >= c){
            st.inc(pos, pos, -val-2*INF);
            f.update(pos, 1);
            tie(val, pos) = st.rmq(l, r);
        }
        int ans = f.query(r);
        if(l > 0) ans -= f.query(l-1);
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

void test_case(){
    int n, q;
    cin >> n >> q;
    
    int A, B;
    cin >> A >> B; // Assumption: A >= 0.
    int C = 0;
    if(A == 0 and B >= 0) C = -INF;
    if(A == 0 and B < 0) C = INF;
    if(A > 0 and B >= 0) C = -(B/A);
    if(A > 0 and B < 0) C = (-B + A - 1)/A;
    // Now the condition is C_v >= C.
    
    vector<Vertex> vertices(n + 1); // Vertices numbered from 1 to n.
    for(int i=1; i<=n; i++) cin >> vertices[i].color;
    
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
        
        if(command == 2){
            int a, b;
            cin >> a >> b;
            
            Vertex *x = &vertices[a];
            Vertex *y = &vertices[b];
            
            int ans = 0;
            
            while(x != y){
                if(x->chain == y->chain){
                    if(x->depth > y->depth) swap(x, y); // Now y is furthest down in the tree
                    ans = ans + y->chain->query(x->chain_position + 1, y->chain_position, C);
                    y = x;
                }else{
                    if(y->chain->father == nullptr) swap(x, y);
                    else if(not (x->chain->father == nullptr) and (y->chain->father->depth < x->chain->father->depth)) swap(x,y);
                    ans = ans + y->chain->query(0, y->chain_position, C);
                    y = y->chain->father;
                }
            }
            ans += x->chain->query(x->chain_position, x->chain_position, C);
            
            cout << ans << '\n';
        }else{
            int a, b, w;
            cin >> a >> b >> w;
            
            Vertex *x = &vertices[a];
            Vertex *y = &vertices[b];
            
            while(x != y){
                if(x->chain == y->chain){
                    if(x->depth > y->depth) swap(x, y); // Now y is furthest down in the tree
                    y->chain->add(x->chain_position + 1, y->chain_position, w);
                    y = x;
                }else{
                    if(y->chain->father == nullptr) swap(x, y);
                    else if(not (x->chain->father == nullptr) and (y->chain->father->depth < x->chain->father->depth)) swap(x,y);
                    y->chain->add(0, y->chain_position, w);
                    y = y->chain->father;
                }
            }
            x->chain->add(x->chain_position, x->chain_position, w);
        }
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int t;
    cin >> t;
    for(int i=1; i<=t; i++){
        test_case();
    }
    
    return 0;
}
