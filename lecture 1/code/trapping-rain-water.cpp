#include <iostream>
#include <vector>
using namespace std;

long long water(const vector<int> &a){
    long long ans = 0;
    int running_max = 0;
    for(int i=0; i<(int)a.size(); i++){
        running_max = max(running_max, a[i]);
        ans += running_max;
        ans -= a[i];
    }
    running_max = 0;
    for(int i=a.size() - 1; i>=0; i--){
        running_max = max(running_max, a[i]);
        ans += running_max;
    }
    ans -= (long long)running_max * a.size();
    return ans;
}

int main(){
    int T;
    cin >> T;
    for(int t=0; t<T; t++){
        int n; cin >> n;
        vector<int> a(n);
        for(int i=0; i<n; i++) cin >> a[i];
        cout << water(a) << '\n';
    }
    return 0;
}
