#include <iostream>
#include <vector>
using namespace std;


long long merge_sort(vector<int> &v){
    int n = v.size();
    if(n <= 1) return 0;
    
    vector<int> v_left(v.begin(), v.begin() + n/2);
    vector<int> v_right(v.begin() + n/2, v.end());
    
    long long ans = merge_sort(v_left) + merge_sort(v_right);
    
    int i = 0, j = 0;
    while(i < n/2 and j < n - n/2){
        if(v_left[i] > v_right[j]){
            ans += n/2 - i;
            v[i + j] = v_right[j];
            j++;
        }else{
            v[i + j] = v_left[i];
            i++;
        }
    }
    
    while(i < n/2){
        v[i + j] = v_left[i];
        i++;
    }
    while(j < n - n/2){
        v[i + j] = v_right[j];
        j++;
    }
    
    return ans;
}

int main(){
    int t;
    for(cin >> t; t > 0; t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i=0; i<n; i++) cin >> a[i];
        cout << merge_sort(a) << '\n';
    }
    return 0;
}
