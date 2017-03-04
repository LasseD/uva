import java.io.*;
import java.math.BigInteger;

public class P10069 {
    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	int cases = Integer.parseInt(br.readLine().trim());
	for(int cas = 0; cas < cases; ++cas) {
	    String X = br.readLine().trim();
	    String Z = br.readLine().trim();
	    if(Z.length() > X.length()) {
		System.out.println(0);
		continue;
	    }

	    BigInteger A[] = new BigInteger[2*X.length()];
	    for(int i = 0; i < X.length(); ++i)
		A[i] = BigInteger.ONE;

	    int prevI = 0;
	    int currI = X.length();

	    for(int i = 1; i <= Z.length(); ++i) {
		for(int j = 0; j + i - 1 < X.length(); ++j) {
		    if(X.charAt(j+i-1) == Z.charAt(i-1)) {
			A[currI+j] = A[prevI+j];
		    }
		    else
			A[currI+j] = BigInteger.ZERO;
		    if(j > 0)
			A[currI+j] = A[currI+j].add(A[currI+j-1]);
		}
		int tmp = currI;
		currI = prevI;
		prevI = tmp;
	    }
	    System.out.println(A[prevI+X.length()-Z.length()]);
	}
    }
}
