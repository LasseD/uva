import java.awt.Color;
import java.awt.Polygon;
import java.awt.geom.Point2D;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

//import viewers.GraphView;

public class P681 {
	public static void main(String[] args) throws IOException {
//		GraphView gv = new GraphView();

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		final int K = Integer.parseInt(br.readLine());
		System.out.println(K);

		for(int IGNORE = 0; IGNORE < K; ++IGNORE) {
			if(IGNORE > 0) {
				br.readLine(); // -1 = separator				
				System.out.println(-1);
			}
			final int N = Integer.parseInt(br.readLine());

			// Read points:
			Point[] points = new Point[N];
			for(int i = 0; i < N; ++i) {
				String[] parts = br.readLine().split("\\s+");
				points[i] = new Point(Integer.parseInt(parts[1]), Integer.parseInt(parts[0]));
	//			gv.addPoint(new Point2D.Double(buildings[i].x, buildings[i].y), Color.GREEN);				
			}
			
			ConvexHull ch = new ConvexHull(points);
			System.out.println(ch.points.length+1);
			for(Point p : ch.points) {
				System.out.println(p);				
			}
			System.out.println(ch.points[0]);				
		}
//		gv.show();
	}	

	static class Point {
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
			return y + " " + x;
		}
	}

	/*
	 * Convex hull represented by a list of points in clockwise order.
	 */
	static class ConvexHull {
		Point[] points;
		
		public ConvexHull(Point[] scatteredPoints) {
//			System.err.println("Initiating construction of convex hull with " + scatteredPoints.length + " points");
			// Sort input by x:
			Arrays.sort(scatteredPoints, new Comparator<Point>() {
				public int compare(Point a, Point b) {
					if(a.x == b.x)
						return a.y-b.y;
					return a.x-b.x;
				}
			});
			// Find left and rightmost points:
			Point leftMost = scatteredPoints[0];
			Point rightMost = scatteredPoints[scatteredPoints.length-1];

			//Split points in upper and lower:
			List<Point> upperPoints = new LinkedList<Point>();
			List<Point> lowerPoints = new LinkedList<Point>();
			for(int i = 1; i < scatteredPoints.length-1; ++i) {			
				Point p = scatteredPoints[i];
				if(Point.colinear(leftMost, rightMost, p))
					continue;
				if(Point.leftTurn(leftMost, rightMost, p))
					upperPoints.add(p);
				else
					lowerPoints.add(p.flipY());
			}
//			new AsciiPrinter(Arrays.asList(scatteredPoints), upperPoints, flipY(lowerPoints)).print();
			
			//Construct upper hull:
			upperPoints = upperHull(leftMost, rightMost, upperPoints);
			
			//Construct lower hull:
			lowerPoints = upperHull(leftMost.flipY(), rightMost.flipY(), lowerPoints);
	/*
			System.err.println("Points on hulls:");
			System.err.println(" Upper hull: " + upperPoints);
			System.err.println(" Lower hull: " + lowerPoints);
			new AsciiPrinter(Arrays.asList(scatteredPoints), upperPoints, flipY(lowerPoints)).print();

			assert upperPoints.get(0).equals(lowerPoints.get(0).flipY());
	*/		
			//Make points of hull:
			points = new Point[upperPoints.size() + lowerPoints.size()];
			int i = 0;
			for(Point p : upperPoints) {
				points[i++] = p;
			}		
			points[i] = rightMost;
			i = points.length;
//			System.err.println("CH:" + Arrays.asList(points));
			for(Point p : lowerPoints) {
				i--;
				if(i != points.length-1)
					points[i+1] = p.flipY();
			}
		}
		
		private List<Point> upperHull(Point left, Point right, List<Point> between) {
			//System.err.println("Constructing CH of " + left + "->" + between + "->" + right);
			Stack<Point> out = new Stack<Point>();
			between.add(right);
			
			out.add(left);
			Point lastPeek = right;
			for(Point p : between) {
				if(p.x == lastPeek.x) {
					if(p.y < lastPeek.y) {
						continue;
					}
					else {
						lastPeek = out.pop();					
					}
				}

				//System.err.println(" " + out + "->" + lastPeek);
				while(!out.isEmpty() && !Point.rightTurn(out.peek(), lastPeek, p)) {
					lastPeek = out.pop();
				}
				out.push(lastPeek);
				lastPeek = p;
			}
			// Fix rightmost point as it should be handled differently:
			out.push(lastPeek);
			if(out.peek() == right) {
				out.pop();
			}
			
			//System.err.println(" " + out + "->" + lastPeek);
			return out;
		}
	}
}