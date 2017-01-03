import java.io.*;
import java.util.*;

public class P11223 {
    public static final String morse = "A .- J .--- S ... 1 .---- . .-.-.- : ---... B -... K -.- T - 2 ..--- , --..-- ; -.-.-. C -.-. L .-.. U ..- 3 ...-- ? ..--.. = -...- D -.. M -- V ...- 4 ....- ' .----. + .-.-. E . N -. W .-- 5 ..... ! -.-.-- - -....- F ..-. O --- X -..- 6 -.... / -..-. _ ..--.- G --. P .--. Y -.-- 7 --... ( -.--. \" .-..-. H .... Q --.- Z --.. 8 ---.. ) -.--.- @ .--.-. I .. R .-. 0 ----- 9 ----. & .-...";

    public static void main(String[] args) throws Exception {
	Map<String, Character> m = new TreeMap<String, Character>();
	String[] morseParts = morse.split("\\s+");
	for(int i = 0; i < morseParts.length; i += 2) {
	    //System.err.println(morseParts[i+1] + " -> " + morseParts[i].charAt(0));
	    m.put(morseParts[i+1], morseParts[i].charAt(0));
	}

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));       
	int scenarios = Integer.parseInt(br.readLine().trim());
	for(int scenario = 0; scenario < scenarios; ++scenario) {
	    if(scenario > 0)
		System.out.println();		    
		
	    System.out.println("Message #" + (scenario+1));
	    String line = br.readLine();
	    //System.err.println(line);
	    String[] parts = line.trim().split("\\s+");
	    int partsI = 0;
	    //System.err.println(parts.length);    
	    boolean prevWasMorse = false;
	    int spaces = 0;
	    for(char c : line.toCharArray()) {
		if(c == '.' || c == '-') {
		    if(!prevWasMorse)
			System.out.print(m.get(parts[partsI++]));
		    prevWasMorse = true;
		    spaces = 0;
		}
		else if(c == ' ') {
		    if(spaces%2 == 1) {
			System.out.print(c);
		    }
		    prevWasMorse = false;
		    ++spaces;
		}
	    }
	    System.out.println();		    
	}
    }
}
