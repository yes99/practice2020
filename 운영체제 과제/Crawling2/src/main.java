
import java.io.IOException;



import org.jsoup.Jsoup;

import org.jsoup.nodes.Document;

import org.jsoup.nodes.Element;

import org.jsoup.select.Elements;



public class main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		String url="https://www.melon.com/chart/index.htm";
                             //크롤링하고싶은 대상 url 을 적는다 
		Document doc=Jsoup.connect(url).get();
		Elements titles=doc.select("div.ellipsis>span>a");
		//Elements singers=doc.select("div.ellipsis rank02 > span>a");
                                             //하단의 그림참조하여 적는다
		//System.out.println(titles.size());
		//System.out.println(singers.size());


		
		for(Element e:titles)
		{
			String song=e.text();
			String singer= e.text();
			System.out.println("노래제목:"+song);
			System.out.println("가수:"+singer);

		}

		System.out.println("============");

		



		

	}

}