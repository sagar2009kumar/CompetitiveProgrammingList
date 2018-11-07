
// http://www.spoj.com/problems/GSS1/

/* Really this one is difficult problem for me to think of
   and implement of the idea because this one was really a 
   nice problem.*/
   
// This problem was based on the fact that the array sum could 
// be partitioned into the node which consists of the four basic
// element that is the best sum, best prefix sum, best suffix sum
// and simply sum.
// You can see the merge portion of the Node which tells about the
// mergining of the array

//  IMPORTANT :: You must take care of the query part which tells about
// the merging of the only left and the right child while querying not 
// on the both sides which will cause a trouble for the solution of the
// problem ( that i was stuck for the most of the part) 

// This problem was painful as i have done in a really bad state of mind
// Hope you will understand (if you are 20+age).. 
// Here goes the code

#include<bits/stdc++.h>
typedef long long int ll;
const int MAX = 50007;
using namespace std;

int n, q, qs, qe;
ll a[MAX];
int u, v;

struct Node {
    ll sum, pre, suff, best;

    void fillzero(int a) {
        sum = pre = suff = best = a;
    }

    // This part is also very necessary and awesome which is 
    // the whole problem see it carefully and you will understand
    // Please do it more than one time.
    
    void mergeOp(const Node a, const Node b) {
        sum = a.sum+b.sum;
        pre = max(a.pre, a.sum+b.pre);
        suff = max(b.suff, b.sum+a.suff);
        best = max(a.suff+b.pre, max(a.best, b.best));
    }
};

Node segTree[4*MAX];

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
    build(0, n-1, 0);
}

Node query(int ss, int se, int ind) {

    if(qs <= ss && qe >= se) return segTree[ind];

    int mid = (ss+se)>>1;
  
    // THIS IS THE IMPORTANT PART THAT I WAS TALKING ABOUT
    // Do not go on both sides unnecessarily go only in one 
    // direction
    
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
        scanf("%d%d",&u, &v);
        printf("%ld\n", query(u-1, v-1));
    }
}

int main() {
    Input();
    return 0;
}
