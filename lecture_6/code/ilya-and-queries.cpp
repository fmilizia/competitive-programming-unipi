#include <iostream>
#include <vector>
using namespace std;

int main(){
    string s; cin >> s;
    int n = s.size();
    
    vector<int> psum(1 + n, 0);
    psum[0] = 0;
    for(int i=1; i<n; i++){
        psum[i] = psum[i-1];
        if(s[i-1] == s[i]) psum[i]++;
    }
    
    
    
    int m; cin >> m;
    for(int i=0; i<m; i++){
        int l, r;
        cin >> l >> r;
        cout << psum[r-1] - psum[l-1] << '\n';
    }
    
    return 0;
}
