#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(){
    int n, u;
    cin >> n >> u;
    
    vector<long long> v(n, 0);
    for(int i=0; i<u; i++){
        int l, r, val;
        cin >> l >> r >> val;
        v[l] += val;
        if(r < n - 1) v[r + 1] -= val;
    }
    for(int i=1; i<n; i++) v[i] += v[i-1];
    
    int q;
    cin >> q;
    for(int i=0; i<q; i++){
        int index;
        cin >> index;
        cout << v[index] << '\n';
    }
}

int main(){
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        solve();
    }
    return 0;
}
