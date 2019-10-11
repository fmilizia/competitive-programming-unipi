#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n;
    long long k;
    cin >> n >> k;
    
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    
    int a = (k - 1) / n;
    nth_element(v.begin(), v.begin() + a, v.end());
    cout << v[a];
    
    int cnt_equal = count(v.begin(), v.end(), v[a]);
    int cnt_less = count_if(v.begin(), v.end(), [&](int x){return x < v[a];});
    
    int b = (k - 1 - (long long)cnt_less * n) / cnt_equal;
    nth_element(v.begin(), v.begin() + b, v.end());
    cout << ' ' << v[b] << '\n';
    
    return 0;
}
