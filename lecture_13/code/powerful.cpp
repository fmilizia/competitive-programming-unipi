#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Query{
    int id;
    int l, r;
    Query(int id, int l, int r): id(id), l(l), r(r) {}
};

int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    const int MAX_A = 1e6; // Upper bound on the elements of the array
    
    int n, t;
    cin >> n >> t;
    
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    
    vector<Query> queries;
    for(int i=0; i<t; i++){
        int l, r;
        cin >> l >> r;
        queries.emplace_back(i, l-1, r-1);
    }
    
    int block_size = max(1, (int)(n/sqrt((double)t/2)));
    sort(queries.begin(), queries.end(), [block_size](const Query &p, const Query & q){
        if(p.l / block_size < q.l / block_size) return true;
        if(p.l / block_size > q.l / block_size) return false;
        return p.r < q.r;
    });
    
    
    vector<long long> ans(t, 0);
    vector<int> k(MAX_A + 1, 0);
    
    long long current_ans = 0;
    int current_l = 0;
    int current_r = -1; // The current interval is [current_i, current_j].
    
    auto add = [&current_ans, &k](int color){
        current_ans -= (long long)k[color]*k[color]*color;
        k[color]++;
        current_ans += (long long)k[color]*k[color]*color;
    };
    auto remove = [&current_ans, &k](int color){
        current_ans -= (long long)k[color]*k[color]*color;
        k[color]--;
        current_ans += (long long)k[color]*k[color]*color;
    };
    
    for(int i=0; i<t; i++){
        Query &q = queries[i];
        while(current_l < q.l) remove(a[current_l++]);
        while(current_l > q.l) add(a[--current_l]);
        while(current_r < q.r) add(a[++current_r]);
        while(current_r > q.r) remove(a[current_r--]);
        ans[q.id] = current_ans;
    }
    
    for(int i=0; i<t; i++) cout << ans[i] << '\n';
}
