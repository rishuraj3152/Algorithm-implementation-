#include<stdio.h>
#include<time.h>
void tower(int n,char a,char c,char b)
{
	if(n==1)
	{
		printf("move disk 1 from %c to %c\n",a,c);
		return;	
	}
		tower(n-1,a,b,c);
		printf("move disk %d from %c to %c\n",n,a,c);
		tower(n-1,b,c,a);
}
int main(void)
{
	int n;
	double totaltime;
	printf("enter number of disks.\n");
	scanf("%d",&n);
	clock_t begin=clock();
	tower(n,'a','c','b');
	clock_t end=clock();
	totaltime=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("the time required is %f",totaltime);
	return 0;
}

















































