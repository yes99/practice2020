
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
    		//1�� �Ϸ�*/
    		try 
    		{
    			doc = Jsoup.connect(url).get();
    		} 
    		catch (IOException e) 
    		{
    			e.printStackTrace();
    		}
    		
    		Elements element =doc.select("div#tb_list").select("tr.lst50");
    		
    		// ���� ũ�Ѹ� �Ϸ�
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
    		System.out.println("����� ã�� Ű���� : " + count); 
    		System.out.println("���� ����� ��ġ "+ this.url);  


    		System.out.println("============================================================");
    		//ũ�Ѹ� Ȯ�� �������� ���� ���� ��� �����̴�
    		/*while (ie1.hasNext()&& ie2.hasNext()&& ie3.hasNext()) 
    		{
    			System.out.println("�뷡 ���� : "+ ie1.next().text());
    			System.out.println("���� : "+ ie2.next().text());
    			System.out.println("�ٹ��� : "+ ie3.next().text());
    		
    		}*/
  
    	}
    }
    
}
