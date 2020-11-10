package search_from_SO;

import java.util.Scanner;

public class BasicConcurrentSearch 
{

	public static void main(String[] args)
    {
        String target = "아이유";

           if (args.length != 1) 
           {          
               System.out.println("java -classpath CLASSPATH BasicConcurrentSearch person");
               System.out.println("원하는 검색어를 입력하세요 : ");
               System.exit(1);
           }
         
        Runnable r1 = new SearchTask("https://www.melon.com/chart/day/index.htm",target);
        new Thread(r1).start();        
   /*     Runnable r2 = new SearchTask("http://www.sportschosun.com",target);
        new Thread(r2).start();
        Runnable r3 = new SearchTask("http://www.stoo.com",target);
        new Thread(r3).start();
        Runnable r4 = new SearchTask("http://www.goodday.com",target);
        new Thread(r4).start();*/
    }
}
