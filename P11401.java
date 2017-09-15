import java.io.*;
import java.math.BigInteger;

public class P11401 {
    public static void main(String[] args) throws Exception {
	BigInteger[] ret = new BigInteger[1000001];
	ret[3] = BigInteger.ZERO;
	for(int i = 4; i <= 1000000; ++i)
	    ret[i] = ret[i-1].add(BigInteger.valueOf(((i-(long)2)/2) * ((i-(long)1)/2)));	
	
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	while(null != (line = br.readLine())) {
	    int N = Integer.parseInt(line.trim());
	    if(N < 3)
		return;
	    System.out.println(ret[N]);
	}
    }
}
