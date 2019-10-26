#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Stree{
    int left_extreme, right_extreme;
    vector<long long> vec;
    vector<int> must_propagate;
    const long long INF = 1e12;
    
    void make_tree(int v, int l, int r, const vector<int> &vals){
        if(l == r) vec[v] = vals[l];
        else{
            make_tree(2*v, l, (l+r)/2, vals);
            make_tree(2*v+1, (l+r)/2+1, r, vals);
            vec[v] = min(vec[2*v], vec[2*v+1]);
        }
    }
    
    Stree(int left_extreme, int right_extreme, const vector<int> &vals): 
        left_extreme(left_extreme), 
        right_extreme(right_extreme), 
        vec(4*(right_extreme - left_extreme + 1)),
        must_propagate(4*(right_extreme - left_extreme + 1),0) {
            make_tree(1, left_extreme, right_extreme, vals);
    }
    
    void propagate(int v){
        vec[2*v] += must_propagate[v];
        must_propagate[2*v] += must_propagate[v];
        vec[2*v+1] += must_propagate[v];
        must_propagate[2*v+1] += must_propagate[v];
        must_propagate[v] = 0;
    }
    
    void inc(int v, int l, int r, int from, int to, int val){
        if(to < l or r < from) return;
        if(from <= l and r <= to){
            vec[v] += val;
            must_propagate[v] += val;
        }else{
            propagate(v);
            inc(2*v, l, (l+r)/2, from, to, val);
            inc(2*v+1, (l+r)/2+1, r, from, to, val);
            vec[v] = min(vec[2*v], vec[2*v+1]);
        }
    }
    
    long long rmq(int v, int l, int r, int from, int to){
        if(to < l or from > r) return INF;
        if(from <= l and r <= to) return vec[v];
        propagate(v);
        return min(rmq(2*v, l, (l+r)/2, from, to), rmq(2*v+1, (l+r)/2+1, r, from, to));
    }
    
    void inc(int from, int to, int val){
        inc(1, left_extreme, right_extreme, from, to, val);
    }
    long long rmq(int from, int to){
        return rmq(1, left_extreme, right_extreme, from, to);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n; cin >> n;
    
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    
    Stree st(0, n-1, a);
    
    int m; cin >> m;
    for(int i=0; i<m; i++){
        string s = "";
        while(s == "") getline(cin, s);
        istringstream ss(s);
        
        int l, r, v;
        ss >> l >> r;
        if(ss >> v){
            if(l <= r) st.inc(l, r, v);
            else {st.inc(0, r, v); st.inc(l, n-1, v);}
        }else{
            if(l <= r) cout << st.rmq(l, r) << '\n';
            else cout << min(st.rmq(0,r), st.rmq(l, n-1)) << '\n';
        }
    }
    return 0;
}
