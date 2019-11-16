#include <iostream>
#include <vector>
using namespace std;


int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    int t;
    for(cin >> t; t>0; t--){
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;
        vector<int> table[2];
        table[0] = vector<int>(m+1, 0);
        table[1] = vector<int>(m+1, 0);
        for(int i=1; i<=n; i++) for(int j=1; j<=m; j++){
            int i2 = i % 2;
            table[i2][j] = table[i2^1][j-1];
            if(a[i-1] == b[j-1]) table[i2][j]++;
            table[i2][j] = max(table[i2][j], table[i2][j-1]);
            table[i2][j] = max(table[i2][j], table[i2^1][j]);
        }
        cout << table[n%2][m] << '\n';
    }
}
