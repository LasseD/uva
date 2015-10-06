import java.io.*;
import java.math.BigInteger;

public class P10523 {
    public static void main(String[] args) throws Exception {
	BigInteger[] Ai = new BigInteger[2400]; // 2400 = 150*16
	BigInteger[] iAi = new BigInteger[2400]; // 2400 = 150*16
	int[] limN = new int[16];
	for(int i = 0; i < 16; ++i)
	    limN[i] = 0;

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	while(null != (line = br.readLine())) {
	    String[] parts = line.split("\\s+");
	    int N = Integer.parseInt(parts[0]);
	    int A = Integer.parseInt(parts[1]);

	    while(limN[A] < N) {
		//std::cerr << "Constructing for N=" << (limN[A]+1) << ", A=" << A << std::endl;
		int currentLim = limN[A];
		BigInteger bigA = BigInteger.valueOf(A);
		BigInteger bigLimPlusOne = BigInteger.valueOf(currentLim+1);
		BigInteger nextAi  = currentLim == 0 ? bigA : Ai[150*A+currentLim-1].multiply(bigA);
		BigInteger nextIAi = currentLim == 0 ? nextAi : iAi[150*A+currentLim-1].add(nextAi.multiply(bigLimPlusOne));
		//std::cout << " A^N=" << nextAi << ", NA^N=" << nextIAi << std::endl;
		Ai[150*A+currentLim] = nextAi;
		iAi[150*A+currentLim] = nextIAi;
		++limN[A];
	    }

	    // Output:
	    System.out.println(iAi[150*A+N-1].toString());
	}
    }
}
