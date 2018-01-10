// http://www.spoj.com/problems/GSS3/

#include<bits/stdc++.h>
typedef long long int ll;
const int MAX = 50007;
using namespace std;

int n, q, qs, qe;
ll a[MAX];
int u, v;
int x, temp;

struct Node {
    ll sum, pre, suff, best;

    void fillzero(int a) {
        sum = pre = suff = best = a;
    }

    void mergeOp(const Node a, const Node b) {
        sum = a.sum+b.sum;
        pre = max(a.pre, a.sum+b.pre);
        suff = max(b.suff, b.sum+a.suff);
        best = max(a.suff+b.pre, max(a.best, b.best));
    }
};

Node segTree[4*MAX];
Node dummy;

void build(int ss, int se, int ind) {
    if(ss == se) {
        segTree[ind].fillzero(a[ss]); return;
    }
    int mid = (ss+se)>>1;
    build(ss, mid, 2*ind+1);
    build(mid+1, se, 2*ind+2);
    segTree[ind].mergeOp(segTree[2*ind+1],segTree[2*ind+2]);
}

void build() {
    dummy.fillzero((ll)-INFINITY);
    dummy.sum = 0;
    build(0, n-1, 0);
}

void update(int upd, int ss, int se, int ind){
    if(ss == se) {
        segTree[ind].fillzero(x); return;
    }
    int mid = (ss+se)>>1;
    if(mid >= upd)
        update(upd, ss, mid, 2*ind+1);
    else
        update(upd, mid+1, se, 2*ind+2);
    segTree[ind].mergeOp(segTree[2*ind+1], segTree[2*ind+2]);
}

void update(int upd, int val) {
    x = val;
    update(upd, 0, n-1, 0);
}

Node query(int ss, int se, int ind) {

    if(qs <= ss && qe >= se) return segTree[ind];

    int mid = (ss+se)>>1;

    if(mid >= qe)
        return query(ss, mid, 2*ind+1);
    else if(mid < qs)
        return query(mid+1, se, 2*ind+2);
    else {
        Node left = query(ss, mid, 2*ind+1);
        Node right = query(mid+1, se, 2*ind+2);
        Node temp;
        temp.mergeOp(left, right);
        return temp;
    }
}

ll query(int a, int b) {
    qs = a, qe = b;
    return query(0, n-1, 0).best;
}

void Input() {
    scanf("%d",&n);
    for(int i = 0; i < n; i++) scanf("%d",&a[i]);
    build();
    scanf("%d",&q);
    for(int i = 0; i < q; i++) {
        scanf("%d%d%d",&temp, &u, &v);
        if(temp==0)
            update(u-1, v);
        else
            printf("%ld\n", query(u-1, v-1));
    }
}

int main() {
    Input();
    return 0;
}
