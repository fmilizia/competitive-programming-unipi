#include <iostream>
#include <vector>
using namespace std;

long long wilbur(vector<int> v){
    int n = v.size();
    
    long long ans = abs(v[0]);
    for(int i=1; i<n; i++) ans += abs(v[i] - v[i-1]);
    
    return ans;
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    cout << wilbur(v) << '\n';
    return 0;
}
