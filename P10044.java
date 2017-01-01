import java.io.*;
import java.util.*;

public class P10044 {
    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));       
	String line = br.readLine().trim();
	int scenarios = Integer.parseInt(line);
	for(int scenario = 0; scenario < scenarios; ++scenario) {
	    System.out.println("Scenario " + (scenario+1));
	    String[] parts = br.readLine().trim().split("\\s+");
	    int P = Integer.parseInt(parts[0].trim());
	    int N = Integer.parseInt(parts[1].trim());

	    //System.err.println("N=" + N + ", P=" + P);
	    // Read the P publications and set up authors and coAuthors
	    //Set<String> authors = new TreeSet<String>();
	    Map<String,Set<String>> coAuthors = new TreeMap<String,Set<String>>();
	    for(int p = 0; p < P; ++p) {
		parts = br.readLine().trim().split("\\.[,\\:]");
		for(int i = 0; i < parts.length-1; ++i) {
		    parts[i] = parts[i].trim() + ".";
		    if(!coAuthors.containsKey(parts[i])) {
			//authors.add(parts[i]);
			coAuthors.put(parts[i], new TreeSet<String>());
		    }
		}
		for(int i = 0; i < parts.length-1; ++i) {
		    String s1 = parts[i];
		    Set<String> s1s = coAuthors.get(s1);
		    for(int j = i+1; j < parts.length-1; ++j) {
			String s2 = parts[j];
			if(!s1s.contains(s2)) {
			    s1s.add(s2);
			    coAuthors.get(s2).add(s1);
			    //System.err.println("Co Author pair: '" + s1 + "' & '" + s2 + "'");
			}
		    }
		}
	    }

	    // Compute Erdos numbers:	    
	    Map<String,Integer> erdosNumbers = new TreeMap<String,Integer>();
	    int erdosNumber = 0;
	    Set<String> readyAuthors = new TreeSet<String>();
	    if(coAuthors.containsKey("Erdos, P.")) {
		readyAuthors.add("Erdos, P.");
	    }
	    while(!readyAuthors.isEmpty()) {
		Set<String> newReadyAuthors = new TreeSet<String>();
		for(String author : readyAuthors) {
		    if(erdosNumbers.containsKey(author))
			continue;
		    erdosNumbers.put(author, erdosNumber);
		    for(String coAuthor : coAuthors.get(author)) {
			if(!newReadyAuthors.contains(coAuthor))
			    newReadyAuthors.add(coAuthor);
		    }
		}
		readyAuthors = newReadyAuthors;
		++erdosNumber;
	    } // while.
	    
	    // Handle queries:
	    for(int i = 0; i < N; ++i) {
		line = br.readLine().trim();
		System.out.print(line + " ");
		if(!erdosNumbers.containsKey(line)) {
		    System.out.println("infinity");
		}
		else {
		    erdosNumber = erdosNumbers.get(line);
		    System.out.println(erdosNumber);		    
		}
	    }
	}
    }
}
