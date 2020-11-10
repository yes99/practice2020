import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
public class Main {
	public static void main(String[] args) 
	{
		// Jsoup�� �̿��ؼ� http://www.cgv.co.kr/movies/ ũ�Ѹ�
		String url = "https://www.melon.com/chart/index.htm"; //ũ�Ѹ��� url����
		Document doc = null;        //Document���� �������� ��ü �ҽ��� ����ȴ�

		try {
			doc = Jsoup.connect(url).get();
		} catch (IOException e) {
			e.printStackTrace();
		}
		//select�� �̿��Ͽ� ���ϴ� �±׸� �����Ѵ�. select�� ���ϴ� ���� �������� ���� �߿��� ����̴�.
		Elements element = doc.select("div.tb_lilst");    

		System.out.println("============================================================");

		//Iterator�� ����Ͽ� �ϳ��� �� ��������
		Iterator<Element> ie1 = element.select("ellipsis rank01").iterator();
		Iterator<Element> ie2 = element.select("ellipsis rank02").iterator();
		//Iterator<Element> ie3 = element.select("").iterator();
		
		while (ie1.hasNext()) {
			System.out.println(ie1.next().text()+"\t"+ie2.next().text());
			//System.out.println(ie3.next().text());
		}
		
		System.out.println("============================================================");
	}
	}