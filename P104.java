import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Scanner;

public class P104 {
	public static void main(String[] args) throws IOException {
		double[][][] table = new double[20][20][20];
		byte[][][] back = new byte[20][20][20]; // from (i,j,k) = l used in computation below
		
    	BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
    	String line;
    	while(null != (line = rd.readLine())) {
    		if(line.trim().isEmpty())
    			return;

    		// Parse input:
    		Scanner s = new Scanner(line);
    		byte n = s.nextByte();
    		System.err.println("Start for " + n);
    		
    		/*
    		 table: Best currency conversion rates as:
    		 iteration -> start currency -> end currency
    		 where:
    		 iteration: i = transactions (so up to n transactions in total)
    		 */

    		// Fill first iteration with input values:
    		for(byte i = 0; i < n; ++i) {
    			line = rd.readLine();
        		s = new Scanner(line);
    			for(byte j = 0; j < n; j++) {
    				if(i == j) {
    					table[0][i][j] = 0;
    					continue;
    				}
    				String st = s.next();
    				if(st.charAt(0) == '.')
    					st = "0" + st;
            		table[0][i][j] = Double.parseDouble(st);    				
    			}
    		}
 
    		boolean found = false;
    		byte bestIteration = 0;
    		byte bestCurrency = 0;
    		// Compute all iterations:
    		for(byte i = 1; i < n; ++i) { // i = iteration
    			if(found) break;
    			for(byte j = 0; j < n; ++j) { // j = from
        			if(found) break;
    				for(byte k = 0; k < n; ++k) { // k = to
            			if(found) break;
			    		//System.err.println(i + " Check " + j + " to " + k);
						table[i][j][k] = 0;
    					for(byte l = 0; l < n; ++l) { // l = middle step tryout.    						    						
    						if(l == k) { // Can't do conversion from selv to self.
    							continue;
    						}
    						double newVal = table[i-1][j][l] * table[0][l][k];
    						if(table[i][j][k] < newVal) {
    							table[i][j][k] = newVal;
    							back[i][j][k] = l;
    				    		//System.err.println(i + " " + j + "..." + l + "->" + k + ": " + table[i-1][j][l] +"*"+ table[0][l][k]);
    							if(newVal > 1.01 && j == k) {
    								found = true;
    								bestCurrency = j;
    								bestIteration = i;
    								break;
    							}
    						}							
    					}
    				}
    			}
    		}
    		
    		// Evaluate  result:
    		if(!found) {
    		  System.out.println("no arbitrage sequence exists");
    		  continue;
    		}
    		
    		LinkedList<Byte> stack = new LinkedList<Byte>();
    		byte c = bestCurrency;
			stack.addFirst(c);
    		for(int i = bestIteration; i > 0; --i) {
    			c = back[i][bestCurrency][c];
    			stack.addFirst(c);
    		}
			stack.addFirst(bestCurrency);
    		
    		boolean first = true;
    		for(byte i : stack) {
    			if(!first) {
        			System.out.print(" ");    				    		
    			}
    			System.out.print(i+1);
    			first = false;
    		}
    		System.out.println();
    	}
    }
}
