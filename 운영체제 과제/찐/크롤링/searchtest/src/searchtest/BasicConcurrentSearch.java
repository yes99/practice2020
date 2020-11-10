package searchtest;

public class BasicConcurrentSearch {

    public static void main(String[] args) 
    {
           if (args.length != 1) 
           {          
                         System.out.println("java -classpath CLASSPATH BasicConcurrentSearch person");
                         System.exit(1);
           }
           
        String target = args[0];       
        Runnable r1 = new SearchTask("http://www.sportsseoul.com",target);
        new Thread(r1).start();        

        Runnable r2 = new SearchTask("http://www.sportschosun.com",target);
        new Thread(r2).start();

        Runnable r3 = new SearchTask("http://www.stoo.com",target);
        new Thread(r3).start();

        Runnable r4 = new SearchTask("http://www.goodday.com",target);
        new Thread(r4).start();

    }

}