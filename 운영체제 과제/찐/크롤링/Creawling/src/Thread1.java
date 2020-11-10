import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
public class Thread1 {

	public static void main(String[] args) {
		// Jsoup를 이용해서 http://www.cgv.co.kr/movies/ 크롤링
		String url = "https://www.melon.com/chart/"; //크롤링할 url지정
		Document doc = null;        //Document에는 페이지의 전체 소스가 저장된다

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
			System.out.println("name : "+ ie1.next().text());
			System.out.println("singer : "+ ie2.next().text());
			System.out.println("album : "+ ie3.next().text());
			System.out.println();

		}
		
		System.out.println("============================================================");
	}
}

