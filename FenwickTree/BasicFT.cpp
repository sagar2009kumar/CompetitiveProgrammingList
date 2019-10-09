#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
const int MAXN = 1e5 + 7;

class FT {

    int size_ft;
    vector<ll> bit;
    int n;

    public :

        FT(int n, const vector<ll> &arr, bool isRangeFT = false) {

            this->size_ft = n + 1;
            this->n = n;

            if (isRangeFT) {
                /**** the vector is initialized with zero ****/
                this->bit.resize(n + 1, 0);

                /**** will do range update ****/
            }
            else {
                /**** the vector is initialized to the given vector ****/
                this->bit.resize(n+1, 0);

                for(int i = 0; i < n; i++) {
                    this->update(i, arr[i]);
                }
            }
        }

        /**** Function for the addition to the range ****/
        void update(int idx, ll val) {

            for (++idx; idx < this->size_ft; idx += idx & -idx)
                bit[idx] += val;
        }

        /**** Function for the cummulative sum at a given index ****/
        ll cummulative_sum(int idx) {

            ll ret = 0;
            for (++idx; idx > 0; idx -= idx & -idx)
                ret += bit[idx];
            return ret;
        }

        /**** Function for the range addition from l to r with the given value as val ****/
        void range_update(int l, int r, ll val) {

            /**** adding to the range of from l to n ****/
            this->update(l, val);
            /**** subtracting from the range from r+1 to n ****/
            this->update(r + 1, -val);
        }

        /**** Function for getting the point query at the given index ****/
        ll point_query(int ind) {
            return cummulative_sum(ind) -cummulative_sum(ind-1);
        }

        ll range_query(int l, int r) {
            return cummulative_sum(r) - cummulative_sum(l-1);
        }

        /**** Function for updating at a particular index ****/
        void updateAtIndex(int ind, ll val) {
            val -= point_query(ind);
            update(ind, val);
        }

        /**** Function to print the fenwick tree ****/
        void print() {

            printf("--------- Printing Fenwick Tree ----------\n");
            for(int i = 0; i < this->n; i++) {
                printf("%ld ", point_query(i));
            }
            printf("\n--------- End Printing Fenwick Tree ----------\n\n");
        }

        /**** Function for the demo of the fenwick tree basic ****/
        void demo() {

            /**** printing for the point update and range query ****/
            printf ("-----WELCOME TO POINT UPDATE AND RANGE QUERY----\n\n");
            /**** printing the initial fenwick tree ****/
            this->print();

            /**** updating few queries for the fenwick tree ****/

            printf("-----UPDATING THE VALUE AT INDEX 1 and 2 with 30 and 12 resp. ");
            this->updateAtIndex(2, 12);
            this->updateAtIndex(1, 30);

            printf("\n\n-----FENWICK TREE AFTER UPDATE-------\n\n");

            this->print();

            printf("------PRINTING THE POINT QUERY------\n\n");

            printf("Value at the index 1 is %ld \n", this->point_query(1));
            printf("Value at the index 2 is %ld \n", this->point_query(2));
            printf("Value at the index 0 is %ld \n", this->point_query(0));
            printf("Value at the index n-1 is %ld \n", this->point_query(this->n-1));

            printf("-----END OF PRINTING THE POINT QUERY ------\n\n");

            printf("-----PRINTING THE RANGE QUERY-------\n\n");

            printf("0, n-1, %ld\n", this->range_query(0, this->n-1));
            printf("0, 1 %ld\n", this->range_query(0, 1));
            printf("3, 5 %ld\n", this->range_query(3, 5));

            printf("\n-----EXITING THE DEMO, BYE ---------\n\n");
        }
};

void demoFT() {

    vector<ll> a = {1, 2, 3, 4, 5, 6, 6, 7, 9};
    FT ft(a.size(), a, false);
    ft.demo();

}

int main() {

    demoFT();
    return 0;
}
