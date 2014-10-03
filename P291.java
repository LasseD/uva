public class P291 {
	public static void main(String[] args) {
		// Build graph:
		boolean[][] exists = new boolean[6][6];
		exists[1][2] = true;
		exists[1][3] = true;
		exists[1][5] = true;
		exists[2][3] = true;
		exists[2][5] = true;
		exists[3][4] = true;
		exists[3][5] = true;
		exists[4][5] = true;
		
		// Try all paths:
		int i = 123153451;
		while(true) {
			++i;
			// Relax path:
			int mult = 1;
			for(int j = 0; j < 8; ++j) {
				if((i / mult) % 10 > 5) {
					i-=5*mult;
					i+=mult*10;
				}
				mult*=10;
			}
			if(i > 154352312)
				return;
			// Check all 8 edges:
			mult = 1;
			boolean ok = true;
			for(int j = 0; j < 8; ++j) {
				int b = (i / mult) % 10;
				assert(b > 0 && b < 6);
				mult*=10;
				int a = (i / mult) % 10;
				assert(a > 0 && a < 6);
				if(b < a) {
					int tmp = b;
					b = a;
					a = tmp;
				}
				if(!exists[a][b]) {
					ok = false;
					break;
				}
				exists[a][b] = false;
			}
			// output if successful:
			if(ok)
				System.out.println(i);

			// Reset graph:
			exists[1][2] = true;
			exists[1][3] = true;
			exists[1][5] = true;
			exists[2][3] = true;
			exists[2][5] = true;
			exists[3][4] = true;
			exists[3][5] = true;
			exists[4][5] = true;
		}
	}
}
