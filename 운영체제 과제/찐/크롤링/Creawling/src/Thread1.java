import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
public class Thread1 {

	public static void main(String[] args) {
		// Jsoup�� �̿��ؼ� http://www.cgv.co.kr/movies/ ũ�Ѹ�
		String url = "https://www.melon.com/chart/"; //ũ�Ѹ��� url����
		Document doc = null;        //Document���� �������� ��ü �ҽ��� ����ȴ�

		try 
		{
			doc = Jsoup.connect(url).get();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		//select�� �̿��Ͽ� ���ϴ� �±׸� �����Ѵ�. select�� ���ϴ� ���� �������� ���� �߿��� ����̴�.
		Elements element =doc.select("div#tb_list").select("tr.lst50");

		System.out.println("============================================================");

		//Iterator�� ����Ͽ� �ϳ��� �� ��������
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

