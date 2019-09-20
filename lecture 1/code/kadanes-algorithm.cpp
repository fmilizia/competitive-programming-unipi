#include <iostream>
#include <vector>
using namespace std;

long long kadane(const vector<int> &a){
    const long long INF = 1e14;
    
    long long ans = -INF;
    long long current_sum = 0;
    for(int x:a){
        if(current_sum < 0) current_sum = x;
        else current_sum += x;
        ans = max(ans, current_sum);
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    for(int t=0; t<T; t++){
        int n; cin >> n;
        vector<int> a(n);
        for(int i=0; i<n; i++) cin >> a[i];
        cout << kadane(a) << '\n';
    }
    return 0;
}
