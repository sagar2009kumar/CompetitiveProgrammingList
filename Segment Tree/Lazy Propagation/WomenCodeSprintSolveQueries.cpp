// https://www.hackerrank.com/contests/womens-codesprint-4/challenges/solve-the-queries
// https://www.hackerrank.com/contests/womens-codesprint-4/challenges/solve-the-queries/submissions/code/1304752488

#include<bits/stdc++.h>
typedef long long int ll;
const int MAXN = 5e4+7;
const int maxn = 101;
using namespace std;
typedef map<int, int> mp;
typedef pair<int, int> pii;
int spf[maxn];
int mod;
vector<int> primes;
int prime[maxn][25];
int segTree[4*MAXN][25];
int lazy[4*MAXN];
bool lz[4*MAXN];
int n, i, j, k, l, x;
int a[MAXN];
int q;
int indexx[maxn];

// power function to calculate the power of the a^b%mod
ll power(ll a, ll b) {
    ll res = 1;
    while(b > 0) {
        if(b&1)
            res = (res*a)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return res;
}

// to get the factor of the number x which is to be stored in the
// prime 2d array which is of size [100][25]
void getFact(int x, int i) {
    while(x!=1) {
        prime[i][indexx[spf[x]]]++;
        x/=spf[x];
    }
}

// sieve function to calculate the prime numbers b/w 1 to 100
// it also contains the list of the primes b/w 1 to 100 in primes
void sieve() {
    for(int i = 0; i < maxn; i++) spf[i] = i;
    for(int i = 2; i < maxn; i+=2) spf[i] = 2;
    for(int i = 3; i*i < maxn; i++) {
        if(spf[i] == i) {
            for(int j = i*i; j < maxn; j+=i) {
                if(spf[j]==j) spf[j] = i;
            }
        }
    }
    int cnt = 0;
    for(int i = 2; i < maxn; i++)
        if(spf[i] == i) {primes.push_back(i); indexx[i] = cnt; cnt++;}

    for(int i = 2; i < maxn; i++) {
        getFact(i,i);
    }
}

// build function to build the segTree
void build(int ss, int se, int ind) {
    if(ss == se) {
        // if it is a leaf node then just carry out the copy
        // of the element of the leaf node
        for(int i = 0; i < 25; i++)
            segTree[ind][i] = prime[a[ss]][i];
        return;
    }
    int mid = (ss + se)>>1;
    build(ss, mid, 2*ind+1);
    build(mid+1, se, 2*ind+2);
    // combining the both of the leaves node by just adding the
    // number of occurences that are occuring in the segTree of children
    for(int i = 0; i < 25; i++)
        segTree[ind][i] = segTree[2*ind+1][i] + segTree[2*ind+2][i];
}

// to update the node of the segTree with lazy propagation
// REALLY PLAYED VERY COOL. AWESOME TRICK
void update(int ss, int se, int us, int ue, int ind) {
    if(lz[ind]) {
        // if lazy node has not been updated then just update the 
        // segTree with the number of the factor of lazyTree present
        for(int i = 0; i < 25; i++)
            segTree[ind][i] = (se-ss+1)*prime[lazy[ind]][i];
        
        if(ss!=se) {
            // Here is the cool trick just just update the children
            // with the number x not with the total factor
            // propating the children
            lazy[2*ind+1] = lazy[ind];
            lazy[2*ind+2] = lazy[ind];
            lz[2*ind+1] = 1, lz[2*ind+2] = 1;
        }
        // the node has been updated
        lz[ind] = 0;
    }
    if(ue < ss || us > se) return;

    if(us <= ss && ue >= se) {
        // if the segTree falls completely in the range
        // then just update the tree with the factors
        for(int i = 0; i < 25; i++)
            segTree[ind][i] = (se-ss+1)*prime[x][i];
        if(ss!=se) {
            // again smartly update the tree with the x
            // you can imagine how awesome is this 
            // not with the factor only with the val x.
            lazy[2*ind+1] = x;
            lazy[2*ind+2] = x;
            lz[2*ind+1] = lz[2*ind+2] = 1;
        }
        return;
    }
    int mid = (ss+se)>>1;
    update(ss, mid, us, ue, 2*ind+1);
    update(mid+1, se, us, ue, 2*ind+2);
    // merging the nodes
    for(int i = 0; i < 25; i++)
        segTree[ind][i] = segTree[2*ind+1][i] + segTree[2*ind+2][i];
}

// You know this query function is also really awesome
// really awesome and this is because it has been made for the
// particular index now for the whole array because for the
// whole array time limit will be exceeded. 
// And that is so because most of the query answer is 1
// if you will query for the particular index you don't have to be
// do for all the merging and the update step that is involved in
// the process for all that. Just think over it

ll query(int ss, int se, int qs, int qe, int ind, int i) {
    // here is the index that you are referring to which is 
    // pretty awesome

    // same stuff as the update function
    if(lz[ind]) {
        for(int i = 0; i < 25; i++)
            segTree[ind][i] = (se-ss+1)*prime[lazy[ind]][i];
        if(ss!=se) {
            lazy[2*ind+1] = lazy[ind];
            lazy[2*ind+2] = lazy[ind];
            lz[2*ind+1] = 1, lz[2*ind+2] = 1;
        }
        lz[ind] = 0;
    }

    if(qe < ss || qs > se) return 0;

    if(qs <= ss && qe >= se) {
        return segTree[ind][i];
    }

    int mid = (ss+se)>>1;
    return query(ss, mid, qs, qe, 2*ind+1, i) +
           query(mid+1, se, qs, qe, 2*ind+2, i);
}

void build() {
    build(0, n-1, 0);
}

void update(int us, int ue) {
    update(0, n-1, us, ue, 0);
}

ll query(int i, int j, int ind) {
    return query(0, n-1, i, j, 0, ind);
}

ll query() {
    ll res = 1;
    i--,j--,k--,l--;
    int n1, n2;
    // query for all the index that has been supposed to 
    for(int t = 0; t < 25; t++) {
        n1 = query(i, j, t);
        n2 = query(k, l, t);
        if(n2>n1) return -1;
        res = (res* power(primes[t],n1-n2))%mod;
    }
    return res;
}

// input and all kind of stuff, no need to explain
void Input() {
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
        scanf("%d",&a[i]);
    build();
    scanf("%d",&q);
    int temp;
    ll res = 1;
    for(int t = 0; t < q; t++) {
        scanf("%d",&temp);
        if(temp == 1) {
            scanf("%d%d%d",&i, &j, &x);
            update(i-1, j-1);
        }else {
            scanf("%d%d%d%d%d",&i, &j, &k, &l, &mod);
            res = query();
            printf("%ld\n",res);
        }
    }
}

int main() {
	//freopen("input.txt", "r", stdin);
	sieve();
    Input();
	return 0;
}
