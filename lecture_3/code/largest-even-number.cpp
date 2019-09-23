#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    const vector<int> best_digits = {0,2,4,6,8,1,3,5,7,9};
    
    int t;
    for(cin >> t; t > 0; t--){
        string s;
        cin >> s;
        vector<int> cnt(10, 0);
        for(char x:s) cnt[x-'0']++;
        int last_digit = 0;
        for(int d:best_digits) if(cnt[d] > 0){
            cnt[d]--;
            last_digit = d;
            break;
        }
        for(int d=9; d>=0; d--) while(cnt[d]){cout << d; cnt[d]--;}
        cout << last_digit << '\n';
    }
    return 0;
}
