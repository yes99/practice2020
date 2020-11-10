import MultiThread.SearchTask;
import java.util.Scanner;

public class Main 
{

	public static void main(String[] args)
    {
		System.out.println("검색하고 싶은 것"); 
        String target;
		Scanner sc = new Scanner(System.in);
		target = sc.next();
		
        Runnable r1 = new SearchTask("https://www.melon.com/chart/day/index.htm",target);
        new Thread(r1).start();        
        Runnable r2 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=202005&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=true",target);
        new Thread(r2).start();
        Runnable r3 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200601&params%5BendDay%5D=20200607&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r3).start();
        Runnable r4 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200525&params%5BendDay%5D=20200531&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r4).start();
        Runnable r41 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200518&params%5BendDay%5D=20200524&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r41).start();
        Runnable r5 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200511&params%5BendDay%5D=20200517&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r5).start();
        Runnable r6 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200504&params%5BendDay%5D=20200510&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r6).start();
        Runnable r7 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200427&params%5BendDay%5D=20200503&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r7).start();
        Runnable r8 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200420&params%5BendDay%5D=20200426&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r8).start();
        Runnable r9 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200413&params%5BendDay%5D=20200419&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r9).start();
        Runnable r10= new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200406&params%5BendDay%5D=20200412&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r10).start();
        Runnable r11 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200330&params%5BendDay%5D=20200405&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r11).start();
        Runnable r12 = new SearchTask("https://www.melon.com/chart/week/index.htm#params%5Bidx%5D=1&params%5BstartDay%5D=20200323&params%5BendDay%5D=20200329&params%5BisFirstDate%5D=true&params%5BisLastDate%5D=false",target);
        new Thread(r12).start();
        Runnable r13 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=202004&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r13).start();
        Runnable r14 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=202003&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r14).start();
        Runnable r15 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=202002&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r15).start();
        Runnable r16 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=202001&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r16).start();
        Runnable r17 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201912&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r17).start();
        Runnable r18 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201911&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r18).start();
        Runnable r19 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201910&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r19).start();
        Runnable r20 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201909&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r20).start();
        Runnable r21 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201908&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r21).start();
        Runnable r22 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201907&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r22).start();
        Runnable r23 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201906&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r23).start();
        Runnable r24 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201905&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r24).start();
        Runnable r25 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201904&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r25).start();
        Runnable r26 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201904&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r26).start();
        Runnable r27 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201902&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r27).start();
        Runnable r28 = new SearchTask("https://www.melon.com/chart/month/index.htm#params%5Bidx%5D=1&params%5BrankMonth%5D=201901&params%5BisFirstDate%5D=true&params%5BisLastDate%5D=false",target);
        new Thread(r28).start();
        Runnable r29 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=202005&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=true",target);
        new Thread(r29).start();
        Runnable r30 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=202004&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r30).start();
        Runnable r31 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=202003&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r31).start();
        Runnable r32 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=202002&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r32).start();
        Runnable r33 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=202001&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r33).start();
        Runnable r34 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=201912&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r34).start();
        Runnable r35 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=201911&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r35).start();
        Runnable r36 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=201911&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r36).start();
        Runnable r37 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=201909&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r37).start();
        Runnable r38 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=201908&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r38).start();
        Runnable r39 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=201907&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r39).start();
        Runnable r40 = new SearchTask("https://www.melon.com/chart/month/index.htm?classCd=AB0000#params%5Bidx%5D=1&params%5BrankMonth%5D=201906&params%5BisFirstDate%5D=false&params%5BisLastDate%5D=false",target);
        new Thread(r40).start();
    }
}
