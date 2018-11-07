/* IMPORTANT: Multiple classes and nested static classes are supported */


//imports for BufferedReader
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.*;

//import for Scanner and other utility classes
import java.util.*;


// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail


class HackerEarth {

    static class Node {
        long st, en, sz;
        Node(long start, long end) {
          st = start; en = end; sz = end-start+1;
        }
    }

    static class NodeCompare implements Comparator<Node>{

      @Override
      public int compare(Node a, Node b) {
          if(a.sz == b.sz) {
            if(a.st < b.st) {
              return -1;
            }else {
              return 1;
            }
          }else if(a.sz < b.sz) {
            return 1;
          }else {
            return -1;
          }
      }
    }

    // static ArrayList<Node> oldal = new ArrayList<Node>();
    static ArrayList<Node> newal1 = new ArrayList<Node>();
    static Set<Node> oldal = new TreeSet<Node>(new NodeCompare());

    static StringTokenizer stk;
    static BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
    static long n , k;
    static long a[] = new long[100007];
    static String str = "";
    static HashMap<Long, Long> hm = new HashMap<Long, Long>();
    static int q;
    static long qr[] = new long[100007];
    static long ans[] = new long[100007];

    public static void main(String args[]) throws IOException{


    	stk = new StringTokenizer(bf.readLine());
        n = Long.parseLong(stk.nextToken());
        k = Long.parseLong(stk.nextToken());
        str = bf.readLine();
        stk = new StringTokenizer(bf.readLine());
       	q = Integer.parseInt(stk.nextToken());

       	for(int i = 0; i < q; i++) {
          stk = new StringTokenizer(bf.readLine());
          qr[i] = Long.parseLong(stk.nextToken());
       }

       preProcess();
       postProcess();



    }

	static void postProcess() {
        for(int i = 0; i < q; i++) {
          if(hm.containsKey(qr[i])){
            System.out.println(hm.get(qr[i]));
          }else {
            System.out.println(-1);
          }
        }
    }

    static void preProcess() {

    	long currStart = 1, currEnd = n;
    	long size = 0;
    	long mid = 0;
        Node temp ;

        oldal.add(new Node(1, n));

        for(long i = 0; i < k; i++) {

    		temp = removeFirst(oldal);

    		if(i == k) break;
    		currStart = temp.st;
    		currEnd = temp.en;
    		size = temp.sz;

    		//System.out.println(temp.st + " "+ temp.en + " "+ temp.sz + " "+ oldal.size());

    		if(size%2==1) {

    			mid = (currStart+currEnd)>>1;
    			hm.put(mid, i+1);
    			oldal.add(new Node(currStart, mid-1));
    			oldal.add(new Node(mid+1, currEnd));
    		}else {

    			if(str.charAt((int)i)=='L'){
    				mid = (currStart+currEnd)>>1;
    				hm.put(mid, i+1);
    				oldal.add(new Node(currStart, mid-1));
    				oldal.add(new Node(mid+1, currEnd));
    			}else {
    				mid = (currStart+currEnd)>>1;
    				hm.put(mid+1, i+1);
    				oldal.add(new Node(currStart, mid));
    				oldal.add(new Node(mid+2, currEnd));
    			}
    		}
        }

    }


	public static <T> T removeFirst(Collection<? extends T> c) {
	  Iterator<? extends T> it = c.iterator();
	  if (!it.hasNext()) { return null; }
	  T removed = it.next();
	  it.remove();
	  return removed;
	}


}