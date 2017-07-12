import java.util.*;
import java.math.*;
import java.io.*;

public class Main 
{
	static public void main(String[] args) 
			throws FileNotFoundException
	{
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);	
		while (in.hasNext())
		{
			int x=in.nextInt();
			out.println(x);
		}
		out.close();
	}
}

class InputReader 
{
	BufferedReader reader;
	StringTokenizer tokenizer;
	public InputReader(InputStream stream) 
	{
		reader = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null;
	}
	public boolean hasNext() 
	{
		while (tokenizer == null || !tokenizer.hasMoreTokens()) 
		{
			try 
			{
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (Exception e) 
			{
				return false;
			}
		}
		return tokenizer.hasMoreTokens();
	}
	public String next() 
	{
		while (tokenizer == null || !tokenizer.hasMoreTokens()) 
		{
			try 
			{
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (Exception e) 
			{
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}
	public int nextInt() 
	{
		return Integer.parseInt(next());
	}
	public Long nextLong()
	{
		return Long.parseLong(next());
	}
	public BigInteger nextBigInteger()
	{
		return new BigInteger(next());
	}
}
