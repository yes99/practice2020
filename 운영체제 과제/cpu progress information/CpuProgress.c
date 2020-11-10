#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <termios.h>


typedef struct _process{
    int pro_num, cpu_time, arr_t, pri, wait_t, ta_t, rem_t, st, ft;
} process;

static struct termios old, new;

int select_menu,cur_menu, ent_key;

void initTermios();
int getkeyboard();
void key_check(int n);
void print(); 


int process_fcfs(process *pro, int n);
int process_srt(process *pro, int n);
int process_pri(process *pro, int n);
int process_rr(process *pro, int n, int Q);
int process_sjf(process *pro, int n);
int process_generate(process *pro, int n);
void at_sort(process *pro, int n);
void resort(process *pro, int n);.


void print(){
   switch(select_menu){
      case 1:
	    system("clear");
		printf("\n=================Main Menu====================\n\n▶▶ Read processes from proc.txt\n2. Generate random processes\n3. First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n6. Priority\n7. Round Robin (RR)\n8. Exit\n==============================================\n");
        break;
      case 2:
        system("clear");
		printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n▶▶ Generate random processes\n3. First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n6. Priority\n7. Round Robin (RR)\n8. Exit\n==============================================\n");
        break;
      case 3:
        system("clear");
		printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n2. Generate random processes\n▶▶ First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n6. Priority\n7. Round Robin (RR)\n8. Exit\n==============================================\n");
        break;
      case 4:
        system("clear");
		printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n2. Generate random processes\n3. First come first Serve (FCFS)\n▶▶ Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n6. Priority\n7. Round Robin (RR)\n8. Exit\n==============================================\n");
        break;
      case 5:
        system("clear");
		printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n2. Generate random processes\n3. First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n▶▶ Shortest Remaining time First (SRTF)\n6. Priority\n7. Round Robin (RR)\n8. Exit\n==============================================\n");

         break;
      case 6:
        system("clear");
		printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n2. Generate random processes\n3. First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n▶▶ Priority\n7. Round Robin (RR)\n8. Exit\n==============================================\n");
        break;
      case 7:
		printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n2. Generate random processes\n3. First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n6. Priority\n▶▶ Round Robin (RR)\n8. Exit\n==============================================\n");
		break;
      case 8:
        system("clear");
		printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n2. Generate random processes\n3. First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n6. Priority\n7. Round Robin (RR)\n▶▶ Exit\n==============================================\n");
        break;
   }

}

id key_check(int n){
   switch(n){
      case 65: // up -1
         if(select_menu == 1)
         {
            select_menu = 1;
         }
         else
         {
            select_menu--;
         }
		 system("clear");
         print(select_menu);
		 ent_key=0;
         break;
      case 66: // down +1
         if(select_menu == 8)
         {
            select_menu = 8;
         }
         else
         {
            select_menu++;
         }
		 system("clear");
         print(select_menu);
		 ent_key=0;
         break;
      case 10: // enter
		 if(select_menu == 7){
			 cur_menu=select_menu;
		 ent_key=1;
		 }
		 else{
			 print(select_menu);
         cur_menu=select_menu;
		 ent_key=1;
		 }

         break;
   }
}

void initTermios() {
   tcgetattr(0, &old);
   new = old;
   new.c_lflag &= ~ICANON;
   tcsetattr(0, TCSANOW, &new);
}

int getkeyboard() {
   int ch;
   initTermios();
   ch = getchar();
   return ch;
}

void at_sort(process *pro, int n){
	process temp;
	int i,j;
	for(i=n-1; i>0;i--){
		for(j=0;j<i;j++){
			if(pro[j].arr_t>pro[j+1].arr_t){
				temp=pro[j+1];
				pro[j+1]=pro[j];
				pro[j]=temp;
			
			}
			else if(pro[j].arr_t==pro[j+1].arr_t&&pro[j].pro_num>pro[j+1].pro_num){
				temp=pro[j+1];
				pro[j+1]=pro[j];
				pro[j]=temp;
			}
		}
	}
}


void resort(process *pro, int n){
	process temp;
	int i,j;
	for(i=n-1; i>0;i--){
		for(j=0;j<i;j++){
			if(pro[j].pro_num>pro[j+1].pro_num){
				temp=pro[j+1];
				pro[j+1]=pro[j];
				pro[j]=temp;
			}
		}
	}
}

int process_fcfs(process *pro, int n){
	int temp;
	int wt=0;
	int i,j,k=0;

	for(i=0;i<n;i++){
		temp=0;
		for(j=k;j<i;j++){
			temp=temp+pro[j].cpu_time;
		}
		wt=temp-pro[i].arr_t+pro[k].arr_t;

		if(wt<=0){
			k=i;
			pro[i].wait_t=0;
			pro[i].ta_t=pro[i].cpu_time + pro[i].wait_t;
		}
		else{
			pro[i].wait_t=wt;
			pro[i].ta_t=pro[i].cpu_time + pro[i].wait_t;
		}
	}
}

