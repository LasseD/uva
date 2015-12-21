import java.util.*;

/**
 * In place quick sort: Random pivot. Move pivot out of the way. Merge. Recurse.
 */
public class InPlaceQuickSort {
    private static Random r = new Random();

    private static void swap(int[] a, int b, int c) {
	if(b == c)
	    return;
	int tmp = a[b];
	a[b] = a[c];
	a[c] = tmp;
    }

    private static void sort(int[] a, final int low, final int high) {
	System.err.print("Sorting " + low + " -> " + high + ": [");
	for(int i = low; i < high; ++i)
	    System.err.print(" " + a[i]);
	System.err.println("]");
	if(low+1 >= high) {
	    System.err.println("At most one element. Exiting.");
	    return; // At most one element.
	}
	if(low+2 == high) {
	    System.err.println("Two elements. Swap if necessary. Exiting.");
	    if(a[low] > a[high-1])
		swap(a, low, high-1);
	    return;
	}
	final int pivot = low + r.nextInt(high-low);
	System.err.println("Pivot at " + pivot + ": " + a[pivot]);
	swap(a, low, pivot); // Get the pivot out of the way.
	int lowC = low+1; // Ready to be swapped around.
	int highC = high; // Already swapped.
	while(lowC < highC) {
	    if(a[lowC] < a[low]) {
		++lowC;
	    }
	    else {
		swap(a, lowC, --highC);		
	    }
	}
	swap(a, low, highC-1);
	System.err.print("After round: [");
	for(int i = low; i < high; ++i)
	    System.err.print(" " + a[i]);
	System.err.println("]");
	sort(a, low, highC-1);
	sort(a, highC, high);
    }

    public static void main(String[] args) {
	Scanner s = new Scanner(System.in);
	int size = s.nextInt();
	
	int[] a = new int[size];
	for(int i = 0; i < size; ++i)
	    a[i] = s.nextInt();
	
	System.out.println("Read array of size " + size + ". Sorting...");
	//Arrays.sort(a); no no no
	sort(a, 0, size);
	for(int i = 0; i < size; ++i)
	    System.out.print(" " + a[i]);
	System.out.println();
    }
}