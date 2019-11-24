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
    const int MAXA = 200; // Values between 1 and MAXA.
    
    int t; 
    for(cin >> t; t > 0; t--){
        int n;
        cin >> n;
        
        vector<int> a(n);
        for(int i=0; i<n; i++) cin >> a[i];
        
        vector<int> increasing_prefix(n, 0);
        Fenwick f_inc(MAXA + 1), f_dec(MAXA + 1);
        int ans = 0;
        
        for(int i=0; i<n; i++){
            int newlength = f_inc.query(a[i] - 1) + 1;
            f_inc.update(a[i], newlength);
            increasing_prefix[i] = max(i > 0? increasing_prefix[i-1] : 0, newlength);
        }
        
        for(int i=n-1; i>=0; i--){
            int newlength = f_dec.query(a[i] - 1) + 1;
            f_dec.update(a[i], newlength);
            ans = max(ans, increasing_prefix[i] + newlength - 1);
        }
        
        cout << ans << '\n';
    }
    return 0;
}
