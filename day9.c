#include<stdio.h>
#include<stdlib.h>
int w[10][10],n,e=14;
struct node
{
	int u;
	int v;
	int w;
}edge[14],a[14];
struct set
{
	int parent;
	int counter;
}s[10];
int partition(struct node edge[],int beg,int end)
{
	int i,j,pindex=beg;	
	struct node pivot,temp;
	pivot=edge[beg];
	for(j=beg+1;j<=end;j++)
	{
		if(edge[j].w<pivot.w)
		{
			temp=edge[j];
			edge[j]=edge[pindex];
			edge[pindex]=temp;
			pindex++;		
		}
	}
	temp=pivot;
	pivot=edge[pindex];	
	edge[pindex]=temp;
	return pindex;
}
void quicksort(struct node edge[],int beg,int end)
{
	int q;
	if(beg<end)
	{
		q=partition(edge,beg,end);
		quicksort(edge,beg,q-1);
		quicksort(edge,q+1,end);
	}
}
int find(int i)
{
	if(s[i].parent==-1)return i;
	return find(s[i].parent);
}
void unionn(int x,int y)
{
	int xset,yset;
	xset=find(x);
	yset=find(y);
	s[xset].parent=yset;
}
void kruskal()
{
	int j=0,i,count=0,sum=0;
	for(i=1;i<10;i++)
	{
		s[i].parent=-1;
		s[i].counter=0;
	}
	quicksort(edge,0,n-1);
	for(i=0;i<e;i++)printf("%d\t%d\t%d\n",edge[i].u,edge[i].v,edge[i].w);
	a[j++]=edge[0];
	unionn(edge[0].u,edge[0].v);
	for(i=1;i<e;i++)
	{
		if(find(edge[i].u)!=find(edge[i].v))
		{
			count++;
			a[j++]=edge[i];
			unionn(edge[i].u,edge[i].v);
		}
		if(count==n-1)break;
	}
	printf("the edges of MST are\n");
	for(i=0;i<j;i++)
	{	printf("%d\t%d\t%d\n",a[i].u,a[i].v,a[i].w);
		sum=sum+a[i].w;}
	printf("the total weight of mst is %d",sum);
}
int main()
{
	int i=0,a,b,c;
	FILE *fp;
	fp=fopen("day8_input.txt","r");
	fscanf(fp,"%d",&n);
	while(fscanf(fp,"%d%d%d",&a,&b,&c)!=EOF)
	{
		edge[i].u=a;
		edge[i].v=b;
		edge[i].w=c;
		i++;
	}
	kruskal();
	fclose(fp);
	return 0;
}
	
