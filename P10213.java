import java.util.Scanner;
import java.math.BigInteger;

/*
  Moser's Circle Problem: See http://mathworld.wolfram.com/CircleDivisionbyChords.html
 */
public class P10213 {
    public static void main(String[] args) throws Exception {
	BigInteger SIX = BigInteger.valueOf(6);
	BigInteger TWENTY_THREE = BigInteger.valueOf(23);
	BigInteger EIGHTEEN = BigInteger.valueOf(18);
	BigInteger TWENTY_FOUR = BigInteger.valueOf(24);

	Scanner s = new Scanner(System.in);
	int cases = s.nextInt();
	for(int cas = 0; cas < cases; ++cas) {
	    BigInteger N = s.nextBigInteger();
	    BigInteger NN = N.multiply(N);
	    BigInteger NNN = NN.multiply(N);
	    BigInteger NNNN = NN.multiply(NN);
	    BigInteger ret = (NNNN.subtract(NNN.multiply(SIX)).add(NN.multiply(TWENTY_THREE)).subtract(N.multiply(EIGHTEEN)).add(TWENTY_FOUR)).divide(TWENTY_FOUR);
	    System.out.println(ret);
	}
    }
}
