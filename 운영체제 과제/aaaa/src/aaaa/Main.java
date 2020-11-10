package aaaa;

import java.util.ArrayList;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;

public class Main 
{

	static void main (String[] args) 
	{
		String url = "https://www.melon.com/chart/index.htm";
		Document doc = null;
		Elements tmp;
		String name_temp = null;
		String singer_temp = null;
		String album_temp = null;
		int rank = 0;
		try 
		{
			doc = Jsoup.connect(url).get();
		} catch (Exception e) 
		{
			e.printStackTrace();
		}
		// 1~50위
		Elements element = doc.select("div#tb_list").select("tr.lst50");

		for (int i = 0; i < 50; i++) 
		{
			// 이름 가져오는 과정
			tmp = element.select("div.ellipsis.rank01");
			name_temp = tmp.get(i).text();
			// 가수 가져오는 과정
			tmp = element.select("div.ellipsis.rank02").select("span");
			singer_temp = tmp.get(i).text();
			// 앨범 가져오는 과정
			tmp = element.select("div.ellipsis.rank03");
			album_temp = tmp.get(i).text();
			// 등수를 가져오는 과정
			tmp = element.select("span.rank");
			rank = Integer.parseInt((tmp.get(i).text()));
			// arrayList에 삽입
			
		}
		//51~ 100위
		element = doc.select("div#tb_list").select("tr.lst100");
		for (int i = 0; i < 50; i++) 
		{
			// 이름 가져오는 과정
			tmp = element.select("div.ellipsis.rank01");
			name_temp = tmp.get(i).text();
			// 가수 가져오는 과정
			tmp = element.select("div.ellipsis.rank02").select("span");
			singer_temp = tmp.get(i).text();
			// 앨범 가져오는 과정
			tmp = element.select("div.ellipsis.rank03");
			album_temp = tmp.get(i).text();
			// 등수를 가져오는 과정
			tmp = element.select("span.rank");
			rank = Integer.parseInt((tmp.get(i).text()));
			// arrayList에 삽입
			
		System.out.println("Crawling complete");
		
		}
	}
}