
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.jsoup.Connection;


import java.net.URL;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;

import java.util.Scanner;


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
     {	
    		String url = this.url; 
    		Document doc = null;        
    		//1차 완료*/
    		try 
    		{
    			doc = Jsoup.connect(url).get();
    		} 
    		catch (IOException e) 
    		{
    			e.printStackTrace();
    		}
    		
    		Elements element =doc.select("div#tb_list").select("tr.lst50");
    		
    		// 각각 크롤링 완료
    		Iterator<Element> ie1 = element.select("div.ellipsis.rank01").iterator();
    		Iterator<Element> ie2 = element.select("div.ellipsis.rank02>a").iterator();
    		Iterator<Element> ie3 = element.select("div.ellipsis.rank03").iterator();	
    		
    		int count = 0;
    		  String all = doc.text();
    		  String[] array_word;
    		  array_word = all.split(" ");
    		for(int i=0 ; i <array_word.length; i++)
    		{
    			if(array_word[i].contains(this.target))
    			{
                    count++;
    			}
    		}
    		System.out.println("당신이 찾은 키워드 : " + count); 
    		System.out.println("현재 당신의 위치 "+ this.url);  


    		System.out.println("============================================================");
    		//크롤링 확인 과정에서 남겨 놓은 출력 과정이다
    		/*while (ie1.hasNext()&& ie2.hasNext()&& ie3.hasNext()) 
    		{
    			System.out.println("노래 제목 : "+ ie1.next().text());
    			System.out.println("가수 : "+ ie2.next().text());
    			System.out.println("앨범명 : "+ ie3.next().text());
    		
    		}*/
  
    	}
    }
    
}
