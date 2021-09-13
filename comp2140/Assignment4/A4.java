import java.io.*;

public class A4 {
	static BufferedReader br_;
	static BufferedWriter bw_;
	static double f2(double x, double y) throws Exception{
		double z;
		z = x * x - y * y;
		return z;
		
	}
	public static void main(String args[]) throws Exception {
		int x;
		br_ = new BufferedReader(new FileReader("A41.input"));
		x = new Integer(br_.readLine()).intValue();;
		int y;
		br_ = new BufferedReader(new FileReader("A42.input"));
		y = new Integer(br_.readLine()).intValue();;
		double z;
		z = f2(x, y) + f2(y, x) * 0.5;
		bw_ = new BufferedWriter(new FileWriter("A4.output"));
		bw_.write(String.valueOf(z));
		bw_.close();
		
	}
	
}