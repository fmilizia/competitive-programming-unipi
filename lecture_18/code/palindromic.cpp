#include <iostream>
#include <vector>
using namespace std;

int longest_palindromic_substring(string s){
    int n = s.size();
    
    vector<int> lps(n, 0);
    for(int l=n-1; l>=0; l--){
        vector<int> new_lps(n, 0);
        new_lps[l] = 1;
        for(int r=l+1; r<n; r++){
            new_lps[r] = max(lps[r], new_lps[r-1]);
            if(s[l] == s[r]) new_lps[r] = max(new_lps[r], lps[r-1] + 2);
        }
        lps = new_lps;
    }
    return lps[n-1];
}

int main(){
    int t;
    for(cin >> t; t > 0; t--){
        string s;
        cin >> s;
        cout << longest_palindromic_substring(s) << '\n';
    }
    return 0;
}
