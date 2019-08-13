#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*int partition(long long int *arr,long long int beg,long long int end)
{
	long long int i,j,pindex=beg,pivot,temp;
	pivot=arr[beg];
	for(j=pindex+1;j<end;j++)
	{
		if(arr[j]<pivot)
		{
			temp=arr[j];
			arr[j]=arr[pindex];
			arr[pindex]=temp;
			pindex++;		
		}
	}
	temp=pivot;
	pivot=arr[pindex];	
	arr[pindex]=temp;
	return pindex;
}*/
int partition(long long int *arr,long long int beg,long long int end)
{
	long long int i,j,pindex=beg,pivot,temp;
	pivot=arr[beg];
	for(j=beg+1;j<=end;j++)
	{
		if(arr[j]<pivot)
		{
			temp=arr[j];
			arr[j]=arr[pindex];
			arr[pindex]=temp;
			pindex++;		
		}
	}
	temp=pivot;
	pivot=arr[pindex];	
	arr[pindex]=temp;
	return pindex;
}
void quicksort(long long int *arr,long long int beg,long long int end)
{
	long long int q;
	if(beg<end)
	{
		q=partition(arr,beg,end);
		quicksort(arr,beg,q-1);
		quicksort(arr,q+1,end);
	}
}
int main(void)
{
	long long int *arr,n,i;
	clock_t beg,end;
	double timetaken;	
	srand(time(NULL));
	FILE *fp;
	fp=fopen("input.txt","w");
	printf("enter the value of n.\n");
	scanf("%lld",&n);
	arr=(long long int*)calloc(n,sizeof(long long int));
	for(i=n;i>0;i--)
		fprintf(fp," %lld",i);
	fclose(fp);
	fp=fopen("input.txt","r");
	i=0;
	do{
		fscanf(fp,"%lld",&arr[i++]);
	}while(!feof(fp));
	fclose(fp);
	//for(i=0;i<n;i++)printf("%lld\n",arr[i]);
	beg=clock();	
	quicksort(arr,0,n-1);
	end=clock();
	timetaken=(double)(end-beg)/CLOCKS_PER_SEC;
	printf("the time taken is %lf",timetaken);
	//for(i=0;i<n;i++)printf("%lld\n",arr[i]);
	fp=fopen("output.txt","w");
	for(i=0;i<n;i++)
		fprintf(fp," %lld",arr[i]);
	fclose(fp);
	return 0;
}
	
