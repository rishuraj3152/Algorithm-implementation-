#include<stdio.h>
#include<stdlib.h>
int a[10][10],*visited,*flag,n,cost=0,l=1,k=1,*path;
void get()
{
	int i,j;
	printf("enter no of cities.\n");
	scanf("%d",&n);
	visited=(int*)malloc(n*sizeof(int));
	printf("enter cost matrix.\n");
	for(i=0;i<n;i++)
	{
		printf("enter elements of row %d\n",i+1);
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
		visited[i]=0;
	}
	printf("\nthe cost matrix is \n");
	for(i=0;i<n;i++)
	{
		printf("\n\n");
		for(j=0;j<n;j++)
			printf("\t%d",a[i][j]);
	}
}
int *del(int *ar,int j,int size)
{
	int i,k,loc;
	int *a;
	a=(int*)malloc((size-1)*sizeof(int));
	for(i=0;i<size;i++)
	{
		if(ar[i]==j)
		{
			loc=i;
			for(k=i;k<(size-1);k++)
			{
				a[k]=ar[k+1];
			}
		}
	}
	for(k=0;k<loc;k++)
	{
		a[k]=ar[k];
	}
	return a;
}
int g(int temp,int p,int *arr,int size)
{
	int min=999,val,*narr,j,loc;
	narr=(int*)malloc((size-1)*sizeof(int));
	if(size==1)
	{
		printf("%d\n",temp);
		if((a[temp][p]+a[p][arr[0]]+a[arr[0]][0])<(a[temp][arr[0]]+a[arr[0]][p]+a[p][0]))
		{
			if(flag[p]==0)
			{
				visited[k++]=arr[0];
				visited[k++]=p;flag[p]=1;flag[arr[0]]=1;
			}
		}
		else
		{
			if(flag[arr[0]]==0)
			{
				visited[k++]=p;
				visited[k++]=arr[0];flag[p]=1;flag[arr[0]]=1;
			}
		}
		return (a[p][arr[0]]+a[arr[0]][0]);
	}
	else
	{
		for(j=0;j<size;j++)
		{
			val=0;
			narr=del(arr,arr[j],size);
			val=a[p][arr[j]]+g(p,arr[j],narr,size-1);
			if(val<min)
			{
				min=val;
				if(flag[p]==0)
				{
					visited[k++]=p;
					flag[p]=1;
				}
			}
		}
	return min;
	}
}
int main(void)
{
	int *v,*p,i;
	get();
	printf("\nlets say the starting and ending vertex is 0.\n");
	v=(int*)calloc(n,sizeof(int));
	visited=(int*)calloc(10,sizeof(int));
	flag=(int*)calloc(n,sizeof(int));
	for(i=0;i<n;i++)v[i]=i;
	p=del(v,0,n);
	cost=g(0,0,p,n-1);
	printf("the path of salesman is\n");
	for(i=n;i>=1;i--)	
	printf("%d-->",visited[i]);
	printf("%d",visited[i]);
	printf("the minimum cost is %d",cost);
	return 0;
}
