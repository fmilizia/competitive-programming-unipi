#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;

vector<LL> nle(int n, const vector<LL> &a){
    vector<LL> ans(n);
    vector<LL> q;
    for(int i=n-1; i>=0; i--){
        while(not q.empty() and q.back() <= a[i]) q.pop_back();
        ans[i] = q.empty() ? -1 : q.back();
        q.push_back(a[i]);
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    for(int t=0; t<T; t++){
        int n; cin >> n;
        vector<LL> a(n);
        for(int i=0; i<n; i++) cin >> a[i];
        vector<LL> ans = nle(n, a);
        for(LL x:ans) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
