import java.util.*;
import java.math.*;
import java.io.*;

public class Main 
{
	static public void main(String[] args) 
	{
		Scanner sc=new Scanner(System.in);
		//Scanner sc=new Scanner(new BufferedInputStream(System.in));
		BigInteger u,v;
		BigInteger w[]=new BigInteger[6];
		u=sc.nextBigInteger();
		v=sc.nextBigInteger();
		w[0]=u.add(v);
		w[1]=u.subtract(v);
		w[2]=u.multiply(v);
		w[3]=u.divide(v);
		w[4]=u.remainder(v);
		w[5]=u.gcd(v);
		for (int i=0;i<=5;i++)
			System.out.println(w[i]);
	}
}

