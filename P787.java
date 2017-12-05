import java.math.BigInteger;
import java.util.*;

public class P787 {
    private static BigInteger update(BigInteger max, ArrayList<Integer> a) {
      if(a.isEmpty())
	return max;
      BigInteger ret = max;

      BigInteger left = BigInteger.ONE;
      for(int i = 0; i < a.size(); ++i) {
	left = left.multiply(BigInteger.valueOf(a.get(i)));
	if(ret == null || left.compareTo(ret) > 0)
	  ret = left;
      }
      BigInteger right = BigInteger.ONE;
      for(int i = a.size()-1; i >= 0; --i) {
	right = right.multiply(BigInteger.valueOf(a.get(i)));
	if(ret == null || right.compareTo(ret) > 0)
	  ret = right;
      }

      a.clear();
      return ret;
    }

    public static void main(String[] args) throws Exception {
	Scanner s = new Scanner(System.in);
	while(s.hasNextInt()) {
	  BigInteger max = null;
	  ArrayList<Integer> a = new ArrayList<Integer>();

	  while(s.hasNextInt()) {
	    int n = s.nextInt();
	    if(n == -999999) {
	      max = update(max, a);
	      break;
	    }
	    else if(n == 0) {
	      max = update(max, a);	      
	      if(max == null || max.compareTo(BigInteger.ZERO) < 0)
		max = BigInteger.ZERO;
	    }
	    else {
	      a.add(n);
	    }
	  }
	  max = update(max, a);
	  System.out.println(max.toString()); // Fails if n is null... which we want.
	} // while s.hasNextInt()
    } // int main
} // class
