import java.io.*;
import java.util.Arrays;

public class P110 {
	private static final StringBuilder sb = new StringBuilder();
	private static long callsDeducedEntries = 0;	
	private static long callsStateComplete = 0;	
	private static long callsWriteCmp = 0;	
	private static long timeStateComplete = 0;	
	private static long timePrintCompleteState = 0;	
	
	private final int n;
	private byte[] state;
	
	public P110(int n) {
		this.n = n;
		state = new byte[n*n];
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Integer.parseInt(br.readLine().trim());
		String line;
		boolean first = true;
		long time = System.currentTimeMillis();
		while((line = br.readLine()) != null) {
			line = line.trim();
			if(line.isEmpty())
				continue;
			P110 program = new P110(Integer.parseInt(line));
			if(!first)
				sb.append('\n');
			program.writeProgram();
			first = false;
		} 
		System.out.print(sb.toString());
		System.err.println("Time, all: " + (System.currentTimeMillis()-time));
		System.err.println("#calls to deducedEntries: " +callsDeducedEntries);
		System.err.println("#calls to stateComplete: " +callsStateComplete);
		System.err.println("#calls to writeCmp: " +callsWriteCmp);
		System.err.println("Time spent in state complete: " + timeStateComplete);		
		System.err.println("Time spent printing: " + timePrintCompleteState);		
	}
	
	private void writeProgram() {
		sb.append("program sort(input,output);\n");
		sb.append("var\n");
		boolean first = true;
		for(int i = 0; i < n; i++) {
			if(!first)
				sb.append(',');
			sb.append((char)(i+'a'));
			first = false;
		}
		sb.append(" : integer;\n");
		sb.append("begin\n");
		sb.append("  readln(");
		first = true;
		for(int i = 0; i < n; i++) {
			if(!first)
				sb.append(',');
			sb.append((char)(i+'a'));
			first = false;
		}
		sb.append(");\n");
		
		state = new byte[n*n]; // i*n+j = 1 is state[i] < state[j], 0 if unknown or same, and -1 otherwise.
		writeCmp("  ");
		
		sb.append("end.\n");
	}
	
	private boolean stateComplete() {		
		callsStateComplete++;
		long time = System.currentTimeMillis();
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(i == j)
					continue;
				if(state[i*n+j] == 0) {
					timeStateComplete += System.currentTimeMillis()-time;
					return false;					
				}
			}
		}
		timeStateComplete += System.currentTimeMillis()-time;
		return true;
	}

	private void printCompleteState(String indent) {
		long time = System.currentTimeMillis();
		// Output state:
		sb.append(indent + "writeln(");
		
		boolean first = true;
		boolean[] done = new boolean[n];
		for(int i = 0; i < n; ++i) { // Fill all n places
			for(int j = 0; j < n; ++j) { // Is digit i j?
				if(done[j])
					continue; // j is already done.
				boolean found = true;
				for(int k = 0; k < n; ++k) { // Check all other.
					if(done[k])
						continue; // All done are smaller than j. 
					if(k == j)
						continue; // Don't check self.
					if(state[j*n+k] == -1) { // j < k
						found = false;
						break;
					}
				}
				if(found) {
					if(!first)
						sb.append(',');
					sb.append((char)(j+'a'));
					done[j] = true;
					first = false;
					break;
				}
			}
		}		
		sb.append(")\n");		
		timePrintCompleteState += System.currentTimeMillis()-time;
	}
	
	private void writeCmp(String indent) {
		callsWriteCmp++;
		if(stateComplete()) {
			printCompleteState(indent);
			return;
		}
		// Set a state and proceed:
		// First find an unknown state:
		int i = 0;
		int j = 0;
		for(i = 0; i < n; ++i) {
			for(j = i+1; j < n; ++j) {
				if(j != i && state[i*n+j] == 0) {
					break; // found;
				}
			}
			if(j < n)
 			  break; // found.
		}
		// First recurse on assumption i < j:
		byte[] stateCopy = Arrays.copyOf(state, state.length);
		fillDeducedEntries(i, j);
		sb.append(indent + "if " + ((char)(i+'a')) + " < " + ((char)(j+'a')) + " then\n");
		writeCmp(indent+"  ");		
		state = stateCopy;

		// Secondly, recurse on assumption i > j:
		stateCopy = Arrays.copyOf(state, state.length);
		fillDeducedEntries(j, i);
		sb.append(indent + "else\n");
		writeCmp(indent+"  ");		
		state = stateCopy;
	}
	
	private void fillDeducedEntries(int i, int j) {
		state[i*n+j] = (byte)1;
		state[j*n+i] = (byte)-1;
		callsDeducedEntries++;

		for(int k = 0; k < n; ++k) { // if k < i and j < l then k < l:
			if(k == i || k == j)
				continue;
			// Simple implications:
			if(state[j*n+k] == 1 && state[i*n+k] == 0) {
//				System.err.print("Found implication of " + (char)(i+'a') + " < " + (char)(j+'a') + " & ");
//				System.err.println((char)(j+'a') + " < " + (char)(k+'a') + " => " + (char)(i+'a') + " < " + (char)(k+'a'));
				fillDeducedEntries(i, k);
			}
			if(state[i*n+k] == -1 && state[j*n+k] == 0) {
//				System.err.print("Found implication of " + (char)(i+'a') + " < " + (char)(j+'a') + " & ");
//				System.err.println((char)(i+'a') + " > " + (char)(k+'a') + " => " + (char)(k+'a') + " < " + (char)(j+'a'));
				fillDeducedEntries(k, j);
			}					
		}
	}
}
