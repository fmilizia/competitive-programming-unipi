#include <iostream>
#include <vector>
using namespace std;


int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    int t;
    for(cin >> t; t>0; t--){
        int n;
        cin >> n;
        
        vector<int> arr(n);
        int sum = 0;
        for(int i=0; i<n; i++){
            cin >> arr[i];
            sum += arr[i];
        }
        
        if(sum % 2 != 0){
            cout << "NO\n";
            continue;
        }
        
        int s = sum / 2;
        vector<bool> is_sum(s+1, false);
        is_sum[0] = true;
        for(int i=0; i<n; i++){
            int val = arr[i];
            for(int c=s; c>=val; c--) is_sum[c] = is_sum[c] or is_sum[c-val];
        }
        cout << (is_sum[s] ? "YES\n" : "NO\n");
    }
    
    return 0;
}
