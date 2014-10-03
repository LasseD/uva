import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class P10432 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line;
		while((line = br.readLine()) != null) {
			String[] parts = line.split("\\s+");
			if(parts.length != 2) {
				return;
			}
			double r = Double.parseDouble(parts[0]);
			int n = Integer.parseInt(parts[1]);

			double O = (2*Math.PI)/n;
			double singleCircularSegmentArea = 0.5 * (O - Math.sin(O));
			//System.err.println(r + " " + n);
			//System.err.println("SINGLE AREA: " + singleCircularSegmentArea + ", ALL: " + (n*singleCircularSegmentArea));
			double res = (Math.PI-singleCircularSegmentArea*n)*r*r;
			//System.err.println("RES: " + res);
			long resM = Math.round(res*1000);
			System.out.printf("%.3f\n", resM/1000.0);
			//System.err.println();			
		}
	}
}
