#include <stdio.h>
#include <iostream>

/*
m x n grid, lower left is 0,0
- bumpers on grid points
- walls surrounding
- Ball: Initial position (x,y), direction (up,down,left,right), lifetime.
- speed: 1 grid cell / time.
- rebound clockwise.
- lifetime: move + bumper cost + wall cost
- dirs: 0 ->
        1 ^ 
	2 <-
	3 v
input:
3 <= m n <= 50
wall cost
|bumpers| = p
...
x y value cost : bumper
...
x y dir lifetime>0 : ball
...

.....
..O..
.O...
.....

 */
void updatePos(int &x, int &y, const int dir) {
  switch(dir) {
  case 0:
    ++x;
    return;
  case 1:
    ++y;
    return;
  case 2:
    --x;
    return;
  case 3:
    --y;
    return;
  }
}

int main() {
  // Read input:
  int m, n, wall_cost, p;

  bool bumpers[50*50] = {0};
  int values[50*50] = {0};
  int costs[50*50] = {0};
  
  std::cin >> m;
  --m;
  std::cin >> n;
  --n;
  std::cin >> wall_cost;
  std::cin >> p;
  for(int i = 0; i < p; ++i) {
    int x, y, value, cost;
    std::cin >> x;
    --x;
    std::cin >> y;
    --y;
    std::cin >> value;
    std::cin >> cost;
    values[y*m+x] = value;
    costs[y*m+x] = cost;    
    bumpers[y*m+x] = 1;
  }
  //std::cerr << "GAME MxN " << m << " x " <<n<<" with  "<<p<<" bumpers"<<std::endl;
  
  int score_total = 0;
  // Handle balls:
  while(!std::cin.eof()) {
    int score = 0;
    int x, y, dir, life;
    std::cin >> x;
    --x;
    if(std::cin.eof())
      break;
    std::cin >> y;
    --y;
    std::cin >> dir;
    std::cin >> life;
    //std::cerr << "Ball start at " << x << "," <<y<<" "<<dir<<" "<<life<<std::endl;

    while(life > 1) {
      int oldx = x;
      int oldy = y;
      updatePos(x, y, dir);
      //      std::cerr << "Moves to " << x << "," <<y<<std::endl;      
      // move:
      --life;
      // handle bumper:
      bool hitSomething = false;
      if(dir == 0 && x == m || 
	 dir == 1 && y == n || 
	 dir == 2 && x == 0 || 
	 dir == 3 && y == 0) {
	dir = (dir+3)%4; 
	life -= wall_cost;
	//	std::cerr << "Bumps wall => life " << life <<std::endl;      
	hitSomething = true;
      }
      else if(bumpers[y*m+x] == 1) {
	dir = (dir+3)%4; 
	score += values[y*m+x];
	life -= costs[y*m+x];
	//	std::cerr << "Bumps bumper " << values[y*m+x] << ", " << costs[y*m+x] << " => life " << life <<std::endl;      
	hitSomething = true;
      }
      if(hitSomething) {
	x = oldx;
	y = oldy;
	// just update pos.
      }

      //      std::cerr << " => " << x << "," << y << ", dir " << dir << ", life " <<life<<", score " << score <<std::endl;            
    }
    std::cout << score << std::endl;
    score_total += score;
    // Handle ball:
  }
  std::cout << score_total << std::endl;
  return 0;
}
