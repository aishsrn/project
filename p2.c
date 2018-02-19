#include<my_global.h>
#include<mysql.h>
#include<string.h>
#include<math.h>
#include"he.h"
int main()
{
	int ch,ti,i,temp,diff,co=0;
	float rf=0.07,org[100],curr,ydiff,annr[100],simr[100],stdd,cl[100],shar,sor,ss=0,me=0;
	char sym[100],yr[10],q[500],q2[100],q3[100],q4[100];
	MYSQL *s=mysql_init(NULL);
	MYSQL_RES *res;
    	MYSQL_ROW row;
	if(s==NULL) { fprintf(stderr, "%s\n", mysql_error(s)); mysql_close(s);exit(1);}
	printf("Success\n");
	if(mysql_real_connect(s,"localhost","newuser","Password1-","project",3306,NULL,0)==NULL)
		{ fprintf(stderr, "%s\n", mysql_error(s)); mysql_close(s); exit(1);}
	printf("Connection established\n");
	
	
	do{
		co=0;me=0;ss=0;
		printf("\n\tMENU\n1.Return\n2.Exit\nEnter choice:");
		scanf("%d",&ch);
		
		if(ch==2) 
			printf("Exiting..");
		else if(ch>2) printf("\nError");
		else 
		{
			printf("\nEnter symbol:");
			scanf("%s",sym);
			printf("\nEnter from which year:");
			scanf("%s",yr);
			strcpy(q,"select close from nse_history_day where time in (select max(time) from nse_history_day where symbol=\'");
			strcpy(q4,"\') and symbol=\'");
			strcpy(q3,"\'");
			strcat(q,sym);
			strcat(q,q4);
			strcat(q,sym);
			strcat(q,q3);
			if (mysql_query(s,q)) 
			{
		      		fprintf(stderr, "%s\n", mysql_error(s));
		      		exit(1);
		   	}
		   	res = mysql_use_result(s);
		   	while ((row = mysql_fetch_row(res)) != NULL)
		      			curr=atof(row[0]);
			strcpy(q,"select max(year(time)) from nse_history_day where symbol=\'");
			strcpy(q3,"\'");
			strcat(q,sym);
			strcat(q,q3);
			if (mysql_query(s,q)) 
			{
		      		fprintf(stderr, "%s\n", mysql_error(s));
		      		exit(1);
		   	}
		   	res = mysql_use_result(s);
		   	while ((row = mysql_fetch_row(res)) != NULL)
	      			ydiff=atof(row[0]);
	
			
			strcpy(q,"select close from nse_history_day where time in (select min(time) from nse_history_day where symbol=\'");
			strcpy(q2,"\' group by year(time)) and symbol=\'");
			strcpy(q3,"\' and year(time)>=");
			
			strcat(q,sym);
			strcat(q,q2);
			strcat(q,sym);
			strcat(q,q3);
			strcat(q,yr);
			
			 if (mysql_query(s,q)) 
			{
      				fprintf(stderr, "%s\n", mysql_error(s));
      				exit(1);
   			}
   			res = mysql_use_result(s);
   		
                       for(i=0;((row = mysql_fetch_row(res)) != NULL);i++)
      				org[i]=atof(row[0]);
			
			strcpy(q,"select close from nse_history_day where time in (select max(time) from nse_history_day where symbol=\'");
			strcpy(q2,"\' group by year(time)) and symbol=\'");
			strcpy(q4,"\' and year(time)>=");
			
			strcat(q,sym);
			strcat(q,q2);
			strcat(q,sym);
			strcat(q,q4);
			strcat(q,yr);
			
			 if (mysql_query(s,q)) 
			{
      				fprintf(stderr, "%s\n", mysql_error(s));
      				exit(1);
   			}
   			res = mysql_use_result(s);
   		
                       for(i=0;((row = mysql_fetch_row(res)) != NULL);i++)
      			{	cl[i]=atof(row[0]);
				simr[i]=(cl[i]-org[0])/org[0];
				annr[i]=(pow(simr[i]+1,(1.0/(i+1)))-1);
				printf("\nYear:%d\tSR:%f\tAR:%f",atoi(yr)+i,simr[i],annr[i]);
			}
			temp=i-1;
			
			
			
			/*strcpy(q,"select stddev(close) from nse_history_day where symbol=\'");
			strcpy(q2,"\' and year(time)>=");
			strcat(q,sym);
			strcat(q,q2);
			strcat(q,yr);
			if (mysql_query(s,q)) 
			{
      				fprintf(stderr, "%s\n", mysql_error(s));
      				exit(1);
   			}
   			res = mysql_use_result(s);
   		
                       while ((row = mysql_fetch_row(res)) != NULL)
      				stdd=atof(row[0]);

			
			diff=ydiff-atoi(yr)+1;
			
			shar=(annr-rf)/stdd;
			
			for(i=0;i<=temp;i++)
				me+=annr[i];
			me/=temp+1;
			for(i=0;i<=temp;i++)
				ss+=pow(annr[i]-me,2);
			ss/=temp;
			ss=sqrt(ss);
			//printf("\nStddev:%f",ss);
			shar=(annr[temp]-rf)/ss;
			printf("\nSharpe ratio:%f",shar);
			for(i=0;i<=temp;i++)
				if(annr[i]<0) {me+=annr[i]; co++;}
			me/=co;
			for(i=0;i<=temp;i++)
				if(annr[i]<0) ss+=pow(annr[i]-me,2);
			ss/=co;
			ss=sqrt(ss);
			sor=(annr[temp]-rf)/ss;
			printf("\nSortino ratio:%f",sor);*/
			ratios(annr,temp,rf);
		}
		
	}while(ch!=2);   
	
	mysql_free_result(res);
	mysql_close(s);
}
