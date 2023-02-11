#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int>vi;
#define loop(i, b) for (ll i = 0; i < b; i++)

// Detect cycle in an undirected graph.
class RecursiveDFS {
  public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V, false);
        for(int i=0; i<V; i++){
            if(!vis[i]) 
                if(dfs(i,-1,vis, adj))
                    return true;
        }
        return false;
    }
    
    bool dfs(int src, int parent, vector<bool>& vis, vector<int> adj[]){
        vis[src] = true;
        for(int dest : adj[src]){
            if(!vis[dest]) // if not visited to adjacent 'destination' node
                if(dfs(dest, src, vis, adj))
                    return true;
            if(dest != parent) // if adjacent node is visited and is it not parent then graph contains cycle
                return true;
        }
        return false;
    }
};

class IterativeBFS {
  public:
    bool isCycleUtil(int u, vector<int> adj[], vector<int> &vis){
        queue<pair<int, int>> q;
        q.push({u,-1});
        vis[u]=true;

        while(!q.empty()){
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            for(auto to : adj[node]){
                if(parent == to) continue;   
                if(vis[to]) return true; 

                vis[to] = true;
                q.push({to, node});
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<int> vis(V,0);

        for(int i=0; i<V; i++){
            if(!vis[i]) {
                if(isCycleUtil(i, adj, vis))
                    return true;
            }
        }
        return false;
    }
};


// Undirected graph cycle detection and retrivel using DFS

int n = 10e5+5, m;
vector<vi>adj(n);
vector<bool>vis(n, false);
vi parent(n);
vi cycle;
bool cycleFound;

// parent of 'u' is 'p'
void dfs(int u, int p){
    if(cycleFound) return; // once cycle is detected stop further dfs calls
    parent[u] = p;
    vis[u] = true;

    for(int v:adj[u]){
        if(cycleFound) return;
        if(!vis[v]) 
            dfs(v, u);
        else if(v!=p) // v is already been visited
        {
            cycleFound = true;
            // loop until u is not found
            while (u!=v)
            {
                cycle.push_back(u);
                u = parent[u];
            }
            cycle.push_back(u); // u==v
            return;
        }
    }
}

void solve(){
    bool flag = false;
    
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            cycleFound = false;
            dfs(i, -1);
            if(cycleFound) break;
        }
    }
    if(cycleFound){
        cout << cycle.size()+1 << endl;
        for(int x : cycle){
            cout << x << " ";
        }
        cout << cycle[0];
    }else{
        cout << "IMPOSSIBLE";
    }
}


int main()
{
    // n nodes, m edges
    cin >> n >> m;
    loop(i, m){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve();
    return 0;
}