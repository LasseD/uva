import java.io.*;
import java.util.*;

public class P10928 {
    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line = br.readLine();
	int cases = Integer.parseInt(line.trim());

	for(int cas = 0; cas < cases; ++cas) {
	    if(cas > 0)
		br.readLine();
	    int N = Integer.parseInt(br.readLine().trim());
	    int[] lenghts = new int[N];
	    int min = 99999;
	    for(int i = 0; i < N; ++i) {
		lenghts[i] = br.readLine().trim().split("\\s+").length;
		if(lenghts[i] < min)
		    min = lenghts[i];
	    }
	    boolean first = true;
	    for(int i = 0; i < N; ++i) {
		if(lenghts[i] != min)
		    continue;
		if(!first)
		    System.out.print(" ");
		System.out.print(i+1);
		first = false;
	    }
	    System.out.println();
	}
    }
}
