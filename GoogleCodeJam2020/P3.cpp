
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define GET(i,j) grid[(i)*C + (j)]

struct S {
  int level, dist[4];
  bool addedInRound;
};

int main() {
  FORCAS {
    GI(R); GI(C);
    S* grid = new S[R*C];
    int* killList = new int[R*C];
    PI* activeList = new PI[R*C];
    PI* backupList = new PI[R*C];
    int activeListSize = 0;

    long pointsPerRound = 0;
    FORI(R) {
      FORJ(C) {
        activeList[activeListSize++] = PI(i,j);
        S * const s = &GET(i,j);
        FORK(4) {
          s->dist[k] = 1; // dist to nearest neighbour
        }
        cin >> s->level;
        pointsPerRound += s->level;
        s->addedInRound = false;

        if(i == 0) {
          s->dist[UP] = -1;
        }
        if(i == R-1) {
          s->dist[DOWN] = -1;
        }
        if(j == 0) {
          s->dist[LEFT] = -1;
        }
        if(j == C-1) {
          s->dist[RIGHT] = -1;
        }
      } // FORJ(C)
    } // FORI(R)

    long ret = 0;

    int elim = 1;
    while(elim > 0) {
      elim = 0;
      // Run round:
      /*cerr << "ROUND" << endl;
      FORI(R) {
        FORJ(C) {
          S *s = &GET(i,j);
          cerr << s->level << ' ';// << '/' << s->dist[0] << '/' << s->dist[1] << '/' << s->dist[2] << '/' << s->dist[3] << ' ';
        }
        cerr << endl;
      }//*/
      int killListSize = 0;
      ret += pointsPerRound;

      FORK(activeListSize) {
        int i = activeList[k].XX, j = activeList[k].YY;
        S const * const s = &GET(i,j);
        //cerr << "Active (" << i << "," << j << ") of level " << s->level << endl;

        if(s->level == 0) {
          continue;
        }

        int sumLevel = 0; // Neighbour levels
        int neighbours = 0;
        int r = s->dist[RIGHT];
        int l = s->dist[LEFT];
        int u = s->dist[UP];
        int d = s->dist[DOWN];

        // UP:
        if(u != -1) { // Has a neighbour up:
          sumLevel += GET(i-u,j).level;
          neighbours++;
        }
        
        // DOWN:
        if(d != -1) {
          sumLevel += GET(i+d, j).level;
          neighbours++;
        }
        
        // LEFT:
        if(l != -1) {
          sumLevel += GET(i, j-l).level;
          neighbours++;
        }
        
        // RIGHT:
        if(r != -1) {
          sumLevel += GET(i, j+r).level;
          neighbours++;
        }
        
        // Kill s:
        bool kill = (neighbours * s->level) < sumLevel;
        if(kill) {
          killList[killListSize++] = k;
          elim++;
        }
      } // FORK activeListSize

      int backupListSize = 0;
      FORK(killListSize) {
        int idx = killList[k];
        PI * const p = &activeList[idx];
        int i = p->XX, j = p->YY;
        S * const s = &GET(i,j);
        pointsPerRound -= s->level;
        //cerr << " KILL " << i << " x " << j << " of level " << s->level << endl; 
        s->level = 0;

        // Connect right neighbour to left:
        int r = s->dist[RIGHT];
        int l = s->dist[LEFT];
        int u = s->dist[UP];
        int d = s->dist[DOWN];
        if(r != -1) {
          S * const t = &GET(i, j+r);
          if(l == -1) {
            t->dist[LEFT] = -1;
          }
          else {
            t->dist[LEFT] += l;
          }
          if(!t->addedInRound) {
            t->addedInRound = true;
            backupList[backupListSize++] = PI(i, j+r);
            //cerr << backupListSize << " Add RIGHT " << i << "," << (j+r) << " -> " << backupList[backupListSize-1].XX << "," << backupList[backupListSize-1].YY << endl;
          }
        }
        if(l != -1) {
          S * const t = &GET(i, j-l);
          if(r == -1) {
            t->dist[RIGHT] = -1;
          }
          else {
            t->dist[RIGHT] += r;
          }
          if(!t->addedInRound) {
            t->addedInRound = true;
            backupList[backupListSize++] = PI(i, j-l);
            //cerr << backupListSize << " Add LEFT " << i << "," << (j-l) << endl;
          }
        }

        if(u != -1) {
          S * const t = &GET(i-u, j);
          if(d == -1) {
            t->dist[DOWN] = -1;
          }
          else {
            t->dist[DOWN] += d;
          }
          if(!t->addedInRound) {
            t->addedInRound = true;
            backupList[backupListSize++] = PI(i - u, j);
            //cerr << backupListSize << " Add UP " << (i-u) << "," << (j) << endl;
          }
        }
        if(d != -1) {
          S * const t = &GET(i+d, j);
          if(u == -1) {
            t->dist[UP] = -1;
          }
          else {
            t->dist[UP] += u;
          }
          if(!t->addedInRound) {
            t->addedInRound = true;
            backupList[backupListSize++] = PI(i + d, j);
            //cerr << backupListSize << " Add DOWN " << (i+d) << "," << (j) << endl;
          }
        }
      } // FORK killListSize

      FORK(backupListSize) {
        PI * const p = &backupList[k];
        //cerr << (k+1) << " UNADD " << p->XX << "," << p->YY << " -> " << GET(p->XX,p->YY).level << endl;
        //assert(p->XX >= 0);
        //assert(p->YY >= 0);
        //assert(GET(p->XX, p->YY).addedInRound);
        GET(p->XX, p->YY).addedInRound = false;
      }
      swap(backupList, activeList);
      activeListSize = backupListSize;
    } // while(elim > 0)

    cout << "Case #" << (cas+1) << ": " << ret << endl;

    delete[] grid;
    delete[] killList;
    delete[] activeList;
    delete[] backupList;
  }
}
