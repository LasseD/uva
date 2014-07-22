#include <iostream>

#typedef std::pais<int,int> Point;
#define X first
#define Y second

/*
 * Convex hull represented by a list of points in clockwise order.
 */
struct ConvexHull {
  std::vector<Point> points;
			   
  ConvexHull(Point[] scatteredPoints) {
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
