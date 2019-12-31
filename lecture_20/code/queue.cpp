#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Person{
    int a;
    int h;
    string name;
};

int main(){
    int n;
    cin >> n;
    
    vector<Person> people(n);
    vector<vector<int>> people_by_a(n); // people_by_a[x] is a vector of indices of people with a = x.
    vector<int> existing_a; // Which values of a actually exist, in decreasing order.
    
    for(int i=0; i<n; i++){
        cin >> people[i].name;
        cin >> people[i].a;
        if(people[i].a >= n){
            cout << "-1\n";
            return 0;
        }else{
            people_by_a[people[i].a].push_back(i);
        }
    }
    
    for(int a=n-1; a>=0; a--) if(not people_by_a[a].empty()) existing_a.push_back(a);
    
    set<int> available_h;
    for(int h=0; h<n; h++) available_h.insert(h);
    
    for(int a: existing_a){
        for(int x: people_by_a[a]){
            auto hp = available_h.lower_bound(a);
            if(hp == available_h.end()){
                cout << "-1\n";
                return 0;
            }
            people[x].h = n - *hp;
            available_h.erase(hp);
        }
    }
    
    for(auto it_a = existing_a.rbegin(); it_a != existing_a.rend(); it_a++)
        for(auto it_x = people_by_a[*it_a].rbegin(); it_x != people_by_a[*it_a].rend(); it_x++){
        cout << people[*it_x].name << ' ' << people[*it_x].h << '\n';
    }
    return 0;
}
