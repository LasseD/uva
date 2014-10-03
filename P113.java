import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;


public class P113 {
	public static void main(String[] args) throws IOException {
		BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
		String line;
		BigInteger TWO = BigInteger.ONE.add(BigInteger.ONE);
		int totalIterations = 0;
		while((line = rd.readLine()) != null) {
			int n = Integer.parseInt(line);
			BigInteger p = new BigInteger(rd.readLine());
			BigInteger low = BigInteger.ONE;
			BigInteger high = p;

			int iterations = 0;
			boolean doingLowLow = true;
			while(low.compareTo(high) < 0) {
				++iterations;
				BigInteger mid;
				BigInteger lowlow;; 
				if(doingLowLow && (lowlow = low.multiply(low)).compareTo(high) < 0)
					mid = lowlow;
				else {		
					mid = low.add(high).divide(TWO);
					doingLowLow = false;
				}
				BigInteger powered = mid.pow(n);
				int cmp = powered.compareTo(p);
				if(cmp == 0) {
					low = high = mid;
					break;
				}
				if(cmp < 0) {
					if(low.equals(mid))
						low = low.add(BigInteger.ONE);
					else
						low = mid;					
				}
				else {
					if(high.equals(mid))
						high = high.subtract(BigInteger.ONE);
					else
						high = mid;
				}
			}
			System.out.println(low);
			System.err.println("Iterations: " + iterations);
			totalIterations+=iterations;
		}
		System.err.println("Total: " + totalIterations);
	}

}
