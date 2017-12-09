/*****************************************************************************************************
*                             sieve algorithm for the printing the prime factor of number             *
*******************************************************************************************************/

// The algorithm runs in precomputation in 0(nloglogn) 
// query time is log(n)

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 1e6+2;
ll n;
int spf[MAX];

void sieve() {
    // setting all the numbers initially to the number itself
    for(int i = 0; i < MAX; i++) {
        spf[i] = i;
    }
    // setting the even numbers smallest factor as the 2
    for(int i = 4; i < MAX; i+=2) {
        spf[i] = 2;
    }
    // calculating the precomputation
    for(int i = 3; i*i < MAX; i+=2) {
        if(spf[i] == i) {
            // if the given number is the prime number 
            for(int j = i*i; j < MAX; j+=i) {
                // setting all the higher factor of this to the given factor 
                if(spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

vector<ll> getFactor(ll n) {
   vector<ll> temp;
   while(n!=1) {
      temp.push_back(spf[n]);
      n/=spf[n];
   }
   sort(temp.begin(), temp.end());
   return temp;
}

int main() {
    sieve();
    int n; 
    scanf("%d", &n);
    vector<ll> vi = getFactor(n);
    for(int i = 0; i < vi.size(); i++) {
        printf("%d", vi[i]);
    }
    return 0;
}
