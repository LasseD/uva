// See en.wikipedia.org/wiki/Edit_distance

typedef pair<PC,PI> CMD; // (cmd, letter), (change pos, len after change)

int main() {
  int d[21][21];
  
  CMD cmd[21][21];
  while(true) {
    GS(a); if(a == "#") return 0; GS(b);
    //cerr << a << " -> " << b << endl;

    // Init matrices:
    d[0][0] = 0;
    cmd[0][0] = CMD(PC('N','x'), PI(-1,0));
    FORUI(a.size()) {
      d[i+1][0] = i+1;
      cmd[i+1][0] = CMD(PC('D',a[i]), PI(1,0));
    }
    FORUJ(b.size()) {
      d[0][j+1] = j+1;
      cmd[0][j+1] = CMD(PC('I',b[j]), PI(j+1,j+1));
    }

    // Fill matrix:
    FORUI(a.size()) {
      FORUJ(b.size()) {
	if(a[i] == b[j]) {
	  d[i+1][j+1] = d[i][j];
	  int len = cmd[i][j].YY.YY + 1;
	  cmd[i+1][j+1] = CMD(PC('N','x'),PI(-1,len)); // No operation needed.
	  //cerr << " (" << d[i][j] << ")Nx, len " << len;
	}
	else {
	  // Try insertion:
	  int bestCost = d[i+1][j]+1;
	  int len =    cmd[i+1][j].YY.YY + 1;
	  CMD c(PC('I',b[j]), PI(j+1,len));

	  // Try deletion:
	  if(d[i][j+1]+1 < bestCost) {
	    bestCost = d[i][j+1]+1;
	    len =    cmd[i][j+1].YY.YY + 0;
	    c = CMD(PC('D',a[i]), PI(len+1,len));
	  }

	  // Try sub:
	  if(d[i][j]+1 < bestCost) {
	    bestCost = d[i][j]+1;
	    len =    cmd[i][j].YY.YY + 1;
	    c = CMD(PC('C',b[j]), PI(j+1,len));
	  }

	  //cerr << " (" << bestCost << ")" << c.XX.XX << c.XX.YY <<", pos "<< c.YY.XX <<", len "<< len;
	  d[i+1][j+1] = bestCost;
	  cmd[i+1][j+1] = c;
	}
	//cerr << endl;
      }
    }

    stack<CMD> s;
    PI pos((int)a.size(), (int)b.size());
    //cerr << "Walk: ";
    while(!(pos.XX == 0 && pos.YY == 0)) {
      //cerr << "(" << pos.XX << "," << pos.YY << ")";
      CMD c = cmd[pos.XX][pos.YY];
      switch(c.XX.XX) {
      case 'D':
	pos.XX--;
	break;
      case 'I':
	pos.YY--;
	break;
      case 'C':
      case 'N':
	pos.XX--;
	pos.YY--;
	break;
      default:
	die();
      }
      s.push(c);
    }    
    // Output:
    while(!s.empty()) {
      CMD c = s.top(); s.pop();
      if(c.XX.XX != 'N')
	printf("%c%c%.2i", c.XX.XX, c.XX.YY, c.YY.XX);
    }
    printf("E\n");
  }
}
