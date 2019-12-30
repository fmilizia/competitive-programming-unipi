#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> schedule(vector<pair<int,int>> meeting){
    int n = meeting.size();
    vector<int> ans;
    
    vector<int> ord(n);
    for(int i=0; i<n; i++) ord[i] = i;
    sort(ord.begin(), ord.end(), [&meeting](int i, int j){
        auto &x = meeting[i];
        auto &y = meeting[j];
        if(x.second < y.second) return true;
        if(x.second > y.second) return false;
        return x.first < y.first;
    });
    
    int last_f = 0;
    for(int i:ord){
        auto &x = meeting[i];
        if(x.first > last_f){
            ans.push_back(i);
            last_f = x.second;
        }
    }
    
    return ans;
}

int main(){
    int t;
    for(cin >> t; t > 0; t--){
        int n;
        cin >> n;
        vector<pair<int,int>> meeting(n);
        for(int i=0; i<n; i++) cin >> meeting[i].first;
        for(int i=0; i<n; i++) cin >> meeting[i].second;
        vector<int> ans = schedule(meeting);
        for(int x:ans){
            cout << x + 1 << ' '; //Offset by 1
        }
        cout << '\n';
    }
    return 0;
}
