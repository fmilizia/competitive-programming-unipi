#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Location{
    int x, y;
    int pop;
    Location(int x, int y, int pop): x(x), y(y), pop(pop) {}
    
    int square_distance() const{
        return x*x + y*y;
    }
    bool operator < (const Location &other){
        return square_distance() < other.square_distance();
    }
};

int main(){
    const int MEGA = 1000000;
    cout.precision(10);
    
    int n, s;
    cin >> n >> s;
    
    vector<Location> v;
    v.reserve(n);
    
    for(int i=0; i<n; i++){
        int x, y, pop;
        cin >> x >> y >> pop;
        v.emplace_back(x, y, pop);
    }
    
    sort(v.begin(), v.end());
    
    if(s >= MEGA){
        cout << "0\n";
        return 0;
    }
    
    for(int i=0; i<n; i++){
        s += v[i].pop;
        if(s >= MEGA){
            cout << fixed << sqrt(v[i].square_distance()) << '\n';
            return 0;
        }
    }
    
    cout << "-1\n";
    return 0;
}
