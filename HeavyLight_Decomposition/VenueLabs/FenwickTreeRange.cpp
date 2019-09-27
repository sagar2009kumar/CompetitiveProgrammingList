#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+7;
int bit[MAXN];
int n;

void add(int idx, int val) {
    for (++idx; idx < n; idx += idx & -idx)
        bit[idx] += val;
}

void range_add(int l, int r, int val) {
    add(l, val);
    add(r + 1, -val);
}

int point_query(int idx) {
    int ret = 0;
    for (++idx; idx > 0; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}

int index_query(int idx) {
    return point_query(idx)-point_query(idx-1);
}

int main() {

    vector<int> a = {1, 2, 3, 4, 5, 6, 6, 7, 9};

    n = 10;

    for(int i = 0; i < 9; i++) {
        range_add(i, i, a[i]);
    }
//    for(int i = 0; i < 9; i++) {
//        add(i, a[i]);
//    }
//
//    for(int i = 0; i < 9; i ++) {
//        cout << index_query(i) << " ";
//    }

    cout << endl;

    range_add(1, 4, 2);
    range_add(3, 9, -3);


    for(int i = 0; i < 9; i ++) {
        cout << point_query(i) << " ";
    }

    cout << endl;

    for(int i = 0; i < 9; i ++) {
        cout << index_query(i) << " ";
    }

    return 0;
}
