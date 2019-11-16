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
        table[0] = vector<int>(m+1, n+m);
        table[1] = vector<int>(m+1, n+m);
        
        table[0][0] = 0;
        for(int i=0; i<=n; i++) for(int j=0; j<=m; j++){
            int i2 = i % 2;
            if(i == 0 and j == 0) continue;
            table[i2][j] = n + m;
            if(i > 0 and j > 0){
                table[i2][j] = table[i2^1][j-1];
                if(a[i-1] != b[j-1]) table[i2][j]++;
            }
            if(j > 0) table[i2][j] = min(table[i2][j], table[i2][j-1] + 1);
            if(i > 0) table[i2][j] = min(table[i2][j], table[i2^1][j] + 1);
        }
        
        cout << table[n%2][m] << '\n';
    }
}
