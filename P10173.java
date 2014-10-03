import java.awt.Color;
import java.awt.Polygon;
import java.awt.geom.GeneralPath;
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

public class P10173 {	
	private static double minAreaWalk(Point[] points) {
		// Find initial rectangle:
		int iLeft = 0;
		int iTop = iLeft;
		while(iTop + 1 < points.length && points[iTop+1].y > points[iTop].y)
			++iTop;
		int iRight = iTop;
		while(iRight + 1 < points.length && points[iRight+1].x > points[iRight].x)
			++iRight;
		int iBottom = iRight;
		while(points[(iBottom+1)%points.length].y < points[iBottom].y)
			iBottom = (iBottom+1)%points.length;
		double area = (points[iRight].x-points[iLeft].x)*(points[iTop].y-points[iBottom].y);
		
		// Walk around CH for best area:
		for(; iLeft < points.length; ++iLeft) {
			Point v = points[iLeft];
			Point w = points[(iLeft+1)%points.length];
			Point tangentV = new Point(v.x+(v.y-w.y), v.y+(w.x-v.x));
			
			// Update other points:
			double dT = points[iTop].distToLine(v, tangentV);
			double dT2;
			while((dT2 = points[(iTop+1)%points.length].distToLine(v, tangentV)) > dT) {
				dT = dT2;
				iTop = (iTop+1)%points.length;
			}
			double dR = points[iRight].distToLine(v, w);
			double dR2;
			while((dR2 = points[(iRight+1)%points.length].distToLine(v, w)) > dR) {
				dR = dR2;
				iRight = (iRight+1)%points.length;
			}
			Point tangentT = new Point(points[iTop].x+(v.y-w.y), points[iTop].y+(w.x-v.x));
			double dB = points[iBottom].distToLine(points[iTop], tangentT);
			double dB2;
			while((dB2 = points[(iBottom+1)%points.length].distToLine(points[iTop], tangentT)) > dB) {
				dB = dB2;
				iBottom = (iBottom+1)%points.length;
			}
			
			// Compute new area:
			double newArea = dR * points[iBottom].distToLine(points[iTop], tangentT);
			
			/*
			System.err.println("NEW AREA TEST: " + newArea);				
			GraphView gv = new GraphView();
			int[] xs = new int[points.length];
			int[] ys = new int[points.length];
			for(int i = 0; i < xs.length; ++i) {
				xs[i] = (int)points[i].x;
				ys[i] = (int)points[i].y;
			}
			gv.addPolygon(new Polygon(xs, ys, xs.length));
			gv.addPoint(new Point2D.Double(points[iLeft].x,points[iLeft].y), Color.BLUE);
			gv.addPoint(new Point2D.Double(points[iLeft+1].x,points[iLeft+1].y), Color.BLUE);
			gv.addPoint(new Point2D.Double(points[iTop].x,points[iTop].y), Color.RED);
			gv.addPoint(new Point2D.Double(points[iRight].x,points[iRight].y), Color.GREEN);
			gv.addPoint(new Point2D.Double(points[iBottom].x,points[iBottom].y), Color.CYAN);
			gv.addPoint(new Point2D.Double(tangentT.x,tangentT.y), Color.CYAN);
			Object monitor = new Object();
			synchronized (monitor) {
				gv.show(monitor);
				try {
					monitor.wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
					return;
				}					
			}//*/
			
			// Update area if new area is smaller:
			if(area > newArea) {
				area = newArea;	
			}
		}			
		return area;
	}
	
