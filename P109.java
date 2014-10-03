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

public class P109 {
	public static void main(String[] args) throws IOException {
		// Read kingdoms:
		List<Kingdom> kingdoms = new LinkedList<Kingdom>();
//		GraphView gv = new GraphView();

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line;
		while((line = br.readLine()) != null) {
			final int N = Integer.parseInt(line);
			if(N == -1)
				break;
			// Build kingdom of size N:
			Point[] buildings = new Point[N];
			for(int i = 0; i < N; ++i) {
				String[] parts = br.readLine().split("\\s+");
				buildings[i] = new Point(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
	//			gv.addPoint(new Point2D.Double(buildings[i].x, buildings[i].y), Color.GREEN);
			}
			kingdoms.add(new Kingdom(buildings));
		}

		{
			double sizeSum = 0;
			for(Kingdom k : kingdoms) {
	//			System.err.println(" Wall with " + k.wall.points.length + " points with area "+ k.getArea());
				sizeSum += k.getArea();
		//		gv.addPolygon(k.getPolygon());
			}
		//	System.err.println("Total kingdom area: " + sizeSum);
		}
//*/		
		// Read missiles:
		double unlitArea = 0;
		while((line = br.readLine()) != null) {
			String[] parts = line.split("\\s+");
			if(parts.length < 2)
				break;
			Point missile = new Point(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
			Kingdom ruined = null;
			for(Kingdom k : kingdoms) {
				if(k.isHitByMissile(missile)) {
					//System.err.println("HIT! " + missile + " -> " + k);
					ruined = k;
					break;
				}
			}
			if(ruined != null) {
				//gv.addPoint(new Point2D.Double(missile.x, missile.y), Color.RED);
				unlitArea += ruined.getArea();
				kingdoms.remove(ruined);
			} 
			else {
			//	System.err.println("MISS! " + missile);
				//gv.addPoint(new Point2D.Double(missile.x, missile.y), Color.BLUE);
			}
		}
		System.out.printf("%.2f\n", unlitArea);
//		gv.show();
	}	
}

class Kingdom {
	ConvexHull wall;
	
	public Kingdom(Point[] buildings) {
		wall = new ConvexHull(buildings);
	}
	
	public boolean isHitByMissile(Point missile) {		
		return wall.contains(missile);
	}
	
	public double getArea() {
		return wall.getArea();
	}
	
	public String toString() {
		return "Kingdom with wall of " + wall.points.length + " points and area " + getArea();
	}
	
	public Polygon getPolygon() {
		int[] xs = new int[wall.points.length];
		int[] ys = new int[wall.points.length];
		for(int i = 0; i < xs.length; ++i) {
			xs[i] = wall.points[i].x;
			ys[i] = wall.points[i].y;
		}
		return new Polygon(xs, ys, xs.length);
	}
}

class Point {
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

/*
 * Convex hull represented by a list of points in clockwise order.
 */
class ConvexHull {
	Point[] points;
	
	public ConvexHull(Point[] scatteredPoints) {
//		System.err.println("Initiating construction of convex hull with " + scatteredPoints.length + " points");
		// Sort input by x:
		Arrays.sort(scatteredPoints, new Comparator<Point>() {
			public int compare(Point a, Point b) {
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
//		new AsciiPrinter(Arrays.asList(scatteredPoints), upperPoints, flipY(lowerPoints)).print();
		
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
//		System.err.println("CH:" + Arrays.asList(points));
		for(Point p : lowerPoints) {
			i--;
			if(i != points.length-1)
				points[i+1] = p.flipY();
		}

//		System.err.println("CH:" + Arrays.asList(points));
//		new AsciiPrinter(Arrays.asList(scatteredPoints), Arrays.asList(points)).print();
	}
	
	private List<Point> flipY(List<Point> l) {
		LinkedList<Point> res = new LinkedList<Point>();
		for(Point p : l) {
			res.add(p.flipY());
		}
		return res;
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
	
	public boolean contains(Point p) {
		Point last = points[points.length-1];
		for(Point point : points) {
			if(point.equals(p))
				return true;
		}
		for(Point point : points) {
			if(!Point.rightTurn(last, point, p))
				return false;
			last = point;
		}
		return true;
	}
	
	public double getArea() {
		int res = 0;
		Point prev = points[points.length-1];
		for(Point p : points) {
			res += prev.x*p.y- prev.y*p.x;
			prev = p;
		}
		return res*-0.5;
	}
}

class AsciiPrinter {
	private List<Point> [] data;
	
	public AsciiPrinter(List<Point> ...lists) {
		data = lists;
	}
	
	public void print() {
		// Find bounding box:
		StringBuilder sb = new StringBuilder();
		int minx = Integer.MAX_VALUE;
		int miny = Integer.MAX_VALUE;
		int maxx = Integer.MIN_VALUE;
		int maxy = Integer.MIN_VALUE;
		for(List<Point> list : data) {
			for(Point p : list) {
				minx = Math.min(minx, p.x);
				maxx = Math.max(maxx, p.x);
				miny = Math.min(miny, p.y);
				maxy = Math.max(maxy, p.y);
			}
		}
		if(maxx-minx > 80)
			return;
		// Construct lines:
		int pointsPrLine = maxx-minx+1;
		int lines = maxy-miny+1;
		byte[] screenBuffer = new byte[lines*pointsPrLine];
		byte id = 1;
		for(List<Point> list : data) {
			for(Point p : list) {
				screenBuffer[pointsPrLine*(p.y-miny)+(p.x-minx)] = id;
				if(data.length == 1)
					++id;
			}
			++id;
		}
		// Write lines:
		for(int y = maxy; y >= miny; --y) {
			for(int x = minx; x <= maxx; ++x) {
				id = screenBuffer[pointsPrLine*(y-miny)+(x-minx)];
				if(id == 0)
					sb.append(' ');
				else
					sb.append((char)('A' + (id - 1)));
			}
			sb.append('\n');
		}
		System.err.print(sb);
	}
}