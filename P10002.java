import java.io.IOException;
import java.util.Arrays;

public class P10002 {
	public static final int BUFFER_SIZE = 100000;
	public static final int COORD_ADD = Integer.MAX_VALUE/2;

	private static final long[] points = new long[102];
	private static final byte[] inB = new byte[BUFFER_SIZE];
	private static int inBi = 0;
	private static final byte[] outB = new byte[BUFFER_SIZE];
	private static int outBi = 0;

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

	private static void printDouble(long x1000) {
		if(x1000 < 0) {
			x1000 = -x1000;
			outB[outBi++] = '-';
		}

		long xTop = x1000 / 1000;
		if(xTop < 10) {
			outB[outBi++] = (byte)('0'+xTop);
		}
		else {
			long b2 = xTop;
			int size = 0;
			while(xTop > 0) {
				xTop/=10;
				++size;
			}

			xTop = b2;
			b2 = size;
			while(xTop > 0) {
				outB[outBi+size-1] = (byte)('0'+(xTop%10));
				xTop/=10;
			    --size;
			}
			outBi+=b2;			
		}
		
		outB[outBi++] = (byte)('.');

		// Handle xBottom:
		int xBottom = (int)(x1000 % 1000);
		if(xBottom < 10) {
			outB[outBi++] = '0';
			outB[outBi++] = '0';
			outB[outBi++] = (byte)('0' + xBottom);    
		}
		else if(xBottom < 100) {
			outB[outBi++] = '0';
			outB[outBi++] = (byte)('0' + (xBottom / 10));    
			outB[outBi++] = (byte)('0' + (xBottom % 10));    
		}	
		else {
			outB[outBi++] = (byte)('0' + (xBottom / 100));    
			outB[outBi++] = (byte)('0' + ((xBottom / 10) % 10));    
			outB[outBi++] = (byte)('0' + (xBottom % 10));    
		}
	}
	
	private static void printRes(long a1000, long b1000) {
		/*System.out.printf("%d %d\n", x(p)-COORD_ADD, y(p)-COORD_ADD);
		return;//*/

		checkWrite(40);

		printDouble(a1000);
		outB[outBi++] = ' ';
		printDouble(b1000);
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
		while(inB[inBi] < '-') {
			++inBi;
		}
	
		int j = inBi;
		boolean xIsNeg = (inB[j++] == '-');
		while(inB[j++] > ' ')
			;
		int xSize = j-inBi-1;

		boolean yIsNeg = (inB[j++] == '-');
		while(inB[j++] > ' ')
			;
		int ySize = j-inBi-2-xSize;
  
		int x = readLong(inBi, xIsNeg, xSize)+COORD_ADD;
		int y = readLong(inBi+xSize+1, yIsNeg, ySize)+COORD_ADD;
		if(x < 0 || y < 0)
			throw new IllegalArgumentException("CAN'T PROCESS INPUT FAST ENOUGH BECAUSE OF BROKEN CONSTRAINTS");
		
		inBi=j;
		
		return (((long)x) << 32) | (y&0x00000000ffffffffl);
	}

	private static int readUInt() throws IOException {
/*		try {
			return Integer.parseInt(new BufferedReader(new InputStreamReader(System.in)).readLine());
		} catch (IOException e) {
			e.printStackTrace();
			return 0;
		}//*/

		checkRead(6);
		while(inB[inBi] < '0') {
			++inBi;
		}

		int N = inB[inBi++]-'0';
		byte c;
		while((c = inB[inBi++]) >= '0') {
			N = 10*N + (c-'0');
		}
		return N;//*/
	}	
	
	public static void main(String[] args) throws IOException {
		System.in.read(inB, 0, BUFFER_SIZE);

		while(true) {
			final int N = readUInt();
			//System.err.println("READING " + N);		    	  
			if(N < 3) {
				System.out.write(outB, 0, outBi);
				System.out.flush();
				return;
			}
			
		    // Find points:
		    int pi = 0;
		    int mini = 0;
		    int maxi = 0;
		    for(int j = 0; j < N; ++j) {
		      long p =  readPoint();
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
		    assert pi == N;
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
		    int diffX = x(maxx)-minx_x;
		    int diffY = y(maxx)-minx_y;

		    int leftI = 1;
		    int rightI = pi-1;
		    while(leftI < rightI) {		
		    	if (rightTurn(diffX, diffY, minx_x, minx_y, points[leftI])) {
		    		++leftI;
		    	}
		    	else {
		    		long tmp = points[leftI];
		    		points[leftI] = points[--rightI];
		    		points[rightI] = tmp;
		    	}
		    }

		    // Sort points by x:
		    Arrays.sort(points, 1, leftI);
		    Arrays.sort(points, leftI, pi-1);

		    // Compute centroid:
		    long sumX = 0;
		    long sumY = 0;
		    long sumA = 0;

		    // Sum up:
		    long prev = points[leftI]; // Last point
		    long p = 0;
		    for(int i = 0; i < leftI; ++i) {
		      p = points[i];
		      sumX += (x(prev)+x(p))*(x(prev)*y(p)-x(p)*y(prev));
		      sumY += (y(prev)+y(p))*(x(prev)*y(p)-x(p)*y(prev));
		      sumA += x(prev)*y(p) - y(prev)*x(p);
		      prev = p;
		    }
/*		    System.err.println("PARTIALS:");
		    System.err.println(" SUM X:" + sumX);
		    System.err.println(" SUM Y:" + sumY);
		    System.err.println(" SUM A:" + sumA);//*/
		    p = maxx;
		    sumX += (x(prev)+x(p))*(x(prev)*y(p)-x(p)*y(prev));
		    sumY += (y(prev)+y(p))*(x(prev)*y(p)-x(p)*y(prev));
		    sumA += x(prev)*y(p) - y(prev)*x(p);
		    prev = maxx;
/*		    System.err.println("PARTIALS:");
		    System.err.println(" SUM X:" + sumX);
		    System.err.println(" SUM Y:" + sumY);
		    System.err.println(" SUM A:" + sumA);//*/
		    for(int i = pi-2; i >= leftI; --i) {
		      p = points[i];
		      sumX += (x(prev)+x(p))*(x(prev)*y(p)-x(p)*y(prev));
		      sumY += (y(prev)+y(p))*(x(prev)*y(p)-x(p)*y(prev));
		      sumA += x(prev)*y(p) - y(prev)*x(p);
		      prev = p;
		    }
/*		    
		    System.err.println("MIN  : " + x(minx) + " " + y(minx));
		    System.err.println("MAX  : " + x(maxx) + " " + y(maxx));
		    System.err.println("LEFTI: " + leftI);
		    System.err.println("SUM X: " + sumX);
		    System.err.println("SUM Y: " + sumY);
		    System.err.println("SUM A: " + sumA);//*/

		    // x:
		    sumX *= 100000;
		    sumX /= (sumA*3);
		    if(sumX > 0)
		      sumX += 50;
		    else 
		      sumX-=50;
		    sumX /= 100;

		    // y
		    sumY *= 100000;
		    sumY /= (sumA*3);
		    if(sumY > 0)
		      sumY += 50;
		    else 
		      sumY-=50;
		    sumY /= 100;
		    
		    printRes(sumX, sumY);
		}
	}
	
	private static int x(long xy) {
		return ((int)(xy >> 32))-COORD_ADD;
	}
	
	private static int y(long xy) {
		return ((int)(xy & 0xFFFFFFFF))-COORD_ADD;
	}	
}
