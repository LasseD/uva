public class P138 {
	public static void main(String[] args) {
		int found = 2;

		// Setup odd:
		long sumLower = 0;
		long sumUpper = 0;
		long herHouse = 35;
		long houseMax = 49;
		for(long i = 1; i < herHouse; ++i) {
			sumLower += i;
		}
		for(long i = herHouse+1; i <= houseMax; ++i) {
			sumUpper += i;
		}
		
		// Two in output given:
		System.out.println(ten(6) + ten(8));
		System.out.println(ten(herHouse) + ten(houseMax));
		
		while(found < 10) {
			// Update odd:
			++houseMax;
			sumUpper+=houseMax;
			while(sumLower < sumUpper) {
				sumLower+=herHouse;
				++herHouse;
				sumUpper-=herHouse;
			}
			if(sumLower == sumUpper) {
				System.out.println(ten(herHouse) + ten(houseMax));				
				found++;
			}
		}
	}
	
	private static String ten(long i) {
		String res = "" + i;
		while(res.length() < 10)
			res = " " + res;
		return res;
	}
}
