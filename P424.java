import java.io.*;
import java.math.BigInteger;

public class P424 {
    public static void main(String[] args) throws Exception {
	BigInteger sum = BigInteger.ZERO;

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	while(true) {
	    String line = br.readLine();
	    BigInteger b = new BigInteger(line.trim());
	    if(b.signum() == 0)
		break;
	    sum = sum.add(b);
	}
	// Output:
	System.out.println(sum);
    }
}
