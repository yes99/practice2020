import java.net.URL;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;



public class Main
{
	URL url = new URL("https://www.melon.com/chart/");
	BufferedReader br = new BufferedReader(new InputStreamReader(url.openStream()));
	StringBuffer sourceCode = new StringBuffer();

	String sourceLine = " ";
	while((sourceLine=br.readLine()) != null) 
	{
	    sourceCode.append(sourceLine+"\n");
	}  
  
	    public static void main (String[] args) 
	{
		// TODO Auto-generated method stub
	}
	

}


