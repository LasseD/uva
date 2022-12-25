int answer1 = 0, X=1, cycle=1;

void tick() {
  if(abs((cycle-1)%40-X) <= 1)
    cout << "#";
  else
    cout << ".";
  cycle++;
  if(cycle%40==1) {
    cout << endl;
  }
}

int main() {
  string op;
  while(cin >> op) {
    tick();
    
    if((cycle-20)%40 == 0) {
      answer1 += cycle*X;
    }    
    
    if(op == "addx") {
      tick();
      
      GI(toAdd);
      X+=toAdd;

      if((cycle-20)%40 == 0) {
	answer1 += cycle*X;
      }
    }
  }
  cout << "Answer1: " << answer1 << endl;
}
