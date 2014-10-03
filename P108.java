import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class P108 {
	public static void main(String[] args) throws IOException {
    	BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
    	String line;
    	line = rd.readLine();
    	final int N = Integer.parseInt(line.trim());
    	final byte[] GRID = new byte[N*N];    	
    	
    	// Fill GRID:
    	int i = 0;
    	while(null != (line = rd.readLine())) {
    		if(line.trim().isEmpty())
    			return;
    		Scanner s = new Scanner(line);
    		while(s.hasNextByte()) {
        		GRID[i] = s.nextByte();
    			++i;
    		}    		
    	}
    	
    	// Compute max sum:
    	int maxSum = Integer.MIN_VALUE;
    	for(int startX = 0; startX < N; ++startX) {
    		for(int width = 0; startX+width < N; ++width) {
    			int maxUsingLastY = 0;
    			for(int y = 0; y < N; ++y) {
    				// Compute own row value:
    				int ySum = 0;
    				for(int x = startX; x < startX+width; ++x) {
    					ySum += GRID[y*N+x];
    				}
    				if(ySum > 0) {
    					maxUsingLastY+=ySum;
    					if(maxUsingLastY > maxSum)
    						maxSum = maxUsingLastY;
    				}
    				else {
    					maxUsingLastY= Math.max(0, maxUsingLastY+ySum);
    				}
    			}
    		}
    	}
    	
    	// Output results:
    	System.out.println(maxSum);
	}
}
