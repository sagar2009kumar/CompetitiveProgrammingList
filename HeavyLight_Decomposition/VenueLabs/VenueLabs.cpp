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

int q;
map<int ,int> calculatedFact;
int nodeCost[MAXN];
int currCost[MAXN];
ll bit[MAXN];
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
int SIZE_FT;

const int SIEVE_MAX = 1e6+2;
int spf[SIEVE_MAX];

/**** Fenwick tree implementation ****/

void add(int idx, int val) {
    for (++idx; idx < SIZE_FT; idx += idx & -idx)
        bit[idx] += val;
}

void range_add(int l, int r, int val) {
    add(l, val);
    add(r + 1, -val);
}

ll point_query(int idx) {
    ll ret = 0;
    for (++idx; idx > 0; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}

void sieve() {

    calculatedFact[1] = 0;

    // setting all the numbers initially to the number itself
    for(int i = 0; i < SIEVE_MAX; i++) {
        spf[i] = i;
    }

    // setting the even numbers smallest factor as the 2
    for(int i = 4; i < SIEVE_MAX; i+=2) {
        spf[i] = 2;
    }
    // calculating the precomputation
    for(int i = 3; i*i < SIEVE_MAX; i+=2) {
        if(spf[i] == i) {
            // if the given number is the prime number
            for(int j = i*i; j < SIEVE_MAX; j+=i) {
                // setting all the higher factor of this to the given factor
                if(spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

/**** Function to get the sum of Factor divisible by 3 ****/

int getFactor(int n) {

  if(calculatedFact.find(n) != calculatedFact.end()) {
        return calculatedFact[n];
  }

   int currN = n;

   map<int, int > mp;

   while(n!=1) {
      mp[spf[n]]++;
      n/=spf[n];
   }

   ll tempVar = 1;
   /**** You can use map to make it fast ****/
   for(auto it = mp.begin(); it != mp.end(); it++) {
        ll tempAns = 0;
        for(int i = 0; i <= it->second; i++) {
            tempAns+= pow(it->first, i);
        }
        tempVar *= tempAns;
   }

   tempVar = (tempVar%3 == 0) ? 1 : 0;
   calculatedFact[currN] = tempVar;
   return tempVar;
}

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
            nodeCost[cur] += nodeCost[adj[cur][i]];
            // following two lines are for the setting of the special child and the special cost
            if(sc[cur] == -1) sc[cur] = adj[cur][i], SC[cur] = nodeCost[adj[cur][i]];
            if(subSize[adj[cur][i]] > subSize[sc[cur]]) sc[cur] = adj[cur][i], SC[cur] = nodeCost[adj[cur][i]];
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
            HLD(adj[cur][i], cur, nodeCost[adj[cur][i]]);
        }
    }
}

/**** Function to build the segment tree ****/

void build(int l, int r, int ind) {

    if(l == r) {
        segTree[ind] = baseArray[l]; return;
    }

    int mid = (l+r)>>1;

    build(l, mid,  2*ind+1);
    build(mid+1, r, 2*ind+2);

    segTree[ind] = segTree[2*ind+1] + segTree[2*ind+2];
}

/**** Function to build the segment tree ****/
void build() {
    build(1, n-1, 0);
}

/**** Function to query from the left and right ****/
ll query(int l, int r, int currL, int currR, int ind) {

    /**** If the range lies completely inside the given range ****/
    if( currL  <= l && currR >= r) return segTree[ind];

    /**** If the range lies completely outside the given range ****/
    if(currL > r || currR < l) return 0;

    int mid = (l + r) >>1;

    /**** If it lies between the given range ****/
    return query(l, mid, currL, currR, 2*ind+1) + query(mid+1, r, currL, currR, 2*ind+2);
}

ll query(int left, int right) {

    return query(1, n-1, left, right, 0);
}

/**** Function to update at the particular point ****/
void update(int l, int r, int currInd, int value, int ind = 0) {

    if(l == r) {
        segTree[ind] = value; return ;
        // segTree[ind] = getFactor(value); return ;
    }

    int mid = (l + r) >>1;

    if(mid >= currInd)
        update(l, mid, currInd, value, 2*ind+1);
    else
        update(mid+1, r, currInd, value, 2*ind+2);
    segTree[ind] = segTree[2*ind+1] + segTree[2*ind+2];
}

void update(int currInd, int value) {
    update(1, n-1, currInd, value, 0);
}

/**** Function for query up tree ****/

ll queryUp(int u, int v) {

    int uchain = chainNo[u], vchain = chainNo[v], ans = 0;

    while(1) {

        // cout << uchain << vchain << "\n";

        if(uchain == vchain) {

            /**** If chain of both the u and v is same ****/

            ans += query(posInBase[v], posInBase[u]); break;
        }

        ans += query(posInBase[chainHead[uchain]], posInBase[u] );

        u = chainHead[uchain];
        u = pa[0][u];
        uchain = chainNo[u];
        // cout << "parent" << u << "uchain : " << uchain << "\n";
    }

    return ans;
}

void updateUp(int u, int v, int value) {

    // cout << u << " " << v;
    int uchain = chainNo[u], vchain = chainNo[v];

    while(1) {

        // cout << uchain << " kk " << vchain << "\n";

        if(uchain == vchain) {

            /**** If chain of both the u and v is same ****/

            range_add(posInBase[v], posInBase[u], value); break;
        }

        range_add(posInBase[chainHead[uchain]], posInBase[u], value);

        u = chainHead[uchain];
        u = pa[0][u];
        uchain = chainNo[u];
        // cout << "parent" << u << "uchain : " << uchain << "\n";
    }
}

ll queryFT(int u) {

    return point_query(u);
}

void queryHLD(int u) {

    /*
    if(u == 1) {
        u = nodeCost[0];
    }else {
        u = queryUp(u-1, 0);
        u += nodeCost[0];
    }*/

    ll ans = 0;
    if(u != 1)
        ans = queryFT(posInBase[u-1]);
    else
        ans = queryFT(0);
    ans = max(ans, (ll)0);

    printf("%ld\n", ans);
}

void updateHLD(int u, int value) {

    value = getFactor(value);

    if(currCost[u-1] == value) return;

    currCost[u-1] = value;

    value = value == 0 ? -1 : 1;

    if(u != 1)
        updateUp(u-1, 0, value);
    else
        range_add(0, 0, value);
}

void queryProgram() {

    int temp = 0, u, value;

    for(int i = 0; i < q; i++) {

        scanf("%d", &temp);

        if(temp == 1) {
            scanf("%d%d", &u, &value);
            updateHLD(u, value);
        }else {
            scanf("%d", &u);
            queryHLD(u);
        }
    }
}

void testSieve() {

    for(int i = 0; i < n; i++) {
        cout << nodeCost[i] << " : "<< getFactor(nodeCost[i]) << "\n";
    }
}

void testGraph() {

    for(int i = 0; i < n-1; i++) {
        cout << i << " : ";
        for(int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
}

void testHLD() {

    print(chainNo); // chain no to which a given node belongs
    print(posInBase);  // position of the node in the array generated
    print(chainHead);  // node which is the head of the chain
    print(baseArray);
}

void testSegTree() {

    for(int i = 0; i < 4*n; i++) {
        cout << segTree[i] << " ";
    }
    cout << n;
}

void testQuery() {

    cout << queryUp(12, 0);
}

void testFT() {

    for(int i = 0; i < n; i++) {
        cout << point_query(i) << " ";
    }
    cout << "\n";
}

void buildFT() {

    SIZE_FT = n+1;

    range_add(0, 0, nodeCost[0]);

    for(int i = 1; i < n; i++) {
        range_add(i, i, baseArray[i]);
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
    //build();
    buildFT();
}

// function to get the input of the graph
void Input() {

    freopen("myinput.txt", "r", stdin);
    scanf("%d%d",&n,&q);
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d",&u,&v,&c);
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    sieve();

    for(int i = 0; i < n; i++) {
        scanf("%d",&nodeCost[i]);
        nodeCost[i] = currCost[i] = getFactor(nodeCost[i]);
    }

    preProcess();
    //testHLD();
    queryProgram();
}

int main() {
    Input();
	return 0;
}

// Hope you have understood the concept atleast. :)
