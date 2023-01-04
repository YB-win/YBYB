#include<stdio.h>
int main ()
{int j,k,i;
for(j=1;j<=25;j++)
{
	for(i=1;i<=25-j;i++)
	printf(" ");
	for(k=1;k<=2*j-1;k++)
	printf("*");
	printf("\n");
 } 
	
	return 0;
}
