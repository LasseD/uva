public class P386 {
	public static void main(String[] args) {
		for(int a = 2; a <= 200; ++a) {
			int aaa = a*a*a;
			for(int b = 2; b < a; ++b) {
				int bbb = b*b*b;
				for(int c = b; c < a; ++c) {
					int ccc = c*c*c;
					if(bbb+ccc >= aaa)
						break;
					int ddd = aaa-bbb-ccc;
					if(ddd < ccc)
						break;
					int lowerD = (int)Math.cbrt(ddd);
					int lowerDDD = lowerD*lowerD*lowerD;
					if(aaa == bbb+ccc+lowerDDD) {
						System.out.println("Cube = " + a + ", Triple = (" + b + "," + c + "," + lowerD + ")");
					}
					else {
						int upperD = lowerD+1;
						int upperDDD = upperD*upperD*upperD;
						if(aaa == bbb+ccc+upperDDD) {
							System.out.println("Cube = " + a + ", Triple = (" + b + "," + c + "," + upperD + ")");
						}						
					}
				}
			}
		}
	}
}
