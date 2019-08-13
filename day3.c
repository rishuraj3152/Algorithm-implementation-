 #include<stdio.h>
#include<stdlib.h>
void insert_by_priority(int);
void delete_by_priority(int);
void check(int);
int *list,n;
int front,rear,comp=0;
void insert_by_priority(int data)
{
	if(rear>=n-1)
		return;
	if((front==-1)&&(rear=-1))
	{
		front++;
		rear++;
		list[rear]=data;
		return;
	}
	else
		check(data);
	rear++;
}
void check(int data)
{
	int i,j;
	for(i=0;i<=rear;i++)
	{
		if(data>=list[i])
		{
			for(j=rear+1;j>i;j--)
				list[j]=list[j-1];
			list[i]=data;
			return;
		}
	}
	list[i]=data;
}

void heapify(int *list,int size,int top)
{
		int temp,child1,child2,biggestchild;
		while(1)	
		{
			child1=2*top+1;
			child2=2*top+2;
			if(child1>=size)break;
			if(child2>=size || list[child1]>=list[child2])
			{comp++;biggestchild=child1;}
			else
			{comp++;biggestchild=child2;}
			if(list[biggestchild]<=list[top])
			{break;}
			comp++;
			temp=list[top];
			list[top]=list[biggestchild];
			list[biggestchild]=temp;
			top=biggestchild;
		}
}
void heapsort(int *list,int n)
{
	int top,temp;
	for(top=n/2;top>0;top--)heapify(list,n,top);
	for(top=n-1;top>0;top--)
	{
		temp=list[top];
		list[top]=list[0];
		list[0]=temp;
		heapify(list,top,0);
	}
}
int main(void)
{
	int ch,a,i,j;
	float avg=0;
	front=rear=-1;
	srand(time(NULL));
	printf("enter the value of n.\n");
	scanf("%d",&n);
	list=(int*)calloc(n,sizeof(int));
	FILE *fp;
	for(j=0;j<=4;j++)
	{
		comp=0;
		fp=fopen("input3.txt","w");
		for(i=0;i<n;i++)fprintf(fp,"%d\t",rand()%100+1);fputs("\n",fp);
		fclose(fp);
		fp=fopen("input3.txt","r");
		do{
			fscanf(fp,"%d",&a);
			insert_by_priority(a);
		}
		while(!feof(fp));
		fclose(fp);
		heapsort(list,n);
		fp=fopen("output3.txt","w");
		for(i=0;i<n;i++)
		{
			fprintf(fp,"%d\t",list[i]);
		}
		fclose(fp);
		printf("the number of comparison is %d\n",comp);
		avg=avg+comp;
	}
	avg=avg/5;
	printf("the average number of comparison is:%f",avg);
	return 0;
}	
		
					
