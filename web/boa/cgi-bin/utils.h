#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
//��ȡʱ��tm�ṹ��
struct tm* gettime();
//��ȡ����ַ�����ʽ
char* getyear();
//��ȡ���������ʽ
int getyearint();
//��ȡ����ַ�����ʽ
char* getmonth();
//��ȡ�·�������ʽ
int getmonthint();
//��ȡ���ַ�����ʽ
char* getday();
//��ȡ��������ʽ
int getdayint();
//��ȡСʱ�ַ���
char* gethour();
//��ȡСʱ������ʽ
int gethourint();
//��ȡ�����ַ���
char* getminute();
//��ȡ����������ʽ
int getminuteint();
//��ȡ���ַ���
char* getsec();
//��ȡ��������ʽ
int getsecint();
//��ȡ�������ַ���2017-11-23
char* getDate();
//��ȡ���ڷ�װ������
long getDateInt();
//��ȡʱ�����ַ���
char* get_time_string();
//��ȡʱ���װ����������
long getTimeInt();
//ǰ������ʱ���ַ������ȶ������װ����������
int transform_date(char* datestr);
//����������ת���������ַ�����ʽ
//20170908->2017-09-08
char* parseDateInt(long date_int);
//��ʱ����ת����ʱ���ַ�����ʽ
//213821->21:38:21
char* parseTimeInt(long date_int);
//��ʱ����ת����ʱ���ַ�����ʽ
//213821->21:38:21
char* parseTimeInt(long date_int);
char* getcgidata(FILE* fp, char* requestmethod);
//����ǰ�˴���Ĳ�����ȡ������
char* getparameter(char* input,char* name);