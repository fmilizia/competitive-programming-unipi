#include <iostream>
#include <vector>
using namespace std;

int fell(vector<pair<int,int>> tree){
    int n = tree.size();
    
    int ans = 1;
    int last_occupied = tree[0].first;
    for(int i=1; i<n; i++){
        auto &p = tree[i];
        if(p.first - p.second > last_occupied){
            ans++;
            last_occupied = p.first;
        }else if(i == n-1 or p.first + p.second < tree[i+1].first){
            ans++;
            last_occupied = p.first + p.second;
        }else{
            last_occupied = p.first;
        }
    }
    return ans;
}

int main(){
    int n;
    cin >> n;
    vector<pair<int,int>> tree(n);
    for(int i=0; i<n; i++) cin >> tree[i].first >> tree[i].second;
    cout << fell(tree) << '\n';
    return 0;
}
