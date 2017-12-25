// I am very happy, this is the first problem after break up 
// This is the first dynamic programming i have solved myself
// I am feeling pretty awesome today after such a long time

// http://codeforces.com/problemset/problem/166/E

#include<bits/stdc++.h>
typedef long long int ll;
const int MAX = 1e7+7;
const int mod = 1e9+7;
using namespace std;

ll a[MAX], b[MAX], c[MAX], d[MAX];

int main() {
    int n;
    scanf("%d",&n);
    d[0] = 1;
    for(int i = 0; i < n-1; i++) {
        d[i+1] = (b[i] + c[i] + a[i])%mod;
        c[i+1] = (b[i] + a[i] + d[i])%mod;
        a[i+1] = (b[i] + c[i] + d[i])%mod;
        b[i+1] = (d[i] + a[i] + c[i])%mod;
    }
    printf("%d",(b[n-1]+a[n-1]+c[n-1])%mod);
	return 0;
}

/* This problem is really cool i mean you can literally see how 
   amazing is that it could be solved by the very less memory like below 
    int zD = 1;
    int zABC = 0;
    for (int i = 1; i <= n; i++) {
      int nzD = zABC * 3LL % MOD;
      int nzABC = (zABC * 2LL + zD) % MOD;
      zD = nzD;
      zABC = nzABC;
    }
    cout << zD;
    
    Means you can literally see the transformation very well and easy
    
    or it could be solved in log(n) time also by making the matrix
    really you could see the amazingness of the problem really appreciable
    but i had not think of it
    
    Due to the symmetry $A_i=B_i=C_i=ABC_i$, so

    ABCi = Di - 1 + ABCi - 1 + ABCi - 1 = Di - 1 + 2 * ABCi - 1
    Di = ABCi - 1 + ABCi - 1 + ABCi - 1 = 3 * ABCi - 1
    
*/
  
