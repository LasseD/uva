import java.io.*;
import java.util.Scanner;
import java.math.BigInteger;

public class P10359 {
    public static void main(String[] args) throws Exception {
	BigInteger TWO = BigInteger.ONE.add(BigInteger.ONE);
	BigInteger[] ret = new BigInteger[251];
	ret[0] = ret[1] = BigInteger.ONE;

	for(int i = 2; i <= 250; ++i) {
	    ret[i] = ret[i-1].add(ret[i-2].multiply(TWO));
	}

	Scanner s = new Scanner(System.in);
	while(s.hasNext()) {
	    int N = s.nextInt();
	    System.out.println(ret[N]);
	}
    }
}
