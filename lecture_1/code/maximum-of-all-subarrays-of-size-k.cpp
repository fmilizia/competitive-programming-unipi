#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main(){
    int T;
    cin >> T;
    for(int t=0; t<T; t++){
        int n, k;
        cin >> n >> k;
        
        vector<int> a(n);
        for(int i=0; i<n; i++) cin >> a[i];
        
        deque<int> q;
        for(int i=0; i<n; i++){
            while(not q.empty() and a[q.back()] <= a[i]) q.pop_back();
            q.push_back(i);
            while(q.front() <= i-k) q.pop_front();
            
            if(i >= k-1) cout << a[q.front()] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
