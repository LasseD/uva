#define North 0
#define NorthEast 1
#define East 2
#define SouthEast 3

int main() {
  string line;
  for(int cas = 0; true; ++cas) {
    cin >> line;
    if(line[0] == 'E')
      return 0;
    long pos[4] = {0,0,0,0}; // N, NE, E, SE
    long x = 0;
    char cmd[2] = {'x','x'};
    FORUI(line.size()) {
      char c = line[i];
      if(c == '.' || c == ',') {
	if(cmd[0] == 'E') {
	  pos[East] += x;
	}
	else if(cmd[0] == 'W') {
	  pos[East] -= x;
	}
	else if(cmd[0] == 'N') {
	  if(cmd[1] == 'E') {
	    pos[NorthEast] += x;
	  }
	  else if(cmd[1] == 'W') {
	    pos[SouthEast] -= x;
	  }
	  else
	    pos[North] += x;
	}
	else {// if(cmd[0] == 'S') {
	  if(cmd[1] == 'E') {
	    pos[SouthEast] += x;
	  }
	  else if(cmd[1] == 'W') {
	    pos[NorthEast] -= x;
	  }
	  else
	    pos[North] -= x;
	}

	cmd[0] = cmd[1] = 'x';
	x = 0;
	if(c == '.')
	  break;	
      }
      else if(isdigit(c)) {
	x = 10*x + c-'0';
	//cerr << "x=" << x << endl;
      }
      else {
	if(cmd[0] == 'x')
	  cmd[0] = c;
	else
	  cmd[1] = c;
	//cerr << "cmd=" << cmd[0] << cmd[1] << endl;
      }
    } // FORI
    printf("Map #%d\n", cas+1);
    double dx = pos[East] + (pos[NorthEast]+pos[SouthEast])/sqrt(2);
    double dy = pos[North] + (pos[NorthEast]-pos[SouthEast])/sqrt(2);
    printf("The treasure is located at (%.3lf,%.3lf).\n", dx, dy);
    printf("The distance to the treasure is %.3lf.\n\n", sqrt(dx*dx+dy*dy)); 
  } // FOR LINE
}
