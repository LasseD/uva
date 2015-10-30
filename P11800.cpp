#include <iostream>

typedef std::pair<int,int> Point;
typedef std::pair<Point,Point> Line;
#define X first
#define Y second
#define P1 first
#define P2 second

#define SQUARE 1
#define RECTANGLE 2
#define RHOMBUS 3
#define PARALLELOGRAM 4
#define TRAPEZIUM 5
#define ORDINARY_QUADRILATERAL 6

void print(int type, int caseNumber) {
  std::cout << "Case " << caseNumber << ": ";
  switch(type) {
  case SQUARE:
    std::cout << "Square" << std::endl;
    break;
  case RECTANGLE:
    std::cout << "Rectangle" << std::endl;
    break;
  case RHOMBUS:
    std::cout << "Rhombus" << std::endl;      
    break;
  case PARALLELOGRAM:
    std::cout << "Parallelogram" << std::endl;
    break;
  case TRAPEZIUM:
    std::cout << "Trapezium" << std::endl;      
    break;
  default:
    std::cout << "Ordinary Quadrilateral" << std::endl;      
    break;
  }
}

bool rightTurn(int diffX, int diffY, int x1, int y1, const Point &p) {
  return diffX*(p.Y-y1) < diffY*(p.X-x1);
}
bool rightTurn(const Point &p1, const Point &p2, const Point &p) {
  return rightTurn(p2.X-p1.X, p2.Y-p1.Y, p2.X, p2.Y, p);
}
bool colinear(int diffX, int diffY, int x1, int y1, const Point &p) {
  return diffX*(p.Y-y1) == diffY*(p.X-x1);
}
bool colinear(const Point &p1, const Point &p2, const Point &p) {
  return colinear(p2.X-p1.X, p2.Y-p1.Y, p2.X, p2.Y, p);
}
bool cross(const Line &a, const Line &b) {
  if(colinear(a.X, a.Y, b.X) || colinear(a.X, a.Y, b.Y)) {
    return rightTurn(b.X, b.Y, a.X) != rightTurn(b.X, b.Y, a.Y);
  }
  if(colinear(b.X,b.Y,a.X) || colinear(b.X,b.Y,a.Y)) {
    return rightTurn(a.X, a.Y, b.X) != rightTurn(a.X, a.Y, b.Y);
  }

  return rightTurn(a.X, a.Y, b.X) != rightTurn(a.X, a.Y, b.Y) && 
         rightTurn(b.X, b.Y, a.X) != rightTurn(b.X, b.Y, a.Y);
}
int norm(const Line &l) {
  return (l.P1.X-l.P2.X)*(l.P1.X-l.P2.X) + 
         (l.P1.Y-l.P2.Y)*(l.P1.Y-l.P2.Y);
}
bool parallel(const Line &l1, const Line &l2) {
  Point v1(l1.P2.X-l1.P1.X, l1.P2.Y-l1.P1.Y);
  Point v2(l2.P2.X-l2.P1.X, l2.P2.Y-l2.P1.Y);
  return colinear(Point(0,0), v1, v2);
}

int analyze(Point *pts) {
  Line lines[4];
  int norms[4];
  for(int j = 0; j < 4; ++j) {
    lines[j] = Line(pts[j], pts[(j+1)%4]);
    norms[j] = norm(lines[j]);
  }

  if(cross(lines[0], lines[2]) || cross(lines[1], lines[3])) {
    return ORDINARY_QUADRILATERAL;
  }

  bool allAnglesAre90 = true;
  bool noAngleIs90 = true;
  for(int j = 0; j < 4; ++j) {
    int n1 = norms[j];
    int n2 = norms[(j+3)%4];
    int nCross = norm(Line(pts[(j+1)%4], pts[(j+3)%4]));
    if(n1 + n2 == nCross)
      noAngleIs90 = false;
    else
      allAnglesAre90 = false;
  }
  bool sameNormPair1 = (norms[0] == norms[2]);
  bool sameNormPair2 = (norms[1] == norms[3]);
  bool sameNorms = (sameNormPair1 && sameNormPair2 && norms[0] == norms[1]);

  bool parallel1 = parallel(lines[0], lines[2]);
  bool parallel2 = parallel(lines[1], lines[3]);

  if(sameNorms && allAnglesAre90)
    return SQUARE;
  else if(sameNormPair1 && sameNormPair2 && allAnglesAre90)
    return RECTANGLE;
  else if(sameNorms && noAngleIs90)
    return RHOMBUS;
  else if(sameNormPair1 && sameNormPair2 && noAngleIs90)
    return PARALLELOGRAM;
  else if(parallel1 != parallel2)
    return TRAPEZIUM;
  else
    return ORDINARY_QUADRILATERAL;
}

struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode *nodes;

  PermutationHandler() : nodes(NULL) {}

  void reset() {
    if(nodes != NULL)
      delete[] nodes;
    nodes = new PermutationNode[5];

    for(unsigned int i = 0; i < 4; ++i) {
      nodes[i+1].val = i;
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[4].next = NULL;
  }

  PermutationNode* root() {
    return &(nodes[0]);
  }
};

void run(Point *pts, const unsigned int i, PermutationHandler &ph, Point *perm, int &best) {
  if(i == 3) {
    int perm3 = ph.root()->next->val;
    perm[3] = pts[perm3];
    
    int trial = analyze(perm);
    if(trial < best)
      best = trial;
    
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    perm[i] = pts[n->val];
    run(pts, i+1, ph, perm, best);

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int main() {
  int T;
  PermutationHandler ph;
  std::cin >> T;
  for(int k = 0; k < T; ++k) {
    Point pts[4];
    for(int j = 0; j < 4; ++j) {
      std::cin >> pts[j].X >> pts[j].Y;
    }
    ph.reset();
    Point perm[4];
    int best = 999;
    run(pts, 0, ph, perm, best);
    print(best, k+1);
  }
}
