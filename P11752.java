import java.math.BigInteger;
import java.util.Comparator;
import java.util.TreeSet;

public class P11752 {
	private static class Long64BitCmp implements Comparator<Long> {
		@Override
		public int compare(Long o1, Long o2) {
			long l1 = o1.longValue();
			long l2 = o2.longValue();
			if(l1 == l2)
				return 0;
			if(o1 > 0 && o2 > 0) {
				if(l1 < l2)
					return -1;
				return 1;				
			}
			if(o1 > 0)
				return -1;
			if(o2 > 0)
				return 1;
			l1 = o1.longValue() & Long.MAX_VALUE;
			l2 = o2.longValue() & Long.MAX_VALUE;
			if(l1 < l2)
				return -1;
			return 1;
		}		
	}
	
	private static final BigInteger B = BigInteger.valueOf(65536);
	private static final BigInteger BB = B.multiply(B);
	private static final BigInteger BBBB = BB.multiply(BB);
	private static final BigInteger BBBB_1 = BBBB.subtract(BigInteger.valueOf(1));
	private static final BigInteger XXXX = BBBB.divide(BigInteger.valueOf(2));
	
	public static void main(String[] args) {
		long start = System.currentTimeMillis();
		Long64BitCmp cmp = new Long64BitCmp();
		TreeSet<Long> res = new TreeSet<Long>(cmp);
		final int MAX_CUBE_ROOT = 65536;
		final int MAX_6_ROOT = 1625;

		// Find all i^2 and i^4 powers
		for(long i = 1; i < MAX_CUBE_ROOT; ++i) {
			long ii = i*i;
			long iiii = ii*ii;
			res.add(iiii);
		}
		System.err.println((System.currentTimeMillis()-start) + "ms.");

		// Find all higher powers, but 
		for(long i = 2; i <= MAX_CUBE_ROOT; ++i) { // MAX_6_ROOT
			long base = i*i;
			while(base <= 264062500) { // 2640625
				BigInteger baseAsBigInt = BigInteger.valueOf(base);
				BigInteger s = baseAsBigInt.multiply(baseAsBigInt);
				while(s.compareTo(BBBB_1) < 0) {
					res.add(s.longValue());
					s=s.multiply(baseAsBigInt);
				}
				base *= i;
			}
		}

		System.err.println((System.currentTimeMillis()-start) + "ms.");//*/
		StringBuilder sb = new StringBuilder();
		for(long l : res) {			
			if(l > 0) {
				sb.append(l);
			}
			else {
				sb.append(BigInteger.valueOf(l & Long.MAX_VALUE).add(XXXX));
			}
			sb.append('\n');
		}		
		System.out.println(sb);
		System.err.println((System.currentTimeMillis()-start) + "ms.");//*/
		System.err.println(res.size());
	}
}


/*
public class P11752 {
	private static final long[] power3Plus = new long[]{1024l,16384l,59049l,4194304l,4782969l,9765625l,60466176l,67108864l,282475249l,6103515625l,10000000000l,17179869184l,25937424601l,31381059609l,61917364224l,78364164096l,137858491849l,274877906944l,289254654976l,576650390625l,678223072849l,2015993900449l,2541865828329l,3570467226624l,6131066257801l,10240000000000l,16679880978201l,26559922791424l,41426511213649l,63403380965376l,70368744177664l,100000000000000l,141167095653376l,296196766695424l,379749833583241l,420707233300201l,590490000000000l,819628286980801l,1125899906842624l,1283918464548864l,1531578985264449l,2064377754059776l,2384185791015625l,2758547353515625l,3937376385699289l,4808584372417849l,6278211847988224l,8140406085191601l,10485760000000000l,11112006825558016l,13422659310152401l,16677181699666569l,17080198121677824l,21611482313284249l,27197360938418176l,29192926025390625l,34050628916015625l,42420747482776576l,52599132235830049l,64925062108545024l,97656250000000000l,119042423827613001l,131621703842267136l,144555105949057024l,168377826559400929l,174887470365513049l,210832519264920576l,253295162119140625l,288230376151711744l,303305489096114176l,362033331456891249l,374813367582081024l,430804206899405824l,511116753300641401l,604661760000000000l,713342911662882601l,799006685782884121l,839299365868340224l,984930291881790849l,1346274334462890625l,1350851717672992089l,1490116119384765625l,1568336880910795776l,1638400000000000000l,1822837804551761449l,2113922820157210624l,2446194060654759801l,2824752490000000000l,3243919932521508681l,3255243551009881201l,3743906242624487424l,3909821048582988049l,4297625829703557649l,4611686018427387904l,4923990397355877376l,5631351470947265625l,6221821273427820544l,6428888932339941376l,7326680472586200649l,8335775831236199424l};

	public static void main(String[] args) {
		long start = System.currentTimeMillis();
		
		long[] power2 = new long[1447];
		for(int i = 2; i <= 1448; ++i) {
			long ii = i*(long)i;
			long s = ii*ii*ii;
			power2[i-2] = s;
		}
		
		//start = System.currentTimeMillis();
		StringBuilder sb = new StringBuilder();		
		int i2 = 0;
		int i3 = 0;		
		for(int i = 1; i <= 55108; ++i) {
			long ii = i*(long)i;
			long s = ii*ii;

			while(i2 < power2.length && power2[i2] < s) {
				long s2 = power2[i2];
				while(i3 < power3Plus.length && power3Plus[i3] < s2) {
					sb.append(power3Plus[i3]);
					sb.append('\n');
//					System.out.println(power3Plus[i3]);					
					++i3;
				}
				sb.append(s2);
				sb.append('\n');
//				System.out.println(s2);					
				++i2;
			}
			while(i3 < power3Plus.length && power3Plus[i3] < s) {
				sb.append(power3Plus[i3]);
				sb.append('\n');
				++i3;
			}
			sb.append(s);
			sb.append('\n');
//			System.out.print(s);					
//			System.out.print('\n');					
		}
		System.out.print(sb);
//		System.err.println((System.currentTimeMillis()-start) + "ms.");
	}
}
*/