#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i=1; i<=n; i++) cin >> a[i];
    
    vector<int> v(n + 1, 0);
    for(int i=1; i<=q; i++){
        int l, r; cin >> l >> r;
        v[l]++;
        if(r < n) v[r+1]--;
    }
    for(int i=1; i<=n; i++) v[i] += v[i-1];
    
    vector<int> ord(n + 1);
    for(int i=0; i<=n; i++) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int i, int j){return v[i] < v[j];});
    sort(a.begin(), a.end());
    
    long long ans = 0;
    for(int i=1; i<=n; i++) ans += (long long)v[ord[i]] * a[i];
    
    cout << ans << '\n';
    return 0;
}
