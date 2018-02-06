#include<my_global.h>
#include<mysql.h>
#include<string.h>

void getf(char* line, int num, char* b)
{
	int i,k=1,t=num;
	char s[100];
	s[0]='\'';
	i=0;
	for(i=0;line[i];i++)
	{
		if(line[i]==',')
			{num--;if(num==1) i++;} 
		if(num==1)
		{	
			while(line[i]!=',')
				if(line[i]!='\'') s[k++]=line[i++];
			s[k]='\'';
			s[k+1]='\0';
			strcpy(b,s);
			return;
		}
	}
	
	return;
}
int main()
{
	MYSQL *s=mysql_init(NULL);
	char b[500];
	if(s==NULL) { fprintf(stderr, "%s\n", mysql_error(s)); mysql_close(s);exit(1);}
	printf("Success\n");
	if(mysql_real_connect(s,"localhost","newuser","Password1-","project",3306,NULL,0)==NULL)
		{ fprintf(stderr, "%s\n", mysql_error(s)); mysql_close(s); exit(1);}
	printf("Connection established\n");
	
	
	
	
	
	int w,i,ch,j;
	long int n=0;
	char line[1024],a[100],q[1000];
	FILE *f=fopen("/home/inxs/Downloads/sri/MASTER_QUOTE.csv","r");
	fgets(line,1024,f);
	
	
	
       
	
	while(fgets(line,1024,f))
	{      //printf("%s",line);
		n++;
		//memset(b, '\0', sizeof(char) * 500);
		//memset(q, '\0', sizeof(char) * 1000);
		strcpy(q,"INSERT INTO master_t VALUES(");
		getf(line,1,b);
		
		//printf("%s",b);
		//printf("\n%ld",n);
		if(strcmp("\'NSE\'",b)==0)		
		{
			for(i=0;i<8;i++)
			{
				getf(line,i+1,b);
				strcat(q,b);
				if(i!=7) strcat(q,",");
				else strcat(q,")");
			}
			
			
			
				if(mysql_query(s,q))
		 		{ fprintf(stderr,"%s\n",mysql_error(s)); mysql_close(s); exit(1);}
				//printf("%s\n", q);
			
		}
	}

	//printf("%ld",n);
	mysql_close(s);
	return 0;
}
