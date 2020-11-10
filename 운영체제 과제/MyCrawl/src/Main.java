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



public class Main {
	static Scanner scanner = new Scanner(System.in);

	public static void main(String[] args) throws IOException {
		String url = "https://www.melon.com/chart/"; //크롤링할 url지정
		Document doc = null;        //Document에는 페이지의 전체 소스가 저장된다
		//1차 완료*/
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
		int count = 0;
		  String all = doc.text();
		  String[] array_word;
		  array_word = all.split(" ");
		for(int i=0 ; i <array_word.length; i++)
		{
			if(array_word[i].contains("전미도"))
			{
                count++;
			}

		}
		System.out.println("실험중 : " + count);  //이런 것 또한 있었지
		

		System.out.println("실험중============================================================");

		while (ie1.hasNext()&& ie2.hasNext()&& ie3.hasNext()) 
		{
			System.out.println("노래 제목 : "+ ie1.next().text());
			System.out.println("가수 : "+ ie2.next().text());
			System.out.println("앨범명 : "+ ie3.next().text());
		
		}
		System.out.println("-----------------------------------------------------------------");
		System.out.println("============================================================");
	}
}