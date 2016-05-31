#include <iostream>
#include <stdio.h>
#include <queue>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define BLOCK -2
#define FREE -1

struct Vector {
  int x, y, z;
  Vector() {}
  Vector(int x, int y, int z) : x(x), y(y), z(z) {}
  Vector(const Vector &v) : x(v.x), y(v.y), z(v.z) {}
  bool operator==(const Vector &v) const {
    return x==v.x && y==v.y && z==v.z;
  }
};

int idx(const Vector &size, const Vector &pos) {
  return size.z*size.y*pos.x + size.z*pos.y + pos.z;
}

int BFS(const Vector &size, const Vector &s, const Vector &t, int *D) {
  std::queue<Vector> q;
  q.push(s);
  while(!q.empty()) {
    Vector u = q.front();
    q.pop();
    int time = D[idx(size,u)] + 1;
    for(int xx = -1; xx <= 1; ++xx) {
      for(int yy = -1; yy <= 1; ++yy) {
	for(int zz = -1; zz <= 1; ++zz) {
	  if(xx==0&&yy==0&&zz==0)
	    continue;
	  if(xx*yy != 0 || xx*zz != 0 || yy*zz != 0)
	    continue; // hackedihack: No diagonals :)
	  int x2 = xx+u.x;
	  int y2 = yy+u.y;
	  int z2 = zz+u.z;
	  if(x2 < 0 || x2 >= size.x || y2 < 0 || y2 >= size.y || z2 < 0 || z2 >= size.z)
	    continue;
	  Vector v(x2,y2,z2);
	  if(v == t)
	    return time;
	  int i = idx(size, v);
	  if(D[i] != FREE)
	    continue;
	  D[i] = time;
	  q.push(v);
	} // z
      } // y
    } // x
  } // empty

  return -1;
}

int main() {
  Vector size, s, t;
  int L, R, C, D[30*30*30];
  char line[39];

  while(true) {
    // Scan input:
    std::cin >> L >> R >> C;
    if(L+R+C == 0)
      return 0;
    size.z = L;
    size.y = R;
    size.x = C;

    for(int z = 0; z < L; ++z) {
      for(int y = 0; y < R; ++y) {
	std::cin >> line;
	for(int x = 0; x < C; ++x) {
	  Vector p(x,y,z);
	  int i = idx(size, p);
	  if(line[x] == '.')
	    D[i] = FREE;
	  else if(line[x] == '#')
	    D[i] = BLOCK;
	  else if(line[x] == 'S') {
	    D[i] = 0;
	    s = p;
	  }
	  else {
	    D[i] = FREE;
	    t = p;
	  }
	}
      }
    }

    int time = BFS(size, s, t, D);
    if(time < 0)
      std::cout << "Trapped!" << std::endl;
    else
      std::cout << "Escaped in " << time << " minute(s)." << std::endl;
  }  
}
