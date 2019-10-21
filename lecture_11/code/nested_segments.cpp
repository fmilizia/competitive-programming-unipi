#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Stree{
    int left_extreme, right_extreme;
    vector<int> vec;
    Stree(int left_extreme, int right_extreme): 
        left_extreme(left_extreme), 
        right_extreme(right_extreme), 
        vec(4*(right_extreme - left_extreme + 1),0) {}
    
    void add(int v, int l, int r, int val, int pos){
        if(pos < l or pos > r) return;
        if(l == r){
            vec[v] += val;
        }else{
            add(2*v, l, (l+r)/2, val, pos);
            add(2*v+1, (l+r)/2+1, r, val, pos);
            vec[v] = vec[2*v] + vec[2*v+1];
        }
    }
    int sum_query(int v, int l, int r, int from, int to){
        if(to < l or from > r) return 0;
        if(from <= l and r <= to) return vec[v];
        return sum_query(2*v, l, (l+r)/2, from, to) + sum_query(2*v+1, (l+r)/2+1, r, from, to);
    }
    
    void add(int val, int pos){
        add(1, left_extreme, right_extreme, val, pos);
    }
    int sum_query(int from, int to){
        int ans = sum_query(1, left_extreme, right_extreme, from, to);
        return ans;
    }
};

int main(){
    int n;
    cin >> n;
    
    vector<pair<int,int>> intervals(n);
    vector<pair<int,int>> ord_left(n), ord_right(n);
    vector<int> ans(n, 0);
    Stree st(1, n);
    
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
        ans[idx] = st.sum_query(intervals[idx].first, n);
        st.add(1, intervals[idx].first);
    }
    
    for(int idx=0; idx<n; idx++) cout << ans[idx] << '\n';
    return 0;
}