int process_srt(process *pro, int n){
	int remain, min, now_p, i, temp[150];
	int now, wt=0;

	remain=n;
	now=pro[0].arr_t;
	while(remain>0){
		min=5000;	
		for(i=0; pro[i].arr_t<=now && i<n; i++){	
			if(pro[i].rem_t<min && pro[i].rem_t>0){	
				now_p=i;
				min=pro[i].rem_t;   //가장 적은 남은 동작 시간을 선언
			}
		}
		now++;      //시간 카운트 업
		if(temp[0] !=pro[0].cpu_time){
			for(i=0; i<n; i++){
				temp[i]=pro[i].rem_t;
			}
		}
		
		pro[now_p].rem_t--; //시간이 지날 수록 남은 동작시간 카운트를 감소

		if(pro[now_p].rem_t==0){	//남은 동작시간 0인경우 연산
			pro[now_p].wait_t=now-pro[now_p].arr_t-pro[now_p].cpu_time;
			pro[now_p].ta_t=pro[now_p].cpu_time + pro[now_p].wait_t;
			wt=wt+pro[now_p].wait_t;
			remain--;
		}
	}
	for(i=0; i<n; i++){
		pro[i].rem_t=temp[i];
	}
}

int process_pri(process *pro, int n){
   int flag = 0;
   int i,time,remain,num, min, temp[150];
   
   for(i=0; i<n; i++){
      pro[i].rem_t = pro[i].cpu_time;
   }
   
   time = pro[0].arr_t;
   remain = n;
   
   	if(temp[0] !=pro[0].cpu_time){
		for(i=0; i<n; i++){
			temp[i]=pro[i].rem_t;
		}
	}

   while(remain>0){
    min = 9999;
   for (i=0; pro[i].arr_t <= time && i<n; i++){
       if(pro[i].rem_t != 0 && pro[i].pri<min && pro[i].cpu_time>0){
          num = i;
          min = pro[i].pri;
          flag = 1;
      }
   }
     
      if(flag ==1){
         pro[num].rem_t = 0;
         pro[num].wait_t = time - pro[num].arr_t;
         remain--;
       time += pro[num].cpu_time;
      }
      
      else{
         time ++;
      }
      flag = 0;
   }
   for(i=0; i<n; i++){
      pro[i].ta_t = pro[i].wait_t + pro[i].cpu_time;
   }
   	for(i=0; i<n; i++){
		pro[i].rem_t=temp[i];
	}
}


int process_sjf(process *pro, int n){
   int flag = 0;
   int i,time,remain,num, min, temp[150];
   
   for(i=0; i<n; i++){
      pro[i].rem_t = pro[i].cpu_time;
   }
   
   time = pro[0].arr_t;
   remain = n;
   
	if(temp[0] !=pro[0].cpu_time){
		for(i=0; i<n; i++){
			temp[i]=pro[i].rem_t;
		}
	}

   while(remain>0){
    min = 9999;
   for (i=0; pro[i].arr_t <= time && i<n; i++){
       if(pro[i].rem_t != 0 && pro[i].cpu_time<min && pro[i].cpu_time>0){
          num = i;
          min = pro[i].cpu_time;
          flag = 1;
      }
   }
         
      if(flag ==1){
         pro[num].rem_t = 0;
         pro[num].wait_t = time - pro[num].arr_t;
         remain--;
       time += pro[num].cpu_time;
      }
      
      else{
         time ++;
      }
      flag = 0;
   }
   for(i=0; i<n; i++){
      pro[i].ta_t = pro[i].wait_t + pro[i].cpu_time;
   }
   	for(i=0; i<n; i++){
		pro[i].rem_t=temp[i];
	}
}

int process_rr(process *pro, int n, int Q){
	int temp, temp2[150];
	int i, count, tt;
	
	if(temp2[0] !=pro[0].cpu_time){
		for(i=0; i<n; i++){
			temp2[i]=pro[i].rem_t;
		}
	}
	
	while(1){   //퀀텀만큼만 동작하는 부분입니다.
		for(i=0,count=0;i<n;i++) {
			temp=Q;
			if(pro[i].rem_t==0){
				count++;
				continue;
			}
			if(pro[i].rem_t>Q)
				pro[i].rem_t=pro[i].rem_t-Q;
			else if(pro[i].rem_t>=0) {
				temp=pro[i].rem_t;
				pro[i].rem_t=0;
				}
				tt=tt+temp;
				pro[i].ta_t=tt;
		}
		if(n==count)
			break;
	}
	for(i=0;i<n;i++){
		pro[i].rem_t=temp2[i];
		pro[i].wait_t=pro[i].ta_t-pro[i].cpu_time;
	}
}


int process_generate(process *pro, int n){
	FILE *fp2;
	int j, found;
	fp2=fopen("proc.txt","a+");
	int i=n;
	int bt =(rand()%25)+1;
	
	pro[i].pro_num=i+1;
	pro[i].cpu_time=bt;
	
	while(1){       //겹치지 않는 프로세스 번호 만들기
		pro[i].pri=rand()%50;
		found=0;
		for(j=0;j<i;++j){
			if(pro[j].pri==pro[i].pri){
				found=1;
				break;
			}
		}
		if(!found) break;
	}
	
	while(1){       //겹치지 않는 프로세스 도착시간 만들기
		pro[i].arr_t=rand()%50;
		found=0;
		for(j=0;j<i;++j){
			if(pro[j].arr_t==pro[i].arr_t){
				found=1;
				break;
			}
		}
		if(!found) break;
	}
	fprintf(fp2,"\r\n%d %d %d %d",pro[i].pro_num, pro[i].cpu_time, pro[i].arr_t, pro[i].pri);
	fclose(fp2);
}





