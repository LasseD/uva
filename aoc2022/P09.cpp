int main() {
  vector<PI> tail_positions;
  PI rope[10]; // For answer 1, use 2 instead of 10

  char dir;
  int steps;
  while(cin >> dir >> steps) {
    FORK(steps) {
      switch(dir) {
      case 'U':
	rope[0].YY--;
	break;
      case 'D':
	rope[0].YY++;
	break;
      case 'L':
	rope[0].XX--;
	break;
      case 'R':
	rope[0].XX++;
	break;
      default:
	cerr << "Unknown command " << dir << endl;
	die();
      }

      FORI(9) {
	PI &head = rope[i];
	PI &tail = rope[i+1];
	if(abs(head.XX-tail.XX)+abs(head.YY-tail.YY)==4) {
	  if(head.XX > tail.XX)
	    tail.XX++;
	  else
	    tail.XX--;
	  if(head.YY > tail.YY)
	    tail.YY++;
	  else
	    tail.YY--;
	}
	else if(abs(tail.YY - head.YY)==2) {
	  if(head.YY > tail.YY)
	    tail.YY++;
	  else
	    tail.YY--;
	  if(head.XX!=tail.XX) {
	    tail.XX = head.XX;
	  }
	}
	else if(abs(tail.XX - head.XX)==2) {
	  if(head.XX > tail.XX)
	    tail.XX++;
	  else
	    tail.XX--;
	  if(head.YY!=tail.YY) {
	    tail.YY = head.YY;
	  }
	}
      }
      
      tail_positions.push_back(rope[10-1]);
    } // FOR steps
  } // parse input

  sort(tail_positions.begin(), tail_positions.end());
  int answer = 1;
  FORUI(tail_positions.size()-1) {
    if(tail_positions[i+1] != tail_positions[i])
      answer++;
  }
  cout << answer << endl;
}
