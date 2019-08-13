#include<stdio.h>
#include<time.h>
int count=0;
long int power(int x,int n)
{
	int temp;
	count++;
	if(n==0)
	{
		
		return 1;
	}
	else if(n==1)
	{
				
		return x;
	}
	else
	{
		temp=power(x,n/2);
		if(n%2==0)
			return temp*temp;
		else
			return temp*temp*x;
	}
}
int main(void)
{
	int x,n;
	long long int res;
	clock_t beg,end;
	double totaltime;
	printf("enter x and n.\n");
	scanf("%d%d",&x,&n);
	beg=clock();
	res=power(x,n);
	end=clock();
	printf("the result of %d to power %d is %lld\n",x,n,res);
	printf("the number of comparison is %d\n",count);
	totaltime=(double)(end-beg)/CLOCKS_PER_SEC;
	printf("the time required is %lf\n",totaltime);
	return 0;
}