	private static double minAreaTurn(final Point[] points) {
		double area = Double.MAX_VALUE;
		
		// Find initial rectangle:		
		for(int i = 0; i < points.length; ++i) {
			// Rotate points:
			Point u = points[i];
			Point v = points[(i+1)%points.length];			
			Point rotator = v.sub(u);
			//System.err.println("ROTATOR: " + rotator);

			double minx = Double.MAX_VALUE;
			double miny = Double.MAX_VALUE;
			double maxx = Double.MIN_VALUE;
			double maxy = Double.MIN_VALUE;			
	/*		
			GraphView gv = new GraphView();
			GeneralPath gp = new GeneralPath(GeneralPath.WIND_NON_ZERO);//*/
			
			for(int j = 0; j < points.length; ++j) {
				Point in = points[j].sub(u);
				Point out = new Point(in.x*rotator.x+in.y*rotator.y, -in.x*rotator.y+in.y*rotator.x);
				//System.err.println(" " + in + " -> " + out);
				
				if(out.x < minx)
					minx = out.x;
				if(out.x > maxx)
					maxx = out.x;
				if(out.y < miny)
					miny = out.y;
				if(out.y > maxy)
					maxy = out.y;
				
//				gv.addPoint(new Point2D.Double(out.x, out.y), Color.RED);
/*				if(j == 0)
					gp.moveTo(out.x, out.y);
				else
					gp.lineTo(out.x, out.y);//*/
			}
/*
			gp.closePath();
			gv.addPolygon(gp);
			Object monitor = new Object();
			synchronized (monitor) {
				gv.show(monitor);
				try {
					monitor.wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}					
			}//*/			
			
			double newArea = (maxx-minx)*(maxy-miny)/rotator.lengthSquared();
			
			if(newArea < area)
				area = newArea;
		}			
		return area;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while(true) {
			// Read input:
			int numPoints = Integer.parseInt(br.readLine());
			if(numPoints == 0)
				return;
			if(numPoints <= 2) {
				br.readLine();
				if(numPoints == 2)
					br.readLine();
				System.out.println("0.0000");
				continue;
			}
			
			Point[] points = new Point[numPoints];
			
			for(int i = 0; i < numPoints; ++i) {
				String[] parts = br.readLine().split("\\s+");
				double x = Double.parseDouble(parts[0]);
				double y = Double.parseDouble(parts[1]);				
				points[i] = new Point(x,y);
			}
			
			// Construct CH:
			points = new ConvexHull(points).points;			
			double area = minAreaTurn(points);
	/*
			System.err.println("CH with " + points.length + " points:");
			System.err.println(" Area turn: " + area);
			System.err.println(" Area walk: " + minAreaWalk(points));
//*/			
			System.out.printf("%.4f\n", area);
		}
	}
	
	static class Point {
		double x;
		double y;
		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}
		
		public double distSquared(Point p) {
			return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
		}
		
		public double dist(Point p) {
			return Math.sqrt(distSquared(p));
		}
		
		public Point flipY() {
			return new Point(x, -y);
		}
		
		public Point sub(Point b) {
			return new Point(x-b.x,y-b.y);
		}
		
		public double length() {
			return Math.sqrt(lengthSquared());
		}
		
		public double lengthSquared() {
			return x*x+y*y;
		}
		
		public Point normalize() {
			double len = length();
			return new Point(x/len,y/len);
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

		public double distToLine(Point A, Point B) {
			double normalLength = Math.sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y));
			return Math.abs((x-A.x)*(B.y-A.y)-(y-A.y)*(B.x-A.x))/normalLength;		
		}
		
		public String toString() {
			return x + "," + y;
		}
	}

	/*
	 * Convex hull represented by a list of points in clockwise order.
	 */
	static class ConvexHull {
		Point[] points;
		
		public ConvexHull(Point[] scatteredPoints) {
			// Sort input by x:
			Arrays.sort(scatteredPoints, new Comparator<Point>() {
				public int compare(Point a, Point b) {
					if(a.x == b.x)
						return (int)Math.signum(a.y-b.y);
					return (int)Math.signum(a.x-b.x);
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

			upperPoints = upperHull(leftMost, rightMost, upperPoints);
			lowerPoints = upperHull(leftMost.flipY(), rightMost.flipY(), lowerPoints);

			//Make points of hull:
			points = new Point[upperPoints.size() + lowerPoints.size()];
			int i = 0;
			for(Point p : upperPoints) {
				points[i++] = p;
			}		
			points[i] = rightMost;
			i = points.length;
			for(Point p : lowerPoints) {
				i--;
				if(i != points.length-1)
					points[i+1] = p.flipY();
			}
		}
		
		private List<Point> upperHull(Point left, Point right, List<Point> between) {
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
			return out;
		}
	}	
}
