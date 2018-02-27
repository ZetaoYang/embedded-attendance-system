#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

#ifdef __cplusplus
extern "C"
{
#endif

//获取时间tm结构体
struct tm* gettime();
//获取年份字符串形式
char* getyear();
//获取年份整数形式
int getyearint();
//获取年份字符串形式
char* getmonth();
//获取月份整数形式
int getmonthint();
//获取日字符串形式
char* getday();
//获取日整数形式
int getdayint();
//获取小时字符串
char* gethour();
//获取小时整数形式
int gethourint();
//获取分钟字符串
char* getminute();
//获取分钟整数形式
int getminuteint();
//获取秒字符串
char* getsec();
//获取秒整数形式
int getsecint();
//获取年月日字符串2017-11-23
char* getDate();
//获取日期封装成整数
long getDateInt();
//获取时分秒字符串
char* get_time_string();
//获取时间封装成整数返回
long getTimeInt();
//把整数日期转换成日期字符串格式
//20170908->2017-09-08
char* parseDateInt(long date_int);
//把时分秒转换成时间字符串格式
//213821->21:38:21
char* parseTimeInt(long date_int);
#ifdef __cplusplus
}
#endif

#endif
