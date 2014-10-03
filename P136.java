
public class P136 {
	public static void main(String[] args) {
/*		int i = 2;
		int counter = 1;
		while(counter < 1500) {
			if(isUgly(i)) {
				++counter;
//				System.out.println("ugly number " + counter + " is " + i + ".");
			}
			++i;
		}
		System.out.println("The " + counter + "'th ugly number is " + --i + ".");
		*/
		System.out.println("The 1500'th ugly number is 859963392.");
	}
	
	private static boolean isUgly(int i) {
		while(i % 5 == 0)
			i /= 5;
		while(i % 3 == 0)
			i /= 3;
		while(i % 2 == 0)
			i /= 2;
		return i == 1;
	}
}
