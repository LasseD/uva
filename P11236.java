public class P11236 {
	public static void main(String[] args) {
		final int MAX = 2000;
		for(int a = 1; a < MAX; ++a) {
			for(int b = a; a+b < MAX; ++b) {
				for(int c = b; a+b+c < MAX; ++c) {
					// A+B+C+D = ABCD
					// A+B+C = D(ABC-1)
					// a=100A =>
					// a/100+b/100+c/100 = d/100(abc/1000000-1)
					// a+b+c = d(abc/1000000-1) = d(abc/1000000-1000000/1000000) = d(abc-1000000)/1000000 =>
					// d = (a+b+c)*1000000/(abc-1000000)
					if(a*b*c==1000000)
						continue;
					if(((a+b+c)*1000000) % (a*b*c-1000000) != 0)
						continue;
					int d = ((a+b+c)*1000000) / (a*b*c-1000000); 
					if(d < c || (a+b+c+d) > MAX)
						continue;
//					System.out.printf("Tryout %.2f %.2f %.2f %.2f\n", a/100.0, b/100.0, c/100.0, d/100.0);
					if(a+b+c+d == a*b*c*d/1000000) {
						System.out.printf("%.2f %.2f %.2f %.2f\n", a/100.0, b/100.0, c/100.0, d/100.0);
					}
				}
			}
		}
	}
}
