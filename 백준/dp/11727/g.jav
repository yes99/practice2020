import java.util.Scanner;

public class Main {

   public static void main(String[] args) {

      Scanner scanner = new Scanner(System.in);
      int n = scanner.nextInt();
      
      int [] count = new int[n+1000];
      //int [] result = new int[n+10];
      
      count[0]=0;
      count[1]=1;
      count[2]=3;
      
      
      
      for(int i=3;i<n+1;i++) {
         count[i]=count[i-1]+2*count[i-2];
         count[i]=count[i]%10007;
      }
      
      int result = (count[n]);
      
      System.out.print(result);
   }
}