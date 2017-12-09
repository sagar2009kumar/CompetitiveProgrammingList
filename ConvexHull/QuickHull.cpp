/**********************************************************************************************************
*                             Implementation of QuickHull taken from the geekforgeeks.org                 *
***********************************************************************************************************/

// The algorithm is used for the finding of the convex hull and it's average time complexity is 0(nlgn)
// but in worst case it can go to the 0(n^2) 

#include<bits/stdc++.h>
const int MAX = 1e5+2;
typedef long long int ll;
using namespace std;
typedef pair<ll, ll> Point;
set<Point> hull;
Point point[MAX];
int n;

// it is used to decide whether the two points lie on the
// same side of the plane or not
// This is simply the point form of the line i.e all the line
// if d is equal to zero then the point lies on the line
// if d has the same sign then the point lies on the same side
// of the line otherwise lies on the other side of the line
int decideface(const Point a, const Point b, const Point c) {
    ll d =  (c.second - a.second)*(b.first -a.first) -
            (b.second - a.second)*(c.first - a.first );
    if(d>0) return 1;
    if(d<0) return -1;
    return 0;
}

// it is used to calculate the distance between the two points
// simple pythagorean formula
ll distance(const Point a, const Point b) {
    return  (b.second- a.second)*(b.second-a.second) +
            (b.first-a.first)*(b.first-a.first);
}

// line distance it is used to decide how far the distance of a point
// is w.r.t to the given lines ax+by+c which is given by the formula
// |ax+by+c|/(root(a^2+b^2));
// in this section we take only the proportionality of the distance
// which is ultimately the distance formula with the absolute function
// associated with it
// There is the line equation and the point. Firstly the line has been
// converted into the line and then the point is then put into it

ll lineDist(const Point a, const Point b, const Point c) {
    return abs((c.second - a.second)*(b.first -a.first) -
            (b.second - a.second)*(c.first - a.first ));
}

// This is the main quickHULL function that does the quickhull
void quickHULL(int leftMost, int rightMost, int face) {
    int ind = -1; // This is the index where we have to divide
    ll max_dist = 0; // it should be zero because of the fact that
                     // it also check the point segment on the same
                     // line
    // Maximum point has been found in the following loop
    ll temp = 0;
    for(int i = 0; i < n; i++) {
        temp = lineDist(point[leftMost], point[rightMost], point[i]);
        if( temp > max_dist && decideface(point[leftMost], point[rightMost], point[i]) == face) {
            ind = i; max_dist = temp;
        }
    }

    // if the index has not been changed i.e no point has been detected to the sides
    // then add the both end point to the convex hull because these are the only end 
    // point containing in the hull
    if(ind==-1) {
        hull.insert(point[leftMost]);
        hull.insert(point[rightMost]);
        return;
    }

    // recurr to the both sides
    quickHULL(ind, leftMost, -decideface(point[ind], point[leftMost], point[rightMost]));
    quickHULL(ind, rightMost, -decideface(point[ind], point[rightMost], point[leftMost]));
}

void quickHull() {
    if(n < 3) {
        printf("QUICK HULL COULD NOT BE FORMED");
        // quickhull can't be formed by the two lines
        return;
    }
    // finding the maximum and the minimum point
    int max_ind = 0, min_ind = 0;
    for(int i = 1; i < n; i++) {
        if(point[min_ind].first > point[i].first) {
            min_ind = i;
        }
        if(point[max_ind].first < point[i].first) {
            max_ind = i;
        }
    }
    // recurring to the both sides
    quickHULL(min_ind, max_ind, 1); // for one side of the polygon
    quickHULL(min_ind, max_ind, -1); // for the other side of polygon
}

void printHull() {
    // method to print the convex hull
    int sz = hull.size();
    for(auto it = hull.begin(); it!= hull.end(); it++, sz--) {
        if(sz == 1) {
            cout << it->first << " " << it->second;
            break;
        }
        cout << it->first <<" " << it->second <<", ";
    }
    hull.clear();
    cout << "\n";
}

void Main() {
    int t;
    scanf("%d",&t);
    int x, y;
    while(t-->0) {
        scanf("%d",&n);
        for(int i =0; i < n; i++) {
            scanf("%d%d",&x, &y);
            point[i] = {x, y};
        }
        quickHull();
        printHull();
    }
}

int main() {
  Main();
	return 0;
}
