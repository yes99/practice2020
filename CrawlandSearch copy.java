import java.net.*;
import java.io.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

/**
* URL로 지정되는곳에서 TARGET을 찾습니다.
*/
public class SearchTask implements Runnable 
{
    private String url;                                    
    private String target; 
    Document doc = null;
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
        try 
		{
			doc = Jsoup.connect(url).get();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		//select를 이용하여 원하는 태그를 선택한다. select는 원하는 값을 가져오기 위한 중요한 기능이다.
		Elements element =doc.select("div#tb_list").select("tr.lst50");

		System.out.println("============================================================");

		//Iterator을 사용하여 하나씩 값 가져오기
		Iterator<Element> ie1 = element.select("div.ellipsis.rank01").iterator();
		Iterator<Element> ie2 = element.select("div.ellipsis.rank02>a").iterator();
		Iterator<Element> ie3 = element.select("div.ellipsis.rank03").iterator();	
		
		while (ie1.hasNext()&& ie2.hasNext()&& ie3.hasNext()) 
		{
			System.out.println("노래 제목 : "+ ie1.next().text());
			System.out.println("가수 : "+ ie2.next().text());
			System.out.println("앨범명 : "+ ie3.next().text());
			System.out.println();

		}
        System.out.println("============================================================");
        //여기까지가 크롤링 과정

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
                    {
                        br.close();
                    }
            }
            catch(Exception ignore) 
            { 

            }         
        }
        //여기까지가 검색 과정
        
    }
}


