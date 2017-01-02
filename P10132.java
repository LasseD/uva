import java.io.*;
import java.util.*;

public class P10132 {
    /* 
       Try to match each line s either with front or back of solution:
       - If it matches neither, return false;
       - If it matches only the front, find and remove the complementing line that matches the back. If it doesnt exist, return false.
       - If it matches only the back, find and remove the complementing line that matches the front. If it doesnt exist, return false.
       - If it matches both the front and back:
        -- All other lines of same length must be equl to s - otherwise return false.
       - End by returning true.
    */
    private static boolean solves(List<String> lines, String solution, int maxLength) {
	int[] fronts = new int[maxLength+1]; // index -> number of lines that matches the front of the solution.
	int[] backs = new int[maxLength+1]; // Same for back
	int[] boths = new int[maxLength+1]; // Same when it matches both front and back!
	// Increment fronts, backs and boths:
	for(String line : lines) {
	    if(solution.startsWith(line)) {
		if(solution.endsWith(line)) {
		    //System.err.println(" " + solution + " both starts and ends with " + line);
		    ++boths[line.length()];
		}
		else {
		    ++fronts[line.length()];
		    //System.err.println(" " + solution + " starts with " + line);
		}
	    }
	    else if(solution.endsWith(line)) {
		++backs[line.length()];
		//System.err.println(" " + solution + " ends with " + line);
	    }
	    else
		return false;
	}
	// Find out if all is OK:
	for(int length = solution.length()-maxLength; length <= maxLength; ++length) {
	    int len2 = solution.length()-length;
	    // Count down all fronts:
	    if(boths[length] > 0 || boths[len2] > 0) {
		if(boths[length]+fronts[length]+backs[length] != boths[len2]+fronts[len2]+backs[len2])
		    return false;
	    }
	    else {
		if(fronts[length] != backs[len2] || fronts[len2] != backs[length])
		    return false;
	    }
	    fronts[length] = backs[length] = boths[length] = fronts[len2] = backs[len2] = boths[len2] = 0;
	}
	return true;
    }

    private static String handleCase(List<String> lines) {
	String L1 = "";
	String S1 = lines.get(0), S2 = lines.get(0);
	for(String s : lines) {
	    if(s.length() > L1.length())
		L1 = s;

	    if(s.length() < S1.length())
		S1 = S2 = s;
	    else if(s.length() == S1.length() && !s.equals(S1))
		S2 = s;
	}
	// Solution is either L1S1, L1S2, S1L1, or S2L1:
	String[] solutions = {L1+S1, L1+S2, S1+L1, S2+L1};
	for(String s : solutions) {
	    //System.err.println("Attempting solution " + s + ", L1=" + L1 + ", S1=" + S1 + ", S2=" + S2);
	    if(solves(lines, s, L1.length()))
		return s;
	}
	throw new RuntimeException();
    }

    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line = br.readLine();
	int cases = Integer.parseInt(line.trim());
	br.readLine();

	for(int cas = 0; cas < cases; ++cas) {
	    if(cas != 0)
		System.out.println();
	    //System.err.println("Case " + cas);
	    List<String> lines = new ArrayList<String>();
	    while((line = br.readLine()) != null && !(line = line.trim()).isEmpty()) {
		lines.add(line);
		//System.err.println(" '" + line + "'");
	    }
	    System.out.println(handleCase(lines));
	}
    }
}
