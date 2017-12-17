import java.util.Scanner;

public class P10916 {
    public static void main(String[] args) throws Exception {
	// 1960 -> 0, 1970 -> 1, ...
	int[] bits = new int[21];
	int[] ret = new int[21];
	bits[0] = 4;
	ret[0] = 3;

	double logEN = Math.log(1);
	int N = 1;

	for(int year = 1970, i = 1; year <= 2160; year+=10, ++i) {
	    bits[i] = 2*bits[i-1];
	    while(logEN <= bits[i]*Math.log(2)) {
		++N;
		logEN += Math.log(N);
	    }
	    ret[i] = N-1;
	}
	
	Scanner s = new Scanner(System.in);
	while(true) {	    
	    N = s.nextInt();
	    if(N == 0)
		return;
	    N -= 1960;
	    N /= 10;
	    System.out.println(ret[N]);
	}
    }
}
