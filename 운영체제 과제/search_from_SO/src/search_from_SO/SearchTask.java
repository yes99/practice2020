package search_from_SO;

import java.net.*;
import java.io.*;


public class SearchTask implements Runnable {          

    private String url;                                                                           
    private String target;                  

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
            catch(Exception ignore) { }         
        }
    }
}
