#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_C = 1e5; // Upper bound on the color of a vertex.

struct Fenwick{ //0-based, valid positions from 0 to n-1.
    int n;
    vector<int> v;
    Fenwick(int n): n(n), v(n+1, 0) {}
    
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

struct ColorCounter{
    vector<int> freq;
    Fenwick f;
    int number_of_colors; // Valid colors: from 0 to number_of_colors - 1.
                          // The maximum frequency of a color must be less than max_k at any time.
    ColorCounter(int number_of_colors, int max_k): freq(number_of_colors, 0), f(max_k), number_of_colors(number_of_colors){
        f.update(0, number_of_colors);
    }
    
    void add(int color){
        f.update(freq[color], -1);
        freq[color]++;
        f.update(freq[color], 1);
    }
    void remove(int color){
        f.update(freq[color], -1);
        freq[color]--;
        f.update(freq[color], 1);
    }
    int count_at_least(int k){
        return number_of_colors - f.query(k - 1);
    }
};

struct Query{
    int vertex;
    int k;
    int answer = 0;
};

struct Vertex{
    int color;
    vector<Vertex*> adj;
    int weight;
    vector<Query*> queries;
};


void calc_weight(Vertex *v, Vertex *father){
    v->weight = 1;
    for(auto u:v->adj) if(u != father){
        calc_weight(u, v);
        v->weight += u->weight;
    }
}

void remove_colors(Vertex *v, Vertex *father, ColorCounter &cc){
    cc.remove(v->color);
    for(auto u:v->adj) if(u != father) remove_colors(u, v, cc);
}
void add_colors(Vertex *v, Vertex *father, ColorCounter &cc){
    cc.add(v->color);
    for(auto u:v->adj) if(u != father) add_colors(u, v, cc);
}

void calc_answers(Vertex *v, Vertex *father, ColorCounter &cc){
    Vertex *heavy_child = nullptr;
    for(auto u:v->adj) if(u != father){
        if(heavy_child == nullptr or heavy_child->weight < u->weight){
            heavy_child = u;
        }
    }
    
    for(auto u:v->adj) if(u != father and u != heavy_child){
        calc_answers(u, v, cc);
        remove_colors(u, v, cc);
    }
    
    if(heavy_child != nullptr) calc_answers(heavy_child, v, cc);
    for(auto u:v->adj) if(u != father and u != heavy_child) add_colors(u, v, cc);
    cc.add(v->color);
    
    for(auto q:v->queries){
        q->answer = cc.count_at_least(q->k);
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    
    int n, m;
    cin >> n >> m;
    
    vector<Vertex> vertices(n + 1);
    
    for(int i=1; i<=n; i++) cin >> vertices[i].color;
    
    for(int i=0; i<n-1; i++){
        int a, b;
        cin >> a >> b;
        vertices[a].adj.push_back(&vertices[b]);
        vertices[b].adj.push_back(&vertices[a]);
    }
    
    vector<Query> queries(m);
    for(int i=0; i<m; i++){
        cin >> queries[i].vertex >> queries[i].k;
        vertices[queries[i].vertex].queries.push_back(&queries[i]);
    }
    
    calc_weight(&vertices[1], nullptr);
    
    ColorCounter cc(MAX_C + 1, n + 1);
    calc_answers(&vertices[1], nullptr, cc);
    
    for(int i=0; i<m; i++) cout << queries[i].answer << '\n';
    return 0;
}
