import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;


public class P100 {
    public static void main(String[] args) throws IOException {
    	BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
    	String line;
    	while(null != (line = rd.readLine())) {
    		if(line.trim().isEmpty())
    			return;
    		Scanner s = new Scanner(line);
    		int i = s.nextInt();
    		System.out.print(i + " ");
    		int j = s.nextInt();
    		System.out.print(j + " ");
    		if(j < i) {
    			int swap = i;
    			i = j;
    			j = swap;
    		}
    		// Compute the max cycle length:
    		int max = 0;
    		for(int k = i; k <= j; ++k) {
    			int len = cycleLength(k);
    			if(len > max)
    				max = len;
    		}
    		System.out.println(max);
    	}
    }
    
    public static int cycleLength(int n) {
    	int res = 1;
    	while(n != 1) {
    		if((n & 1) == 1) {
    			n = 3 * n + 1;
    		}
    		else {
    			n >>= 1;
    		}
    		res++;
    	}
    	return res;
    }
}
