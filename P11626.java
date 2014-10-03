import java.io.IOException;
import java.util.Arrays;
import java.util.Random;

public class P11626 {
	public static final int BUFFER_SIZE = 30;
	public static final int COORD_ADD = 1000000000;

	private static final long[] points = new long[100000];
	private static final byte[] inB = new byte[BUFFER_SIZE];
	private static int inBi = 0;
	private static final byte[] outB = new byte[BUFFER_SIZE];
	private static int outBi = 0;
	private static boolean icr = false;

	private static boolean rightTurn(int diffX, int diffY, int x1, int y1, long p) {
		return diffX*((long)y(p)-y1) < diffY*((long)x(p)-x1);
	}

	private static void checkWrite(int toAdd) {
		if(outBi + toAdd >= BUFFER_SIZE) {
			System.out.write(outB, 0, outBi);
			outBi = 0;
		}	
	}

	private static void checkRead(int toAdd) throws IOException {
		if(inBi + toAdd < BUFFER_SIZE) 
			return;

		int res = BUFFER_SIZE-inBi;  
		for(int i = 0; i < res; ++i) {
			inB[i] = inB[inBi+i];
		}
		System.in.read(inB, res, BUFFER_SIZE-res);
		inBi = 0;
	}

	private static void printLong(int x) {
		if(x < 0) {
			x = -x;
			outB[outBi++] = '-';
		}

		if(x < 10) {
			outB[outBi++] = (byte)('0'+x);
			return;
		}

		int b2 = x;
		int size = 0;
		while(x > 0) {
			x/=10;
			++size;
		}

		x = b2;
		b2 = size;
		while(x > 0) {
			outB[outBi+size-1] = (byte)('0'+(x%10));
			x/=10;
		    --size;
		}
		outBi+=b2;
	}
	
	private static void printPoint(long p) {
		/*System.out.printf("%d %d\n", x(p)-COORD_ADD, y(p)-COORD_ADD);
		return;//*/

		checkWrite(25);

		printLong(x(p)-COORD_ADD);
		outB[outBi++] = ' ';
		printLong(y(p)-COORD_ADD);
		if(icr)
			outB[outBi++] = '\r';    
		outB[outBi++] = '\n';//*/
	}

	private static void writeUInt(int x) {
		/*System.out.printf("%d\n", x);
		return;//*/

		checkWrite(8);

		if(x < 10) {
			outB[outBi++] = (byte)('0'+x);
		    if(icr)
		    	outB[outBi++] = '\r';    
		    outB[outBi++] = '\n';
		    return;
		}

		int b2 = x;
		int size = 0;
		while(x > 0) {
		    x/=10;
		    ++size;
		}

		x = b2;
		b2 = size;
		while(x > 0) {
			outB[outBi+size-1] = (byte)('0'+(x%10));
		    x/=10;
		    --size;
		}
		outBi+=b2;
		if(icr)
			outB[outBi++] = '\r';    
		outB[outBi++] = '\n';//*/
	}

	private static int readLong(int i, boolean isNeg, int size) {
		if(isNeg) {
			++i;
		    --size;
		}
		int res = inB[i++]-'0';
		while(--size > 0) {
			res = 10*res + (inB[i++]-'0');
		}
		if(isNeg)
			return -res;
		return res;
	}

	private static long readPoint() throws IOException {
		/*String[] parts;
		try {
			parts = new BufferedReader(new InputStreamReader(System.in)).readLine().split(" ");
		} catch (IOException e) {
			e.printStackTrace();
			return 0;
		}
		char c = parts[2].charAt(0);
		if(c == 'N')
			return Long.MIN_VALUE;
		int x = Integer.parseInt(parts[0]);
		int y = Integer.parseInt(parts[1]);//*/

		checkRead(27);
	
		int j = inBi;
		boolean xIsNeg = (inB[j++] == '-');
		while(inB[j++] != ' ')
			;
		int xSize = j-inBi-1;

		boolean yIsNeg = (inB[j++] == '-');
		while(inB[j++] != ' ')
			;
		int ySize = j-inBi-2-xSize;
  
		if(inB[j++] == 'N') {
			inBi=j+1;
			if(inB[inBi] < '-')
				++inBi;
			return Long.MIN_VALUE;
		}

		int x = readLong(inBi, xIsNeg, xSize)+COORD_ADD;
		int y = readLong(inBi+xSize+1, yIsNeg, ySize)+COORD_ADD;

		inBi=j+1;
		if(inB[inBi] < '-') {
			++inBi;
		}//*/
		
		return (((long)x) << 32) | (y&0x00000000ffffffffl);
	}

