import java.io.*;
import java.util.*;

public class P10528 {
    public static final String[] TONES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    //public static final int[] SPACE = {0, 2, 4, 5, 7, 9, 11};
    public static final int[] NON_SPACE = {1, 3, 6, 8, 10};

    public static void main(String[] args) throws Exception {
	Map<String,Integer> map = new TreeMap<String,Integer>();
	for(int i = 0; i < TONES.length; ++i)
	    map.put(TONES[i], i);

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	while(true) {
	    // read input:
	    String line = br.readLine().trim();
	    if(line.equals("END"))
		return;
	    String[] parts = line.split("\\s+");

	    // Compute hit nodes:
	    boolean[] hit = new boolean[12];
	    for(String part : parts) {
		if(!part.isEmpty())
		    hit[map.get(part)] = true;
	    }

	    // output:
	    boolean first = true;
	    for(int i = 0; i < 12; ++i) {
		// Check accord:
		boolean ok = true;
		for(int nonSpace : NON_SPACE) {
		    if(hit[(i + nonSpace)%12]) {
			ok = false;
			break;
		    }
		}
		if(ok) {
		    if(!first)
			System.out.print(" ");
		    System.out.print(TONES[i]);
		    first = false;
		}
	    }
	    
	    System.out.println();
	}
    }
}
