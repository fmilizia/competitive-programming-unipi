#include <iostream>
#include <vector>
using namespace std;


int main(){
    int n;
    cin >> n;
    
    vector<int> cnt(1001, 0);
    int max_height = 0;
    int num = 0;
    
    for(int i=0; i<n; i++){
        int x; cin >> x;
        if(cnt[x] == 0) num++;
        cnt[x]++;
        max_height = max(max_height, cnt[x]);
    }
    
    cout << max_height << ' ' << num << '\n';
    
    return 0;
}
