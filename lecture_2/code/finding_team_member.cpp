#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
    int n;
    cin >> n;
    
    vector<int> teammember(2*n+1, 0);
    vector<pair<int,pair<int,int>>> pairs(n*(2*n-1));
    
    int idx = 0;
    for(int i=1; i<=2*n; i++) for(int j=1; j<i; j++){
        cin >> pairs[idx].first;
        pairs[idx].second = {i, j};
        idx++;
    }
    sort(pairs.begin(), pairs.end());
    
    while(idx > 0){
        idx--;
        if(teammember[pairs[idx].second.first] == 0 and teammember[pairs[idx].second.second] == 0){
            teammember[pairs[idx].second.first] = pairs[idx].second.second;
            teammember[pairs[idx].second.second] = pairs[idx].second.first;
        }
    }
    
    for(int i=1; i<=2*n; i++) cout << teammember[i] << ' ';
    cout << '\n';
    return 0;
}
