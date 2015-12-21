import java.util.*;

public class TwoSum5 {
    public static void main(String[] args) {
	Scanner s = new Scanner(System.in);
	int size = s.nextInt();
	int sum = s.nextInt();
	
	int[] a = new int[size];
	for(int i = 0; i < size; ++i)
	    a[i] = s.nextInt();
	
	System.out.println("Read array of size " + size + ". Finding all pairs that sum to " + sum + ".");
	Arrays.sort(a);
	int high = size-1;
	boolean done = false;
	for(int low = 0; low < high; ++low) {
	    while(a[high] + a[low] > sum) {
		--high;
		if(high == low) {
		    done = true;
		    break;
		}
	    }
	    if(done)
		break;
	    if(a[high] + a[low] == sum) {
		System.out.println(a[low] + " + " + a[high] + " = " + sum);
	    }
	}
    }
}