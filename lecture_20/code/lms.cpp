#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string lms(string s){
    int n = s.size();
    
    string ans;
    
    char last = 'a';
    for(int i=n-1; i>=0; i--){
        if(s[i] >= last){
            ans.push_back(s[i]);
            last = s[i];
        }
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(){
    string s;
    cin >> s;
    cout << lms(s) << '\n';
    return 0;
}
