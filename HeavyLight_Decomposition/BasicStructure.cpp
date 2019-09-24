/**************************************************************************************
*                              Heavy_Light_Decomposition                              *
**************************************************************************************/

// Please refer to the anudeep blog before going through the code that is awesome

// https://blog.anudeep2011.com/heavy-light-decomposition/


#include<bits/stdc++.h>
typedef long long int ll;
const int MAXN = 1e5+7; // check these before you apply
const int MAXLN = 17;   // check it also
using namespace std;

int chainNo[MAXN]; // chain no to which a given node belongs
int posInBase[MAXN];  // position of the node in the array generated
int chainHead[MAXN];  // node which is the head of the chain
int baseArray[MAXN];  // base array which is going to be generated
ll segTree[4*MAXN];   // segment tree of the array that has been generated
int ptr = 0, n, u, v, c;
int currChainNo;      // current chain no i.e the chain no of the branch
int subSize[MAXN];    // subsize of the array that has been generated
int sc[MAXN];         // special child of the given node or simply a node
int SC[MAXN];         // special cost or cost related to the special child
int depth[MAXN];      // depth of the given node
vector<int> adj[MAXN];// graph containing the adjacency list
vector<int> cost[MAXN];// cost of the edge of the graph
int pa[MAXLN][MAXN];    // to get the lca of the two node by dynamic programming
                     // if necessary

// helper function to print the array
void print(int* a) {
    for(int i = 0; i < n; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

// depth first search for the setting of the current node and the special child
void dfs(int cur, int prev, int _depth = 0) {
    // setting the subsize of current node which is ought to be 1 first for every child
    subSize[cur] = 1;
    // firstly we assume that the current node is the special child
    sc[cur] = -1;
    pa[0][cur] = prev;
    depth[cur] = _depth;
    for(int i = 0; i < adj[cur].size(); i++) {
        if(adj[cur][i]!= prev) {
            dfs(adj[cur][i], cur, _depth+1);
            subSize[cur]+= subSize[adj[cur][i]];
            // following two lines are for the setting of the special child and the special cost
            if(sc[cur] == -1) sc[cur] = adj[cur][i], SC[cur] = cost[cur][i];
            if(subSize[adj[cur][i]] > subSize[sc[cur]]) sc[cur] = adj[cur][i], SC[cur] = cost[cur][i];
        }
    }
}

// Heavy_Light_Decomposition Actual part

// Function contains three argument the current node then previous node and then the cost to the
// edge which is recursively called to just break up the chains
// First thing is that chain is made for the special child of all the node

// 1. For this to achieve, the chainHead is set up for each of the chains so that
//    while jumping in the chains we can change the chain easily
// 2. chainNo for the current node is set up properly i.e to which chain the given
//    node belongs
// 3. posInBase refers to the position of the baseArray so that while querying time 
//    we can query over from the given range to the given range
// 4. baseArray contains the actual cost of the edge which is used to build up the
//    segment tree
// 5. Remember that we have calculated the special child with the special cost in the dfs
//    portion before so we need to calculate it here as opposed to anudeep blog
// 6. If the current node is not a leaf node then add the current node to the current chain
//    and continue to do so until you get to the leaf node and then come back and do
// 7. Now change the current chain no by incrementing it and then finally do the Heavy_Light_
//    Decompositon with the normal child 


void HLD(int cur, int prev, int ncost) {
    if(chainHead[currChainNo]==-1)
        chainHead[currChainNo] = cur; // point no 1

    chainNo[cur] = currChainNo;       // point no 2
    posInBase[cur] = ptr;             // point no 3
    baseArray[ptr++] = ncost;         // point no 4

    if(sc[cur]!=-1)
        HLD(sc[cur], cur, SC[cur]);   // point no 5 & 6

    for(int i = 0; i < adj[cur].size(); i++) {
        // point no 7
        if(adj[cur][i]!=sc[cur] && adj[cur][i]!= prev){
            currChainNo++;
            HLD(adj[cur][i], cur, cost[cur][i]);
        }
    }
}

// preProcess function to set up the necessary details and
// do heavy_light_decomposition
void preProcess() {
    memset(pa, -1, sizeof(pa));
    memset(chainHead, -1, sizeof(chainHead));
    dfs(0,-1);
    currChainNo = 0, ptr = 0;
    HLD(0, -1, -1);
}

// function to get the input of the graph
void Input() {
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d%d",&u,&v,&c);
        adj[u].push_back(v);
        adj[v].push_back(u);
        cost[u].push_back(c);
        cost[v].push_back(c);
    }
    preProcess();
}

int main() {
    Input();
	return 0;
}

// Hope you have understood the concept atleast. :)