	private static int readUInt() throws IOException {
/*		try {
			return Integer.parseInt(new BufferedReader(new InputStreamReader(System.in)).readLine());
		} catch (IOException e) {
			e.printStackTrace();
			return 0;
		}//*/

		checkRead(8);

		int N = inB[inBi++]-'0';
		byte c;
		while((c = inB[inBi++]) >= '0') {
			N = 10*N + (c-'0');
		}
		if(inB[inBi] < '-') {
			++inBi;
			icr = true;
		}
		else
			icr = false;
		return N;//*/
	}	
	
	private static void generateInput(int n) {
		Random r = new Random();
		System.out.println(1);
		System.out.println(n);
		for(int i = 0; i < n; ++i) {	
			int x = r.nextInt(2*n)-n;
			int y = r.nextInt(2*n)-n;
			System.out.println(x + " " + y + (r.nextBoolean() ? " Y" : " N"));
		}
	}
	
	public static void main(String[] args) throws IOException {
		/*if(args.length == 1) {
			generateInput(Integer.parseInt(args[0]));
			return;
		}//*/		
		System.in.read(inB, 0, BUFFER_SIZE);

		final int NUMBER_OF_TEST_CASES = readUInt();
		for(int IGNORE = 0; IGNORE < NUMBER_OF_TEST_CASES; ++IGNORE) {
			final int N = readUInt();
			
		    // Find points:
		    int pi = 0;
		    int mini = 0;
		    int maxi = 0;
		    for(int j = 0; j < N; ++j) {
		      long p =  readPoint();
		      if(p == Long.MIN_VALUE) {
		    	  //System.err.println("SKIPPING POINT");		    	  
		    	  continue;
		      }
	    	  //System.err.println("READ POINT " + x(p) + " " + y(p));		    	  
			
		      points[pi] = p;				
		      if(points[pi] < points[mini]) {
		    	  mini = pi;
		      }
		      else if(points[pi] > points[maxi]) {
		    	  maxi = pi;
		      }
		      ++pi;
		    }
		    if(mini != 0) {
		    	long tmp = points[mini];
		    	points[mini] = points[0];
		    	points[0] = tmp;
		    	
		    	if(maxi == 0)
		    		maxi = mini;
		    }

		    long minx = points[0];
		    int minx_x = x(minx);
		    int minx_y = y(minx);
		    if(maxi != pi-1) {
		      long tmp = points[pi-1];
		      points[pi-1] = points[maxi];
		      points[maxi] = tmp;
		    }
		    long maxx = points[pi-1];
		    int diffX = x(maxx)-x(minx);
		    int diffY = y(maxx)-y(minx);

		    writeUInt(pi);

		    int leftI = 1;
		    int rightI = pi-1;
		    while(leftI < rightI) {		
		    	if (rightTurn(diffX, diffY, minx_x, minx_y, points[leftI]))
		    	  ++leftI;
		    	else {
		    		long tmp = points[leftI];
		    		points[leftI] = points[--rightI];
		    		points[rightI] = tmp;
		    	}
		    }

		    // Sort points by x:
		    Arrays.sort(points, 1, leftI);
		    Arrays.sort(points, leftI, pi-1);

		    printPoint(minx);
		    for(int i = 1; i < leftI; ++i) {
		      printPoint(points[i]); 	
		    }
		    printPoint(maxx);
		    for(int i = pi-2; i >= leftI; --i) {			
		      printPoint(points[i]);				
		    }
		}

	    //System.err.println("FLUSHING 0-" + outBi);
		System.out.write(outB, 0, outBi);
		System.out.flush();
	}
	
	private static int x(long xy) {
		return (int)(xy >> 32);
	}
	
	private static int y(long xy) {
		return (int)(xy & 0xFFFFFFFF);
	}
}