#include <iostream>
#include <vector>
using namespace std;

int solve(vector<int> arr){
    int lower_bound = 0; // Each element must be greater than the lower_bound
    
    vector<int> v;
    for(int x:arr){
        while(not v.empty() and x > v.back()){
            lower_bound = v.back();
            v.pop_back();
        }
        
        if(x <= lower_bound) return 0;
        
        if(v.empty() or x < v.back()) v.push_back(x);
        else return 0; //Two keys are equal
    }
    return 1;
}

int main(){
    int t; cin >> t;
    for(int i=0; i<t; i++){
        int n;
        cin >> n;
        
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin >> arr[i];
        
        cout << solve(arr) << '\n';
    }
    return 0;
}
