/****************************************************************************
*                         PROGRAM FOR LCA                                   *
*****************************************************************************/

// http://www.spoj.com/problems/LCA/

// IMPORTANT POINT ::
// 1. The edges must be undirected.
// 2. 0 is taken as the root.
// 3. It is solved with the help of sparse table.
// 4. Time Complexity :: PreProcessing Time (nlgn) and Query Time (lgn)

#include<bits/stdc++.h>
#define root 0
typedef long long int ll;
const int MAXN = 1111;
const int MAXLN = 11;
using namespace std;
int depth[MAXN];
int par[MAXLN][MAXN];
vector<int> adj[MAXN];
int n, q, u, v, sz;

// dfs function to set up the parent and the depth of the node
void dfs(int cur, int prev, int _depth = 0) {
    depth[cur] = _depth;
    par[0][cur] = prev;
    for(int i = 0; i < adj[cur].size(); i++) {
        if(adj[cur][i]!= prev) {
            dfs(adj[cur][i], cur, _depth+1);
        }
    }
}

// dynamic programming for finding the LCA
void LCAPreprocess() {
    for(int i = 1; i < MAXLN; i++) {
        for(int j = 0; j < n; j++) {
            // if the parent of the below level exist
            // then parent of level i is equal to the
            // parent of the parent of the level-1
            // Please get the feel of the dp here 
            // otherwise you will not get the picture
            if(par[i-1][j]!=-1)
                par[i][j] = par[i-1][par[i-1][j]];
        }
    }
}

// function to give the LCA of two edges
int LCA(int u, int v) {

    // we want the u to be at the lower level
    if(depth[u] < depth[v])
        swap(u, v);

    // we want to make the two nodes to be at the same level
    int diff = depth[u]-depth[v];

    for(int i = 0; i < MAXLN; i++)
        if((diff>>i)&1) u = par[i][u];

    // if the node which are the same level are same then it is lca
    if(u == v) return u;

    // if the parent of both the nodes are not same then jump to that level
    for(int i = MAXLN-1; i>=0; i--)
        if(par[i][u]!= par[i][v])
            u = par[i][u], v = par[i][v];

    // return the immediate parent to the given node
    return par[0][u];
}

// Function to take the inputs
void Input() {
    for(int i = 0; i < n; i++) {
        scanf("%d",&sz);
        for(int j = 0; j < sz; j++) {
            scanf("%d",&u);
            // remember to add the undirected edges
            adj[i].push_back(u-1);
            adj[u-1].push_back(i);
        }
    }
}

void clearI() {
    for(int i = 0; i < n; i++) {
        adj[i].clear();
        for(int j = 0; j < MAXLN; j++) par[j][i] = -1;
    }
}

void solve(int t) {
    scanf("%d",&n);
    clearI();
    Input();
    scanf("%d",&q);
    dfs(0, -1);
    LCAPreprocess();
    printf("Case %d:\n", t);
    for(int i = 0; i < q; i++) {
        scanf("%d%d",&u, &v);
        printf("%d\n",LCA(u-1, v-1)+1);
    }
}

void go() {
    int t = 1;
    scanf("%d",&t);
    int cnt = 1;
    while(cnt <= t){
        solve(cnt);
        cnt++;
    }
}

int main() {
	//freopen("input.txt", "r", stdin);
	go();
	return 0;
}
