#include <iostream>
using namespace std;

int main(){
    int T;
    cin >> T;
    for(int t=0; t<T; t++){
        int n; cin >> n;
        int x = n;
        for(int i=1; i<n; i++){
            int a; cin >> a;
            x ^= a;
            x ^= i;
        }
        cout << x << '\n';
    }
    return 0;
}
