#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fenwick{
    int n;
    vector<int> v;
    Fenwick(int n): n(n), v(n+1,0) {}
    
    void add(int val, int pos){
        for(int i = pos; i <= n; i += i & -i){
            v[i] += val;
        }
    }
    
    int sum(int pos){
        int ans = 0;
        for(int i = pos; i > 0; i -= i & -i){
            ans += v[i];
        }
        return ans;
    }
};

int main(){
    int n;
    cin >> n;
    
    vector<pair<int,int>> intervals(n);
    vector<pair<int,int>> ord_left(n), ord_right(n);
    vector<int> ans(n, 0);
    Fenwick fen(n);
    
    for(int i=0; i<n; i++){
        cin >> intervals[i].first >> intervals[i].second;
    }
    
    for(int i=0; i<n; i++) ord_left[i] = {intervals[i].first, i};
    for(int i=0; i<n; i++) ord_right[i] = {intervals[i].second, i};
    sort(ord_left.begin(), ord_left.end());
    sort(ord_right.begin(), ord_right.end());
    
    // Now compress the coordinates of the starting points of the intervals
    // They are big at the beginning; after this they will be between 1 and n.
    for(int i=0; i<n; i++) intervals[ord_left[i].second].first = i + 1;
    
    for(int i=0; i<n; i++){
        int idx =  ord_right[i].second;
        ans[idx] = i - fen.sum(intervals[idx].first);
        fen.add(1, intervals[idx].first);
    }
    
    for(int idx=0; idx<n; idx++) cout << ans[idx] << '\n';
    return 0;
}
