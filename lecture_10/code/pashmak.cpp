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
    
    vector<pair<int,int>> a(n);
    for(int i=0; i<n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }
    
    sort(a.begin(), a.end());
    
    vector<int> equal_left(n);
    vector<int> equal_right(n);
    
    int last_value = 0; // Different from every value in the array
    int cnt = 0;
    for(int i=0; i<n; i++){
        cnt++;
        if(a[i].first != last_value){
            last_value = a[i].first;
            cnt = 1;
        }
        equal_left[a[i].second] = cnt;
    }
    
    last_value = 0;
    cnt = 0;
    for(int i=n-1; i>=0; i--){
        cnt++;
        if(a[i].first != last_value){
            last_value = a[i].first;
            cnt = 1;
        }
        equal_right[a[i].second] = cnt;
    }
    
    long long answer = 0;
    Fenwick fen(n);
    for(int i=0; i<n; i++){
        answer += i - fen.sum(equal_right[i]);
        fen.add(1, equal_left[i]);
    }
    
    cout << answer << '\n';
    return 0;
}
