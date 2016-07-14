import java.io.*;
import java.math.BigInteger;

// Compute (a.b)^exp
public class P748 {
    private static String noTrailingZeros(String s) {
	return s.replaceAll("0+$", "");
    }

    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	while(null != (line = br.readLine())) {
	    final String[] lineParts = line.trim().split("\\s+");
	    if(lineParts.length != 2)
		throw new IllegalArgumentException("Number of line parts: " + lineParts.length);
	    final String base = lineParts[0];
	    final int exp = Integer.parseInt(lineParts[1]);
	    final String[] baseParts = base.split("\\.");
	    final String a = baseParts[0];
	    final String b = baseParts[1];
	    //System.err.println("ab=" + a + b);

	    final BigInteger ab = new BigInteger(a+b);
	    BigInteger noDot = ab;
	    for(int i = 1; i < exp; ++i)
		noDot = noDot.multiply(ab);
	    String noDotStr = noDot.toString();
	    // move the dot in exp*|b| positions from the right:
	    int dotPositionFromRight = exp * b.length();
	    int len = noDotStr.length();
	    if(len < dotPositionFromRight) {		
		String zeros = new String(new char[dotPositionFromRight-len]).replace('\0', '0');
		noDotStr = zeros + noDotStr;
		len = noDotStr.length();
	    }
	    String outLeft = noDotStr.substring(0, len-dotPositionFromRight);
	    String outRight = noTrailingZeros(noDotStr.substring(len-dotPositionFromRight));
	    if(outRight.length() > 0)
		System.out.println(outLeft + "." + outRight);
	    else
		System.out.println(outLeft);
	}
    }
}
