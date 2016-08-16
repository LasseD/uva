import java.io.*;
import java.math.BigInteger;

/*
#include <iostream>

int main() {
  unsigned long long long N, a[1001];
  a[0] = 1;
  a[1] = 2;
  a[2] = 5;
  a[3] = 13;
  for(int i = 4; i <= 1000; ++i) {
    a[i] = 2*a[i-1] + a[i-2] + a[i-3];
  }

  while(std::cin >> N) {
    std::cout << a[N] << std::endl;
  }
  return 0;
}
 */
public class P10198 {
    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	BigInteger[] a = new BigInteger[1001];
	a[0] = BigInteger.ONE;
	a[1] = new BigInteger("2");
	a[2] = new BigInteger("5");
	for(int i = 3; i <= 1000; ++i) {
	    a[i] = a[i-1].add(a[i-1]).add(a[i-2]).add(a[i-3]);
	}

	while(null != (line = br.readLine())) {
	    System.out.println(a[Integer.parseInt(line.trim())]);
	}
    }
}
