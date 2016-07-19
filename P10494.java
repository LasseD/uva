import java.io.*;
import java.math.BigInteger;

public class P10494 {
    public static void main(String[] args) throws Exception {
	BigInteger sum = BigInteger.ZERO;

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	while(null != (line = br.readLine())){
	    String[] parts = line.split("\\s+");
	    if(parts.length != 3)
		throw new Exception();
	    BigInteger a = new BigInteger(parts[0]);
	    boolean divide = parts[1].charAt(0) == '/';
	    BigInteger b = new BigInteger(parts[2]);
	    System.out.println(divide ? a.divide(b) : a.mod(b));
	}
    }
}
