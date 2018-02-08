#include<my_global.h>
#include<mysql.h>
#include<string.h>
#include<math.h>
int main()
{
	int ch,ti,i,temp;
	float rf=7.12,org[100],curr,ydiff,annr,simr[100],stdd,cl[100];
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
		printf("\n\tMENU\n1.Return\n2.Exit\nEnter choice:");
		scanf("%d",&ch);
		
		if(ch==2) 
			printf("Exiting..");
		else if(ch>2) printf("\nError");
		else 
		{
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
			strcpy(q,"select max(year(time)) from nse_history_day symbol=\'");
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
	      			yr=atof(row[0]);
	
			printf("\nEnter symbol:");
			scanf("%s",sym);
			printf("\nEnter from which year:");
			scanf("%s",ydiff);
			strcpy(q,"select close from nse_history_day where time in (select min(time) from nse_history_day where symbol=\'");
			strcpy(q2,"\' group by year(time)) and symbol=\'");
			strcpy(q3,"\' and year(time)<=");
			
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
			strcpy(q4,"\' and year(time)<");
			
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
				simr[i]=(cl[i]-org[i])/org[i];
				printf("\n%f",simr[i]);
			}
			temp=i-1;
			
			
			
			strcpy(q,"select stddev(close) from nse_history_day where symbol=\'");
			strcpy(q2,"\' and year(time)<=");
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

			
			
			//annr=pow(simr[temp]+1,(1.0/ydiff))-1*100;
			//printf("\n%f",annr);
			
		}
		
	}while(ch!=4);   
	
	mysql_free_result(res);
	mysql_close(s);
}
