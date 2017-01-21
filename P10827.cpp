int main() {
  int a[75*75], sums[76*2*76*2];  
  FORCAS {
    int N; // max 75
    // Read data:
    cin >> N;
    int NN = 2*N+1;
    for(int y = 0; y < N; ++y) {
      for(int x = 0; x < N; ++x) {
	cin >> a[y*N+x];
      } // x
    } // y
    /* Compute sums: 
       indices: 0, 1->0, 2->1, ... N->N-1, N+1->0, ... 2N->N-1
     */
    for(int x = 0; x < NN; ++x) {
      sums[x] = 0; // first row.
    }
    for(int y = 1; y <= N; ++y) {
      sums[y*NN] = 0; // first column.
      for(int x = 1; x <= N; ++x) {
	sums[y*NN+x] = a[(y-1)*N+x-1] + sums[(y-1)*NN+x] + sums[y*NN+x-1] - sums[(y-1)*NN+x-1];
      } // x
      for(int x = N+1; x < NN; ++x) {
	sums[y*NN+x] = a[(y-1)*N+x-1-N] + sums[(y-1)*NN+x] + sums[y*NN+x-1] - sums[(y-1)*NN+x-1];
      } // x
    } // y
    for(int y = N+1; y < NN; ++y) {
      sums[y*NN] = 0; // first column.
      for(int x = 1; x <= N; ++x) {
	sums[y*NN+x] = a[(y-1-N)*N+x-1] + sums[(y-1)*NN+x] + sums[y*NN+x-1] - sums[(y-1)*NN+x-1];
      } // x
      for(int x = N+1; x < NN; ++x) {
	sums[y*NN+x] = a[(y-1-N)*N+x-1-N] + sums[(y-1)*NN+x] + sums[y*NN+x-1] - sums[(y-1)*NN+x-1];
      } // x
    } // y 
    /*
    for(int y = 0; y < NN; ++y) {
      for(int x = 0; x < NN; ++x) {
	cerr << " " << sums[y*NN+x];
      }
      cerr << endl;
    }//*/

    // Find best sum:
    int max = a[0];
    for(int width = 1; width <= N; ++width) {
      for(int height = 1; height <= N; ++height) {
	for(int y = height; y <= 2*N; ++y) {
	  for(int x = width; x <= 2*N; ++x) {
	    int sum = sums[y*NN+x] 
	      + sums[(y-height)*NN+x-width] 
	      - sums[y*NN+x-width] 
	      - sums[(y-height)*NN+x];
	    if(sum > max)
	      max = sum;
	  }
	}
      }
    } // for width
    cout << max << endl;
  } // FORCAS
} // main 
