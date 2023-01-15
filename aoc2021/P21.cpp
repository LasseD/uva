//Remove all but starting positions from input.
int pos[2];   //3 4 5 6 7 8 9
int rolls[7] = {1,3,6,7,6,3,1};

// Dynamic programming: Number of ways to at most get this amount of points:
//  pos 1[0;9] pos 2, points 1[0;23], points 2, turns
//        i      j      x              y        turn
LL Q[10][10][32][32][38];

int main() {
  cin >> pos[0] >> pos[1];
  cout << "Start game with player 1 at position " << pos[0] << " and player 2 at " << pos[1] << endl;
  pos[0]--;
  pos[1]--;

  // Initial setup for 0 points:
  FORI(10) {
    FORJ(10) {
      FORX(32) {
	FORY(32) {
	  Q[i][j][x][y][0] = 0;
	}
      }
    }
  }
  Q[ pos[0] ][ pos[1] ][ 0 ][ 0 ][ 0 ] = 1; // 1 way to get to start position in turn 0 with 0 points

  for(int turn = 1; turn < 38; turn++) { // At most 38 turns... most likely less
    // Player 1 to get points with player 2 having less:
    cout << "TURN " << turn << endl;
    FORI(10) { // position i for player 1
      FORJ(10) { // position j for player 2
	FORX(32) { // player 1 x points
	  FORY(32) { // player 2 y points
	    // Find out how many ways we can get to this state in turn:
	    Q[i][j][x][y][turn] = 0;
	    if(x >= 21 && y >= 21) {
	      continue; // Game stopped as soon as one of them won.
	    }
	    
	    if(turn%2 == 1) { // Player 1 moved
	      if(y >= 21)
		continue; // Player 2 already won
	      for(int rollI = 0; rollI < 7; rollI++) {
		int roll = rollI+3;
		LL mult = rolls[rollI];
		int prevPosition = (i-roll+10)%10;
		int prevPoints = x-(i+1); // current position x, i+1 points received.
		if(prevPoints < 0 || prevPoints >= 21)
		  continue;
		Q[i][j][x][y][turn] += mult*Q[prevPosition][j][prevPoints][y][turn-1];
		//if(Q[prevPosition][j][prevPoints][y][turn-1] > 0) cout << mult << " Player 1 prevPos " << (prevPosition+1) << " roll " << roll << " pos " << (i+1) << " -> " << x << " points" << endl;
	      }
	    }
	    else {
	      if(x >= 21)
		continue; // Player 1 already won
	      for(int rollI = 0; rollI < 7; rollI++) {
		int roll = rollI+3;
		LL mult = rolls[rollI];
		int prevPosition = (j-roll+10)%10;
		int prevPoints = y-(j+1); // current position y
		if(prevPoints < 0 || prevPoints >= 21)
		  continue;
		Q[i][j][x][y][turn] += mult*Q[i][prevPosition][x][prevPoints][turn-1];
		//if(Q[i][prevPosition][x][prevPoints][turn-1]) cout << mult << " Player 2 prevPos " << (prevPosition+1) << " roll " << roll << " pos " << (j+1) << " -> " << y << " points" << endl;
	      }
	    }
	    /*if(Q[i][j][x][y][turn] > 0) {
	      cout << "Player 1 at " << (i+1) << " with " << x << " points" << endl;
	      cout << "Player 2 at " << (j+1) << " with " << y << " points" << endl;
	      cout << "Ways to get here: " << Q[i][j][x][y][turn] << endl;
	    }//*/
	  }
	}
      }
    }
  }

  // Find out how many times each player wins:
  // Player 1:
  LL p1 = 0, p2 = 0;
  for(int turn = 1; turn < 38; turn++) {
    FORI(10) { // position i for player 1
      FORJ(10) { // position j for player 2
	FORX(32) { // player 1 x points
	  FORY(32) { // player 2 y points
	    if(Q[i][j][x][y][turn] < 0) {
	      cerr << "Unexpected state!" << endl;
	      die();
	    }
	    if(Q[i][j][x][y][turn] == 0)
	      continue;
	    if(x >= 21) {
	      p1 += Q[i][j][x][y][turn];
	      if(y >= 21) {
		cerr << "Unexpected state!" << endl;
		die();
	      }
	    }
	    if(y >= 21) {
	      p2 += Q[i][j][x][y][turn];
	      if(x >= 21) {
		cerr << "Unexpected state!" << endl;
		die();
	      }
	    }
	  }
	}
      }
    }
  }
  cout << "Player 1 wins in: " << p1 << endl;
  cout << "Player 2 wins in: " << p2 << endl;
  
	       
}

/* Part 1:
int pos[2], points[2] = {0,0}, d = -1, numRolls = 0;

int roll() {
  d++;
  if(d == 100)
    d = 0;
  numRolls++;
  return d+1;
}

int main() {
  cin >> pos[0] >> pos[1];
  pos[0]--;
  pos[1]--;

  int player = 0;
  while(points[0] < 1000 && points[1] < 1000) { // 1000 for part 1
    int rolled = roll() + roll() + roll();
    pos[player] = (pos[player]+rolled)%10;

    cout << "Player " << (player+1) << " rolled total " << rolled << " and moved to " << (pos[player]+1) << endl;
    
    points[player] += pos[player]+1;
    player = 1-player;
  }
  int winner = 1-player; // winner
  cout << "Player " << (winner+1) << " wins with " << points[winner] << " points." << endl; 
  cout << "Rolls: " << numRolls << endl;  
  cout << (numRolls * points[1-winner]) << endl;
 */
