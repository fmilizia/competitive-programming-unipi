#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
    int n;
    cin >> n;
    
    vector<vector<int>> positions(100);
    
    for(int i = 0; i < 2*n; i++){
        int x; cin >> x;
        positions[x].push_back(i);
    }
    
    vector<int> chosen_heap(2*n); // The sequence of chosen heaps (0 or 1. Will add +1 while printing).
    vector<int> distinct(2, 0);
    int last_unique = 0;
    int last_copy = 1;
    
    for(int x = 10; x <= 99; x++){
        if(positions[x].size() == 1){
            last_unique = 1 - last_unique;
            distinct[last_unique]++;
            chosen_heap[positions[x][0]] = last_unique;
        }else if(positions[x].size() >= 2){
            distinct[0]++;
            distinct[1]++;
            for(int p:positions[x]){
                last_copy = 1 - last_copy;
                chosen_heap[p] = last_copy;
            }
        }
    }
    
    cout << distinct[0] * distinct[1] << '\n';
    for(int x:chosen_heap) cout << x + 1 << ' ';
    cout << '\n';
    
    return 0;
}
