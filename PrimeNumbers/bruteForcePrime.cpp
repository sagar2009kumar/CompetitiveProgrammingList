#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll n;

ll bruteForce() {

    // return the maximum factor of a prime number
    int currMax = 0;
    for(int i = 2; i < sqrt(n) ; i++) {
        while(n%i==0) {
            // removing all the factor i
            n/=i;
        }
        if(n==1) break;
        currMax = i;
    }
    // if the last number is the prime number
    currMax = currMax < n ? n : currMax;
    return currMax;
}

int main() {
    int t; 
    scanf("%d",&t);
    while(t-->0) {
        scanf("%d", &n);
        ll temp = bruteForce();
        printf("%d", &temp);
    }
return 0;
}
