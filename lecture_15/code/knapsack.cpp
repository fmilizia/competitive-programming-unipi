#include <iostream>
#include <vector>
using namespace std;


int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    int s, n;
    cin >> s >> n;
    vector<int> max_value(s+1, 0);
    for(int i=0; i<n; i++){
        int sz, val;
        cin >> sz >> val;
        for(int c=s; c>=sz; c--) max_value[c] = max(max_value[c], max_value[c-sz]+val);
    }
    for(int c=1; c<=s; c++) max_value[c] = max(max_value[c], max_value[c-1]);
    cout << max_value[s] << '\n';
    
    return 0;
}
