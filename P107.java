import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class P107 {
	public static void main(String[] args) throws IOException {
//		long time = System.currentTimeMillis();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line;
		StringBuilder sb = new StringBuilder();
		while((line = br.readLine()) != null) {
			String[] parts = line.split("\\s+");
			long heightOfLargestCat = Long.parseLong(parts[0]);
			if(heightOfLargestCat == 0) {
//				System.err.println("Time total: " + (System.currentTimeMillis()-time));
				System.out.print(sb.toString());
				return;							
			}
			long numberOfSmallestCats = Long.parseLong(parts[1]);
			if(numberOfSmallestCats+1 == heightOfLargestCat) {
				sb.append("1 ");
				sb.append(numberOfSmallestCats+heightOfLargestCat);
				sb.append('\n');
				continue;
			}

			long n = findN(heightOfLargestCat, numberOfSmallestCats);
			// Count lazy cats and sum of heights:
			long sumOfHeights = 1*numberOfSmallestCats;
			long numberOfLazyCats = 0;
			long numberOfCatsInLayer = 1;
			long heightOfCatsInLayer = heightOfLargestCat;
			
			while(heightOfCatsInLayer > 1) {
				sumOfHeights += numberOfCatsInLayer*heightOfCatsInLayer;
				numberOfLazyCats += numberOfCatsInLayer;
				
				heightOfCatsInLayer /= n+1;						
				numberOfCatsInLayer *= n;						
			}
			sb.append(numberOfLazyCats);
			sb.append(' ');
			sb.append(sumOfHeights);
			sb.append('\n');
		}	 
	}
	
	//private static final double INV_LOG2 = 1.0/Math.log(2);
	private static long findN(long heightOfLargestCat, long numberOfSmallestCats) {
		if(numberOfSmallestCats == 1)
			return 1;
		for(int power = 2; true; ++power) {
			long base = Math.round(Math.pow(numberOfSmallestCats, 1.0/power)); // take power's root of n and check
			// check base:
			long trialN = base;
			long trialN1 = base+1;
			for(int i = 1; i < power; ++i) {
				trialN*=base;
				trialN1*=(base+1);
			}
			if(trialN == numberOfSmallestCats && trialN1 == heightOfLargestCat) {
				return base;
			}
		}
	}
}
