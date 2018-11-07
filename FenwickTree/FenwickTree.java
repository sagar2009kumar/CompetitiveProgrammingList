import java.io.*;
import java.util.*;

/****

	IMPORTANT POINTS TO BE REMEBERED

	1. The max length of the array is 1e5+7.
	2. The size of the fenwick tree will be length+1.
	3. The update will be done on 1 indexed.
	4. The query will be done on 1 indexed.
	5. The array will be taken on 0 indexed.

	e.g

	6
	1 2 3 4 5 6

	rsq(1, 6) -> 21
	rsq(2, 6) -> 20
	rsq(3, 6) -> 18
	rsq(4, 6) -> 15
	rsq(5, 6) -> 11
	rsq(6, 6) -> 6

	e.g

	6
	1 2 3 4 5 6

	query(1) -> 1
	query(2) -> 3
	query(3) -> 6
	query(4) -> 10
	query(5) -> 15
	query(6) -> 21

	6
	1 2 3 4 5 6

	getValAtInd(1) -> 1
	getValAtInd(2) -> 2
	getValAtInd(3) -> 3
	getValAtInd(4) -> 4
	getValAtInd(5) -> 5
	getValAtInd(6) -> 6

****/

class FenwickTree {

	static final int MAX = (int)1e5+7;
	static int sz_ft = 0;
	static int n = 0;
	static BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
	static long bitArr[] = new long[MAX];
	static long a[] = new long[MAX];
	static StringTokenizer stk;

	public static void main(String args[]) throws IOException {

		stk = new StringTokenizer(bf.readLine());
		n = Integer.parseInt(stk.nextToken());

		stk = new StringTokenizer(bf.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Long.parseLong(stk.nextToken());
		}

		constructBIT();

		rangeUpdate(1, 3, 5);
		// rangeUpdate(2, 4, 3);

		// update(2, 8);

		for(int i = 1; i < sz_ft; i++) {
			System.out.println(getValAtInd(i));
		}

	}

	static void constructBIT() {

		setSize();

		for(int i = 1; i < sz_ft; i++) {
			update(i, a[i-1]);
		}
	}

	static void setSize() {
		sz_ft = n+1;
	}

	static void update(int ind, long val) {
		while(ind < sz_ft) {
			bitArr[ind]+= val;
			ind+= ind&(-ind);
		}
	}

	static long query(int ind) {
		long sum = 0;
		while(ind > 0) {
			sum += bitArr[ind];
			ind-= ind&(-ind);
		}
		return sum;
	}

	static long getValAtInd(int ind) {
		return query(ind)-query(ind-1);
	}

	static void rangeUpdate(int left, int right, long val) {
		update(left, val);
		update(right+1, -val);
	}

	static long rsq(int left, int right) {
		// 9910888047
		return query(right) - query(left-1);
	}

}