#include <iostream>
#include <vector>
using namespace std;

bool magic(string s){
    int n = s.size();
    
    int last_one = -3;
    for(int i=0; i<n; i++){
        if(s[i] == '4'){
            if(last_one < i - 2) return false;
        }else if(s[i] == '1'){
            last_one = i;
        }else return false;
    }
    
    return true;
}

int main(){
    string s;
    cin >> s;
    cout << (magic(s)? "YES" : "NO") << '\n';
    return 0;
}
