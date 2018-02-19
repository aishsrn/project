#include<stdio.h>
#include<math.h>
void ratios(char *annr,int temp,float rf)
{
	int i;
	float me=0,ss=0,sor,shar,co=0;	

	for(i=0;i<=temp;i++)
		me+=annr[i];
	me/=(temp+1.0);
	for(i=0;i<=temp;i++)
	ss+=pow(annr[i]-me,2);
	ss/=temp*1.0;
	ss=sqrt(ss);
	//printf("\nStddev:%f",ss);
	shar=(annr[temp]-rf)/ss;
	printf("\nSharpe ratio:%f",shar);
	me=0;ss=0;
	for(i=0;i<=temp;i++)
		if(annr[i]<0) {me+=annr[i]; co++;}
	me/=co;
	for(i=0;i<=temp;i++)
		if(annr[i]<0) ss+=pow(annr[i]-me,2);
	ss/=co;
	ss=sqrt(ss);
	sor=(annr[temp]-rf)/ss;
	printf("\nSortino ratio:%f",sor);
}
