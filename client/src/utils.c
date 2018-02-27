#include "utils/utils.h"
struct tm* gettime(){

    time_t timep;

    struct tm *p;

    time(&timep);

    p=localtime(&timep);

    return p;

}
char* getyear(){

    struct tm* p=gettime();

    int y=1900+p->tm_year;

    static char year[4];

    sprintf(year,"%d" , y);//将int数据转换为字符串
    //itoa(y,year,10);

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return year;

}
int getyearint(){

    struct tm* p=gettime();

    int y=1900+p->tm_year;

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return y;

}
char* getmonth(){

    struct tm* p=gettime();

    int m=1+p->tm_mon;

    static char month[4];

     sprintf(month,"%d" , m);//将int数据转换为字符串
//itoa(m,month,10);

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return month;

}
int getmonthint(){

    struct tm* p=gettime();

    int m=1+p->tm_mon;

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return m;

}
char* getday(){

    struct tm* p=gettime();

    int d=p->tm_mday;

    static char day[4];

    //itoa(d,day,10);

     sprintf(day,"%d" , d);//将int数据转换为字符串
//printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return day;

}
int getdayint(){

    struct tm* p=gettime();

    int d=p->tm_mday;

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return d;

}
char* gethour(){

    struct tm* p=gettime();

    int h=p->tm_hour;

    static char hour[2];
    sprintf(hour,"%d" , h);//将int数据转换为字符串

    //itoa(h,hour,10);

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return hour;

}
int gethourint(){

    struct tm* p=gettime();

    int h=p->tm_hour;

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return h;

}
char* getminute(){

    struct tm* p=gettime();

    int h=p->tm_min;

    static char hour[2];

    //itoa(h,hour,10);

     sprintf(hour,"%d" , h);//将int数据转换为字符串
//printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return hour;

}
int getminuteint(){

    struct tm* p=gettime();
    int h=p->tm_min;

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return h;

}
char* getsec(){

    struct tm* p=gettime();

    int h=p->tm_sec;

    static char hour[2];

    //itoa(h,hour,10);

     sprintf(hour,"%d" , h);//将int数据转换为字符串
//printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return hour;

}
int getsecint(){

    struct tm* p=gettime();

    int h=p->tm_sec;

    //printf("日期：%s\n",year);

    //char * u;

    //strcpy(u,year);

    return h;

}
char* getDate(){

    static char date[50] ;

    strcpy(date,getyear());

    strcat(date,"-");

    strcat(date,getmonth());

    strcat(date,"-");



    strcat(date,getday());

    return date;

}
char* get_time_string(){
     static char date[50] ;

    strcpy(date,gethour());

    strcat(date,":");

    strcat(date,getminute());

    strcat(date,":");



    strcat(date,getsec());

    return date;
}
long getDateInt(){
    return (getyearint()*10000+getmonthint()*100+getdayint());

}
long getTimeInt(){
    return (gethourint()*10000+getminuteint()*100+getsecint());

}
char* parseDateInt(long date_int){
    char y[4];
    static char s[12];
    //itoa(date_int/10000,y,10);
 sprintf(y,"%ld" ,date_int/10000);//将int数据转换为字符串
    printf("%s\n",y);

    strcpy(s,y);//年份

    strcat(s,"-");
sprintf(y,"%ld" ,date_int%10000/100);//将int数据转换为字符串
    //itoa(date_int%10000/100,y,10);

    strcat(s,y);//月份

    strcat(s,"-");
sprintf(y,"%ld" ,date_int%100);//将int数据转换为字符串
    //itoa(date_int%100,y,10);


    strcat(s,y);//天

    return s;

}
char* parseTimeInt(long date_int){
   static char s[12];
    char y[4];
sprintf(y,"%ld" ,date_int/10000);//将int数据转换为字符串
   // itoa(date_int/10000,y,10);

    printf("%s\n",y);

    strcpy(s,y);//时

    strcat(s,":");
sprintf(y,"%ld" ,date_int%10000/100);//将int数据转换为字符串
    //itoa(date_int%10000/100,y,10);

    strcat(s,y);//分

    strcat(s,":");

    //itoa(date_int%100,y,10);
sprintf(y,"%ld" ,date_int%100);//将int数据转换为字符串
    strcat(s,y);//秒

    return s;

}
/*
void main(){
    puts(getDate());
    puts(get_time_string());
}
*/
