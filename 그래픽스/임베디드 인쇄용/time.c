#include <time.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    char tmbuf[4096];
    struct tm* tm;
    time_t t;

    t = time(NULL);
    tm = localtime(&t);

    strftime(tmbuf, 4096,
        "a:[%a]\n"   /* 현재 locale의 약자 요일(week) 문자열 ex). SUN */
        "A:[%A]\n"   /* 현재 locale의 full 요일(week) 문자열 ex). Sunday*/
        "b:[%b]\n"   /* 현재 locale의 약자 월(달) 문자열 ex). JAN */
        "B:[%B]\n"   /* 현재 locale의 full 월(달) 문자열 ex). January */
        "c:[%c]\n"   /* 현재 locale의 full 일시 정보 ex). Mon Jan 30 16:08:19 2017 */
        "C:[%C]\n"   /* 현재 locale의 세기(century) 정보 year / 100값 ex). 20 */
        "d:[%d]\n"   /* 현재 locale의 일자(day) 정보 ex). 01 ~ 31 */
        "D:[%D]\n"   /* 현재 locale의 날짜(2자리 년도)정보 %m/%d/%y  ex). 01/30/17 */
        "e:[%e]\n"   /* 현재 locale의 일자(day) 정보, %d와 비슷하나 1~9앞에는 space가 붙음 ex). 1~31 */
        "E options\n"
        "Ec:[%Ec]\n" /* %c와 같음 */
        "Ex:[%Ex]\n" /* %x와 같음 */
        "EX:[%EX]\n" /* %X와 같음 */
        "Ey:[%Ey]\n" /* y와 같음 */
        "EY:[%EY]\n" /* %Y와 같음 */
        "F:[%F]\n"   /* %Y-%m-%d format 예). 2017-01-30 */
        "G:[%G]\n"   /* %Y와 같음. 4자리 년도 ex). 2017 */
        "g:[%g]\n"   /* 2자리 년도. ex). 17 */
        "h:[%h]\n"   /* %b와 같음. 현재 locale의 약자 월(달) 문자열 ex). JAN */
        "H:[%H]\n"   /* 00~23까지의 시간 */
        "I:[%I]\n"   /* 01~12까지의 시간 */
        "j:[%j]\n"   /* 001 ~ 366까지의 1월 1일부터 현재까지의 날 수*/
        "k:[%k]\n"   /* [ 0] ~ [23]까지의 시간. 0 ~ 9까지는 앞에 스페이스 붙음. ex).  9  */
        "l:[%l]\n"   /* [ 1] ~ [12]까지의 시간. 0 ~ 9까지는 앞에 스페이스 붙음. ex).  9  */
        "m:[%m]\n"   /* 01 ~ 12까지의 월(month) */
        "M:[%M]\n"   /* 00 ~ 59까지의 분 Minute */
        "n:[%n]\n"   /* new line */
        "O:Options\n"
        "Od:[%Od]\n" /* %d와 같음 */
        "Oe:[%Oe]\n" /* %e와 같음 */
        "OH:[%OH]\n" /* %H와 같음 */
        "OI:[%OI]\n" /* %I와 같음 */
        "Om:[%Om]\n" /* %m과 같음 */
        "OM:[%OM]\n" /* %M과 같음 */
        "OS:[%OS]\n" /* %S와 같음 */
        "Ou:[%Ou]\n" /* %u와 같음 */
        "OU:[%OU]\n" /* %U와 같음 */
        "OV:[%OV]\n" /* %V와 같음 */
        "Ow:[%Ow]\n" /* %w와 같음 */
        "OW:[%OW]\n" /* %W와 같음 */
        "Oy:[%Oy]\n" /* %y와 같음 */
        "p:[%p]\n"   /* AM/PM 구분 */
        "P:[%P]\n"   /* am/pm 구분 */
        "r:[%r]\n"   /* %I:%M:%S %P format의 문자열 ex). 04:05:16 PM */
        "R:[%R]\n"   /* %H:%M format의 시분 문자열  ex). 16:05 */
        "s:[%s]\n"   /* 1970-01-01 00:00:00 +0000(UTC) 기준의 초(seconds) */
        "S:[%S]\n"   /* 00 ~ 60까지의 초 */
        "t:[%t]\n"   /* tab문자 */
        "T:[%T]\n"   /* %H:%M:%S 형태의 24시간 format 문자열. %X와 같음. ex). 16:05:10 */
        "u:[%u]\n"   /* 1~7까지의 요일정보 %w는 0 ~ 6까지의 요일정보*/
        "U:[%U]\n"   /* 0~53까지의 그 해의 몇번째 주(week) */
        "V:[%V]\n"   /* 1 ~ 53까지의 그 해의 몇번째 주(week). 시작 주(week)가 4일 이상인 주부터 1이 됨. */
        "w:[%w]\n"   /* 0 ~ 6까지의 요일정보 0은 일요일 */
        "W:[%W]\n"   /* 00 ~ 53 까지의 그 해의 주정보 01은 처음으로 월요일이 있는 주 */
        "x:[%x]\n"   /* %m/%d/%g format(mm/dd/yy) 형태의 날짜 ex). 01/30/17 */
        "X:[%X]\n"   /* %H:%M:%S 형태의 24시간 format 문자열. %T와 같음.  ex). 16:05:10 */
        "y:[%y]\n"   /* 00 ~ 99까지의 2자리 년도 */
        "Y:[%Y]\n"   /* 4자리 년도 */
        "z:[%z]\n"   /* +hhmm 또는 -hhmm의 time zone 표시 */
        "Z:[%Z]\n"   /* timezone명 ex). KST */
        "%%:[%%]\n"  /* %문자 출력*/
        , tm);
    printf("%s", tmbuf);
}