#include <iostream>
#include <vector>
using namespace std;

struct Fenwick{ //0-based, valid positions from 0 to n-1. Computes max on prefixes.
    int n;
    vector<int> v;
    void build(int n){
        this->n = n;
        v = vector<int>(n+1, 0);
    }
    Fenwick(): n(0) {}
    Fenwick(int n){
        build(n);
    }
    void update(int pos, int val){
        for(pos++; pos <= n; pos += pos&-pos) v[pos] = max(v[pos], val);
    }
    int query(int pos){
        if(pos >= n) pos = n - 1;
        int ans = 0;
        for(pos++; pos > 0; pos -= pos&-pos) ans = max(ans, v[pos]);
        return ans;
    }
};


int main(){
    const int MAXA = 300;
    
    int t; 
    for(cin >> t; t > 0; t--){
        int n;
        cin >> n;
        
        Fenwick f(MAXA + 1);
        
        for(int i=0; i<n; i++){
            int a; cin >> a;
            f.update(a, f.query(a - 1) + 1);
        }
        
        cout << f.query(MAXA) << '\n';
    }
    return 0;
}
