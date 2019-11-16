#include <iostream>
#include <vector>
using namespace std;

int main(){
	int t;
	for(cin >> t; t > 0; t--){
	    int n;
	    cin >> n;
	    
	    vector<int> a(n);
	    for(int i=0; i<n; i++) cin >> a[i];
	    
	    vector<int> useful_pos;
	    useful_pos.push_back(0);
	    for(int i=1; i<n; i++)
	        if(a[i] + i > a[useful_pos.back()] + useful_pos.back())
	            useful_pos.push_back(i);
	   
       for(int x:useful_pos) cout << x << ' ' << x + a[x] << endl;
       cout << endl;
       
	   int ans = 0;
	   int pos = 0;
	   int i = 0;
	   while(ans < n and pos + a[pos] < n - 1){
	        while(i < (int)useful_pos.size()-1 and useful_pos[i+1] <= pos + a[pos]) i++;
	        pos = useful_pos[i];
	        ans++;
	   }
	   ans++;
	   
	   if(ans < n) cout << ans << '\n';
	   else cout << "-1\n";
	}
	return 0;
}
