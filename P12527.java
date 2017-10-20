import java.io.*;
import java.util.*;

public class P12527 {
    private static boolean isDup(int i) {
	    char[] letters = ("" + i).toCharArray();
	    boolean taken[] = new boolean[10]; // Digits taken
	    for(int j = 0; j < letters.length; ++j) {
		int digit = letters[j]-'0';
		if(taken[digit])
		    return true;
		taken[digit] = true;
	    }
	    return false;
    }
    
    public static void main(String[] args) throws Exception {
	boolean dup[] = new boolean[5001];
	for(int i = 1; i <= 5000; ++i) {
	    dup[i] = isDup(i);
	}
	
	Scanner br = new Scanner(System.in);
	while(br.hasNextInt()) {
	    int low = br.nextInt();
	    int high = br.nextInt();
	    int ret = 0;
	    for(int i = low; i <= high; ++i) {
		if(!dup[i])
		    ++ret;
	    }
	    
	    System.out.println(ret);
	}
    }
}
