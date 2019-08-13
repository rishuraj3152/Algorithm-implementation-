#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int comp=0;
void permute()
{
	int i=0,x,a[10],a2[10],count=0,flag=0;
	FILE *fp;
	srand(time(NULL));
	fp=fopen("input2.txt","w");
	while(i<9)
		{
			int r=rand()%9;
			for(x=0;x<i;x++)
			{
				if(a[x]==r)break;
			}
			if(x==i)a[i++]=r;
		}
	do
	{
		i=0;flag=0;
		while(i<9)
		{
			int r=rand()%9;
			for(x=0;x<i;x++)
			{
				if(a2[x]==r)break;
			}
			if(x==i)a2[i++]=r;
		}
		for(i=0;i<9;i++){if(a[i]==a2[i])flag=1;}
		if(flag==0)
		{
			for(i=0;i<9;i++)fprintf(fp,"%d",a2[i]);
			fputs("\n",fp);
			count++;
		}
		for(i=0;i<9;i++){a[i]=a2[i];}	
	}	
	while(count<362880);
	fclose(fp);
}
int partition(int *arr,int p,int r)
{
	int pivotindex=p+rand()%(r-p+1);
	int i=p-1,j,pivot,temp;
	pivot=arr[pivotindex];
	temp=arr[pivotindex];
	arr[pivotindex]=arr[r];
	arr[r]=temp;
	for(j=p;j<r;j++)
	{
		comp++;
		if(arr[j]<pivot)
		{
			i++;
			temp=arr[j];
			arr[j]=arr[i];
			arr[i]=temp;	
		}
	}
	temp=arr[r];
	arr[r]=arr[i+1];	
	arr[i+1]=temp;
	return i+1;
}
void quicksort(int *arr,int beg,int end)
{
	int q;
	if(beg<end)
	{
		q=partition(arr,beg,end);
		quicksort(arr,beg,q-1);
		quicksort(arr,q+1,end);
	}
}
int main(void)
{
	int n,i=0,x;
	int a[10],a2[10];
	double timetaken,avg=0;
	char buf[1000];
	FILE *fp,*fp1;
	srand(time(NULL));
	clock_t beg,end;
	permute();
	fp=fopen("input2.txt","r");
	if(!fp)return 1;
	while(fgets(buf,1000,fp)!=NULL)
	{
		for(i=0;i<9;i++)
			{
				a[i]=buf[i]-48;
				//printf("%d\t",a[i]);
			}comp=0;
			beg=clock();
			quicksort(a,0,8);
			end=clock();
			//for(i=0;i<10;i++)printf("%d\t",a[i]);
			fp1=fopen("output2.txt","a");
			for(i=0;i<9;i++)fprintf(fp1,"%d",a[i]);
			fputs("\n",fp1);
			fclose(fp1);
			timetaken=(double)(end-beg)/CLOCKS_PER_SEC;
			printf("time=%lf\tcomparison=%d",timetaken,comp);
			avg=avg+comp;
			printf("\n");
	}
	avg=avg/362880;
	printf("the average is %lf",avg);
	fclose(fp);
	return 0;
}

	
