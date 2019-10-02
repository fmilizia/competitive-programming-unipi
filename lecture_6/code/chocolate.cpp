#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> t(n);
    
    for(int i=0; i<n; i++) cin >> t[i];
    int sum = 0;
    for(int i=0; i<n; i++) sum += t[i];
    
    int a = 0, b = 0;
    int alice = 0, bob = 0;
    while(a + b < n){
        if(alice <= bob){
            alice += t[a];
            a++;
        }else{
            bob += t[n-1-b];
            b++;
        }
    }
    cout << a << ' ' << b << '\n';
    return 0;
}
