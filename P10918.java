import java.io.*;
import java.util.Scanner;
import java.math.BigInteger;

public class P10918 {
    public static void main(String[] args) throws Exception {
	BigInteger TWO = BigInteger.ONE.add(BigInteger.ONE);
	BigInteger[] above1 = new BigInteger[31],
	    below1 = new BigInteger[31],
	    above2 = new BigInteger[31],
	    below2 = new BigInteger[31],
	    full = new BigInteger[31];

	// 1 row:
	above1[1] = below1[1] = full[1] = BigInteger.ZERO;
	above2[1] = below2[1] = full[0] = BigInteger.ONE;

	for(int i = 2; i <= 30; ++i) {
	    above1[i] = below2[i-1];
	    below1[i] = above2[i-1];
	    above2[i] = below1[i-1].add(full[i-1]);
	    below2[i] = above1[i-1].add(full[i-1]);
	    full[i] = above1[i].add(below1[i]).add(full[i-2]);
	}

	Scanner s = new Scanner(System.in);
	while(true) {
	    int N = s.nextInt();
	    if(N == -1)
		return;
	    System.out.println(full[N]);
	}
    }
}
