import java.util.Scanner;

public class P11231 {
    private static long gib(long n, long m, int c) {
	if(c == 0) { // Bottom right corner is black:
	    /*
	      XOXOXOXOXO
	      1Y1Y1Y1Y1Y
	      XOXOXOXOXO
	     */	    
	    --n;
	    long fromXGrid = ((m-6)/2) * ((n-6)/2);
	    ++n; --m;
	    long fromYGrid = ((m-6)/2) * ((n-6)/2);
	    return fromXGrid + fromYGrid;	    
	}
	else { // Bottom right corner is white, like a chess board:
	    /*
	      XOXOX
	      1Y1Y1
	      XOXOX
	     */	    
	    long fromXGrid = ((m-6)/2) * ((n-6)/2);
	    --n; --m;
	    long fromYGrid = ((m-6)/2) * ((n-6)/2);
	    return fromXGrid + fromYGrid;
	}	
    }

    public static void main(String[] args) throws Exception {
	Scanner s = new Scanner(System.in);

	while(true) {
	    int n = s.nextInt();
	    int m = s.nextInt();
	    int c = s.nextInt();
	    if(n == 0 && m == 0 && c == 0)
		return;
	    System.out.println(gib(n, m, c));
	}
    }
}
