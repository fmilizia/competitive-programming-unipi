#include <iostream>
#include <vector>
using namespace std;

int score(string s){
    int n = s.size();
    
    int ans = 1;
    for(int i=1; i<n; i++) if(s[i] != s[i-1]) ans++;
    
    return min(n, ans + 2);
}

int main(){
    int n; cin >> n;
    string s; cin >> s;
    cout << score(s) << '\n';
    return 0;
}
