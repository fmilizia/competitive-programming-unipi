#include <iostream>
#include <vector>
using namespace std;

int main(){
    int T;
    cin >> T;
    for(int t=0; t<T; t++){
        int n; cin >> n;
        vector<int> a(n);
        vector<bool> leader(n, false);
        for(int i=0; i<n; i++) cin >> a[i];
        
        int maximum = 0;
        for(int i=n-1; i>=0; i--) if(a[i] >= maximum){
                maximum = a[i];
                leader[i] = true;
        }
        
        for(int i=0; i<n; i++) if(leader[i]) cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}
