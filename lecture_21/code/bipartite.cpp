// C++ program to find out whether a given graph is Bipartite or not.
// It works for disconnected graph also.
#include <bits/stdc++.h>
using namespace std;
const int MAX = 100;
bool isBipartite(int G[][MAX],int V);
int main()
{
    int t;
	cin>>t;
	int g[MAX][MAX];
	while(t--)
	{
		memset(g,0,sizeof (g));
		int n;
		cin>>n;
	
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cin>>g[i][j];
			}
		}
		
		cout<<isBipartite(g,n)<<endl;
	}
	return 0;
}


bool color_graph(int v, int adj[][MAX], vector<int> &color, int x, int x_color){
    if(color[x] > 0 and color[x] != x_color) return false;
    if(color[x] > 0) return true;
    color[x] = x_color;
    for(int i=0; i<v; i++) if(adj[x][i]) if(not color_graph(v, adj, color, i, 3 - x_color)) return false;
    return true;
}

bool isBipartite(int adj[][MAX], int v){
    vector<int> color(v, 0);
    for(int i=0; i<v; i++) if(color[i] == 0)
        if(not color_graph(v, adj, color, i, 1)) return false;
    return true;
}
