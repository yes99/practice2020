package searchtest;

import java.net.*;
import java.io.*;

/**

* URL로 지정되는곳에서 TARGET을 찾습니다.

*/

package searchtest;

public class BasicConcurrentSearch {

    public static void main(String[] args) 
    {
           if (args.length != 1) 
           {          
                         System.out.println("java -classpath CLASSPATH BasicConcurrentSearch person");
                         System.exit(1);
           }
           
        String target = args[0];       
        Runnable r1 = new SearchTask("http://www.sportsseoul.com",target);
        new Thread(r1).start();        

        Runnable r2 = new SearchTask("http://www.sportschosun.com",target);
        new Thread(r2).start();

        Runnable r3 = new SearchTask("http://www.stoo.com",target);
        new Thread(r3).start();

        Runnable r4 = new SearchTask("http://www.goodday.com",target);
        new Thread(r4).start();

    }

}

public class SearchTask implements Runnable 
{                                  
    private String url;                                                                          
    private String target;                  
    /**
    * String url    : 검색할 URL
    * String target : 검색할 대상
    */                              
    public SearchTask(String url,String target)
    {
        this.url = url;
        this.target = target;
    }
    public void run() 
    {
        BufferedReader br = null;                                
        try 
        {
        URL u = new URL(url);
            br = new BufferedReader(new InputStreamReader(u.openStream()));                  
            String s = "";
            while((s = br.readLine()) != null)
            {                                                    
                if (s.indexOf(target) != -1) 
                {                                                        
                    System.out.println(url + " , " + target + " 찾았습니다.");
                    return;                                                                                                          
                }
            }
            System.out.println(url + " , " + target + " 없습니다.");
        }
        catch(Exception e )
        {
            e.printStackTrace();
        }
        finally 
        {
            try 
            {
                if (br != null)                        
                    br.close();
            }
            catch(Exception ignore) 
            { 
            	
            }         
        }

    }

}