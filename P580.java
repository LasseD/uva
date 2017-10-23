import java.math.BigInteger;
import java.util.Scanner;

public class P580 {
    public static void main(String[] args) throws Exception {
	BigInteger[] all = new BigInteger[31];
	BigInteger[] top0 = new BigInteger[31];
	BigInteger[] top1 = new BigInteger[31];
	BigInteger[] top2 = new BigInteger[31]; // 2 uranium blocks on top
	BigInteger[] ret = new BigInteger[31];

	all[1] = BigInteger.ONE.add(BigInteger.ONE);
	top0[1] = BigInteger.ONE;
	top1[1] = BigInteger.ONE;
	top2[1] = BigInteger.ZERO;
	ret[1] = BigInteger.ZERO;
	
	for(int i = 2; i < 31; ++i) {
	    all[i] = all[i-1].add(all[i-1]);
	    top0[i] = top1[i-1].add(top2[i-1]).add(top0[i-1]);
	    top1[i] = top0[i-1];
	    top2[i] = top1[i-1];
	    ret[i] = all[i].subtract(top0[i].add(top1[i]).add(top2[i]));
	}
	
	Scanner s = new Scanner(System.in);
	while(true) {	    
	    int N = s.nextInt();
	    if(N == 0)
		return;
	    System.out.println(ret[N]);
	}
    }
}
