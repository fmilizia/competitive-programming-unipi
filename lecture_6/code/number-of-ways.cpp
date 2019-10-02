#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i=1; i<=n; i++) cin >> a[i];
    
    long long sum = 0;
    for(int i=1; i<=n; i++) sum += a[i];
    if(sum % 3 != 0){cout << "0\n"; return 0;}
    
    long long psum = 0;
    int cnt = 0;
    long long ans = 0;
    
    for(int i=1; i<n; i++){
        psum += a[i];
        if(psum == sum / 3 * 2) ans += cnt;
        if(psum == sum / 3) cnt++;
    }
    
    cout << ans << '\n';
    
    return 0;
}
