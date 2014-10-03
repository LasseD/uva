import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Stack;
import java.util.TreeMap;
import java.util.TreeSet;

public class P105 {
	public static void main(String[] args) throws IOException {
		int[] l = new int[5000];
		int[] h = new int[5000];
		int[] r = new int[5000];
		
		// Read input:
    	BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
    	String line;
    	int num = 0;
    	while(null != (line = rd.readLine())) {
    		line = line.trim();
    		if(line.isEmpty())
    			break;
    		String[] parts = line.split(" ");
    		l[num] = Integer.parseInt(parts[0]);
    		h[num] = Integer.parseInt(parts[1]);
    		r[num] = Integer.parseInt(parts[2]);
    		num++;
    	}
//    	System.err.println("Number of buildings: " + num);
    	
    	Pair[] ra = new Pair[num]; // ra[i] = (r, index of house with r) ordered by r
    	for(int i = 0; i < num; ++i) {
    		ra[i] = new Pair(r[i], i);
    	}
    	// Sort ra by r:
    	Arrays.sort(ra);

    	// Walk:
    	int li = 0;
    	int ri = 0;
    	int x = l[0];
    	TreeSet<Pair> sweepLine = new TreeSet<Pair>(); // Pairs here are (-h, index of house with h)
    	while(l[li] == x && li < num) {
    		sweepLine.add(new Pair(-h[li], li));
    		li++;
    	}
    	boolean first = true;
    	int hBefore = -sweepLine.first().a;
		int xBefore = x;
    	while(!(sweepLine.isEmpty() && li == num)) {
    		if(li != num && l[li] < ra[ri].a) { // Insertion:
    			sweepLine.add(new Pair(-h[li], li));    			
    			x = l[li];
    			li++;
    		}
    		else { // Removal:
    			Pair rp = ra[ri];
    			int rh = h[rp.b];
    			x = rp.a;
    			sweepLine.remove(new Pair(-rh, rp.b));
    			ri++;
    		}
    		int hNow = sweepLine.isEmpty() ? 0 : -sweepLine.first().a;
    		if(x != xBefore) {
    			if(hBefore != hNow) {
        	    	System.out.print((!first ? " " : "") + xBefore);
        	    	System.out.print(" " + hBefore);    			
        	    	xBefore = x;
        	    	first = false;
    			}    				
    		}
    		hBefore = hNow;
    	}
    	System.out.print(" " + xBefore);
    	System.out.print(" " + hBefore);    			
    	System.out.println();
	}
	
	private static class Pair implements Comparable<Pair> {
		int a, b;
		
		public Pair(int a, int b) {
			this.a = a;
			this.b = b;
		}
		
		@Override
		public int compareTo(Pair other) {
			if(a != other.a)
				return a-other.a;
            return b-other.b;
		}
	}
}
