#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int L = 2*1e5;
vector<bool> is_prime(L, true);


void solve(){
    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    
    for(int i=1; i<=n; i++){
        int x; cin >> x;
        children[x].push_back(i);
    }
    
    vector<int> depth(n + 1, 0);
    
    int cnt = 0;
    
    queue<int> q;
    q.push(0);
    depth[0] = -1;
    while(not q.empty()){
        int x = q.front(); q.pop();
        for(int y:children[x]){
            depth[y] = depth[x] + 1;
            q.push(y);
        }
        if(depth[x] > 0 and is_prime[x + depth[x]]) cnt++;
    }
    
    cout << cnt << '\n';
}

int main(){
    is_prime[0] = is_prime[1] = false;
    for(int i=2; i<L; i++) if(is_prime[i]){
        for(int j=2*i; j<L; j+=i) is_prime[j] = false;
    }
    
	int t;
	cin >> t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
