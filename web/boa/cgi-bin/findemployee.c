#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite.h"
#include "utils.h"
int main(){
int routine_id;
char *input;
char *req_method;
   char led[10];
   int i = 0;
   int j = 0;
   int fd;
   struct person* persons;
   int count;//�������
   char *param=0;//����
	char test[20];
   char eque='=';
   //printf("Content-type: text/html; charset=iso-8859-1\n\n\n\n\n");
	printf("Content-type:text/html;charset=gbk\n\n");
	printf("<HEAD>\n");
	printf("<TITLE> post method </TITLE>\n");
	printf("<style>\n");
	printf("h1{text-align:center}");
	printf("h3{text-align:center}");
	printf("table{text-align:center}");
	printf("</style>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	printf("<h1>Ա����Ϣ</h1>");
   req_method = getenv("REQUEST_METHOD");
   input = getcgidata(stdin, req_method);//����input�е��ַ�����Ϣȷ��led�Ƶĵ����ر�
//���²������ƴ���
	//printf("Your POST Message is \"%s\". \n\n", input);
   //printf("The following is query reuslt:\n");
	sqliteDB_open();
    if(strstr(input,"pnumber")){//����Ա���Ų���
        //param=getparameter(input,"pnumber");
			//printf("Your POST pnumber is \"%s\". \n\n", param);
			for(j=0;j<strlen(input);++j){
					if(input[j-1]=='='){
					//printf("Your POST =%d",j);
						i=j;
					}
					if(i>0){
					test[j-i]=input[j];					
					}			
				}
	//printf("Your POST pnamenumber test is %s", test);        
	count=get_employee_by_number(test,&persons);
	if(count==0){
		printf("<h3>û����Ҫ����Ϣ!</h3>");
 		 }
    }else if(strstr(input,"pname")){//������������
			//param=(char*) malloc(sizeof(char*)*10);
        		//strcpy(param,getparameter(input,"pname"));
		//printf("Your POST pnumber is \"%s\". \n\n", param);
		//sqliteDB_opt_add_person("yangtao","140410430","1995011");
		//param=getparameter(input,"pname");	
		//printf("Your POST pname count %d", strlen(input));
		//printf("Your POST pname is %s", param);
			for(j=0;j<strlen(input);++j){
					if(input[j-1]=='='){
					//printf("Your POST =%d",j);
						i=j;
					}
					if(i>0){
					test[j-i]=input[j];					
					}			
				}
	//printf("Your POST pname test is %s", test);
			//f//or(j=0;j<strlen(param);++j){
		//test=strcpy(test,param);
	count=get_employee_by_name(test,&persons);
	if(count==0){
		printf("<h3>û����Ҫ����Ϣ!</h3>");
}
        //��ӡԱ����Ϣ
    }else{
        printf("\n ָ������!\n");
    }
	//count=get_all_people(&persons);
	  //  printf("count:%d",count);
sqliteDB_close();

   close(fd);
printf("</BODY>\n");
   return 0;
 }

