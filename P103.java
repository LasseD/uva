import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Stack;

public class P103 {
    public static void main(String[] args) throws IOException {
    	BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
    	String line;
    	while(null != (line = rd.readLine())) {
    		if(line.trim().isEmpty())
    			continue;
    		Scanner s = new Scanner(line);
    		int numBoxes = s.nextInt();
    		Box[] boxes = new Box[numBoxes];
    		int numDims = s.nextInt();
    		for(int i = 0; i < numBoxes; ++i) {
    			line = rd.readLine();
        		s = new Scanner(line);
        		int[] dims = new int[numDims];
        		for(int j = 0; j < numDims; ++j) {
			    dims[j] = s.nextInt();
        		}
        		boxes[i] = new Box(dims, i+1);        		
    		}
    		Arrays.sort(boxes);
    		
    		// Brute force the result!
    		// For each box: compute the max nesting number:
    		int boxWithMaxNesting = 0;
    		int[] numNestings = new int[numBoxes];
    		int[] nestsFrom = new int[numBoxes];
    		for(int i = 0; i < numBoxes; ++i) {
    			numNestings[i] = 1; // At least the box itself
    			nestsFrom[i] = -1;
			for(int j = 0; j < i; ++j) {
				if(boxes[j].fitsIn(boxes[i])) {
				    int nesting = 1 + numNestings[j];
				    if(nesting > numNestings[i]) {
					numNestings[i] = nesting;
					nestsFrom[i] = j;
				    }
    				}
    			}
    			if(numNestings[i] > numNestings[boxWithMaxNesting]) {
    				boxWithMaxNesting = i;
    			}
    		}
    		System.out.println(numNestings[boxWithMaxNesting]);

    		LinkedList<Integer> stack = new LinkedList<Integer>();
    		int box = boxWithMaxNesting;
    		while(box != -1) {
    			stack.addFirst(boxes[box].index);
    			box = nestsFrom[box];
    		}
    		
    		boolean first = true;
    		for(int i : stack) {
    			if(!first)
        			System.out.print(" ");    				
    			System.out.print(i);
    			first = false;
    		}
    		System.out.println();
    	}
    }

    private static class Box implements Comparable<Box> {
    	int index;
    	int[] dims;
    	
    	public Box(int[] dims, int index) {
    		this.index = index;
    		this.dims = dims;
    		Arrays.sort(this.dims);
    	}
    	
    	public boolean fitsIn(Box other) {
    		for(int i = 0; i < dims.length; ++i) {
    			if(dims[i] >= other.dims[i])
    				return false;
    		}
    		return true;
    	}
    	
    	public int compareTo(Box other) {
    		for(int i = 0; i < dims.length; ++i) {
    			if(dims[i] > other.dims[i])
    				return 1;
    			else if(dims[i] < other.dims[i])
    				return -1;
    		}
    		return index < other.index ? -1 : 1;
    	}
    }
}
