import java.math.BigInteger;
import java.util.ArrayList;

public class P485 {
	public static void main(String[] args) {
		ArrayList<BigInteger> left = new ArrayList<BigInteger>();
		left.add(BigInteger.ONE);
		print(left, true);
		print(left, false);
		left.add(BigInteger.valueOf(2));
		print(left, true);
		boolean uneven = false;
		while(true) {
			// Compute new row:
			int last = left.size()-1;
			if(uneven) { // Only add new if uneven:
				left.add(left.get(last).add(left.get(last)));
			}
			for(int i = last; i > 0; --i) {
				left.set(i, left.get(i).add(left.get(i-1)));
			}
			
			// Output new row:
			print(left, uneven);
			uneven = !uneven;

			// Check if done:
			if(left.get(left.size()-1).toString().length() > 60)
				return;
		}
	}
	
	private static void print(ArrayList<BigInteger> left, boolean uneven) {
		StringBuilder sb = new StringBuilder();
		boolean first = true;
		for(BigInteger i : left) {
			if(!first)
				sb.append(' ');
			sb.append(i);
			first = false;
		}
		int firstIndex = uneven ? left.size()-2 : left.size()-1;		
		for(int i = firstIndex; i >= 0; --i) {
			sb.append(' ');
			sb.append(left.get(i));
		}
		System.out.println(sb);
	}
}
