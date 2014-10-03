import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class P10078 {
	private static class Point {
		int x;
		int y;
		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}
		
		public Point flipY() {
			return new Point(x, -y);
		}
		
		public static boolean leftTurn(Point lineStart, Point lineEnd, Point p) {
			return (lineEnd.x-lineStart.x)*(p.y-lineStart.y) - (lineEnd.y-lineStart.y)*(p.x-lineStart.x) > 0;
		}
		
		public static boolean rightTurn(Point lineStart, Point lineEnd, Point p) {
			return (lineEnd.x-lineStart.x)*(p.y-lineStart.y) - (lineEnd.y-lineStart.y)*(p.x-lineStart.x) < 0;
		}
		
		public static boolean colinear(Point lineStart, Point lineEnd, Point p) {
			return (lineEnd.x-lineStart.x)*(p.y-lineStart.y) - (lineEnd.y-lineStart.y)*(p.x-lineStart.x) == 0;
		}
		
		public boolean equals(Point other) {
			return x == other.x && y == other.y;
		}
		
		public String toString() {
			return "(" + x + "," + y + ")";
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line;
		while((line = br.readLine()) != null) {
			int N = Integer.parseInt(line.trim());
			if(N == 0) 
				return;
			Point first, second;
			Point prevprev = null;
			String[] parts = br.readLine().split("\\s+");
			prevprev = new Point(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
			first = prevprev;

			Point prev = null;
			parts = br.readLine().split("\\s+");
			prev = new Point(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
			second = prev;
						
			Point p = null;
			parts = br.readLine().split("\\s+");
			p = new Point(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
			boolean goingRight = Point.rightTurn(prevprev, prev, p);
			
			boolean ok = false;
			for(int i = 3; i < N; ++i) {
				prevprev = prev;
				prev = p;
				parts = br.readLine().split("\\s+");
				if(ok)
					continue;
				p = new Point(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));

				if(goingRight != Point.rightTurn(prevprev, prev, p)) {
					System.out.println("Yes");
					ok = true;
				}
			}			
			if(ok)
				continue;
			if(goingRight != Point.rightTurn(prev, p, first)) {
				System.out.println("Yes");
				continue;
			}
			if(goingRight != Point.rightTurn(p, first, second)) {
				System.out.println("Yes");
				continue;
			}
			System.out.println("No");			
		}
	}
}
