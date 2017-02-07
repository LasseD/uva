import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

// See http://www.mathwords.com/a/area_regular_polygon.htm
public class P10451 {
    public static void main(String[] args) throws IOException {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	int cas = 1;
	while((line = br.readLine()) != null) {
	    String[] parts = line.split("\\s+");
	    double A = Double.parseDouble(parts[1]); // Area of n-sided polygon
	    int n = Integer.parseInt(parts[0]);
	    if(n < 3) {
		return;
	    }
	    double r = Math.sqrt(A/n/Math.tan(Math.PI/n));
	    double R = Math.sqrt(2*A/n/Math.sin(2*Math.PI/n));
	    
	    System.out.printf("Case %d: %.5f %.5f\n", cas++, Math.PI*R*R - A, A - Math.PI*r*r);
	}
    }
}
