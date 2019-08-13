#include<stdio.h>
#include<stdlib.h>
#define inf 999
int n=0,w[6][6],*deg,**adj,count,temp;
struct node
{
	int vx;
	int key;
	int parent;
};
struct node *pq,*s;
void buildheap(struct node* pq,int n);
int isempty(struct node* pq,int n);
int isfull(struct node* pq,int n);
struct node dequeue(struct node* pq);
struct node* min_heapify(struct node* pq,int top,int size);
struct node* heapifyupward(struct node* pq,int temp);
struct node* init_single_source(struct node* pq,int temp);
struct node* heapifyupward(struct node* pq,int start)
{
	int parent,i;
	struct node temp1;
	if(start>1)
	{
		parent=start/2;
		for(i=1;i<=count;i++)
		{
			if(pq[i].vx==start)start=i;
			if(pq[i].vx==parent)parent=i;
		}
		if(pq[parent].key>pq[start].key)
		{
			temp1=pq[start];
			pq[start]=pq[parent];
			pq[parent]=temp1;
			heapifyupward(pq,parent);
		}
	}
	return pq;
}
struct node* init_single_source(struct node* pq,int temp)
{
	int i;
	pq=(struct node*)malloc((n+1)*sizeof(struct node));
	for(i=1;i<n+1;i++)
	{
		pq[i].vx=i;
		if(i==temp)pq[i].key=0;
		else
		{
			pq[i].key=inf;
		}
		pq[i].parent=-1;
	}
	return pq;
}
void buildheap(struct node* pq,int n)
{
	int i,index;
	index=n/2;
	for(i=index;i>=1;i--)
		pq=min_heapify(pq,i,n);
}
int isempty(struct node* pq,int n)
{
	if(n==0)return 1;
	else return 0;
}
int isfull(struct node* pq,int n)
{
	if(n==0)return 1;
	else return 0;
}
struct node dequeue(struct node* pq)
{
	struct node u;
	if(isempty(pq,n))printf("underflow.\n");
	else
	{
		u=pq[1];
		pq[1]=pq[count];
		count--;
		return u;
	}
}
struct node* min_heapify(struct node* pq,int i,int N)
{
	struct node temp1;
	int left=2*i;
	int right=2*i+1;
	int smallest;
	if(left<=N && pq[left].key<pq[i].key)
		smallest=left;
	else
		smallest=i;
	if(right<=N && pq[right].key<pq[smallest].key)
		smallest=right;
	if(smallest!=i)
	{
		temp1=pq[smallest];
		pq[smallest]=pq[i];
		pq[i]=temp1;
		pq=min_heapify(pq,smallest,N);
	}
	return pq;
}
struct node extract_min()
{
	int i;
	for(i=count/2;i>=1;i--)
	{
		pq=min_heapify(pq,i,count);
	}
	struct node u;
	u=dequeue(pq);
	return u;
}
struct node* relax(struct node* pq,struct node u,int v)
{
	int i,v2,flag=0;
	for(i=1;i<=count;i++)
	{
		if(pq[i].vx==v)
		{
			v2=i;
			flag=1;
		}
	}
	if(flag==0)return pq;
	if(pq[v2].key>(u.key+w[u.vx][v]))
	{
		pq[v2].key=u.key+w[u.vx][v];
		pq[v2].parent=u.vx;
	}
	return pq;
}
void dijkstra(int temp)
{
	struct node u,par;
	int path[5];
	int i=0,j,k,l,v,r=0,dis=0;
	pq=init_single_source(pq,temp);
	buildheap(pq,n);
	s=(struct node*)malloc(n*sizeof(struct node));
	while(count!=0)
	{
		u=extract_min();
		printf("extracted=%d\n",u.vx);
		s[r++]=u;
		for(j=1;j<=deg[u.vx];j++)
		{
			v=adj[u.vx][j];
			pq=relax(pq,u,v);
		}
		for(i=1;i<=count;i++)
		{
			printf("%d\t%d\t%d\n",pq[i].vx,pq[i].key,pq[i].parent);
		}
	}
	printf("the final set of vertices and their parents are\n");
	for(i=0;i<n;i++)
	{
		k=0;
		dis=0;
		par=s[i];
		//path[0]=temp;
		for(l=0;l<5;l++)path[l]=0;
		while(par.parent!=-1)
		{
			dis+=w[par.parent][par.vx];
			path[k++]=par.vx;
			for(j=0;j<n;j++)
			{
				if(s[j].vx==par.parent)
				{
					par=s[j];
				}
			}
			
		}
		printf("%d",temp);
		for(l=4;l>=0;l--)
		{
			if(path[l]!=0)
			printf("-->%d",path[l]);
		}	
		printf("distance=%d\n",dis);		
	}
}		
int main(void)
{
	int i=0,j=1,a,b,c,temp,garbage,start;
	FILE *fp;
	fp=fopen("day6_input.txt","r");
	fscanf(fp,"%d",&n);
	count=n;
	printf("enter the starting vertex within range.\n");
	scanf("%d",&temp);
	start=temp;
	adj=(int**)malloc((n+1)*sizeof(int*));
	deg=(int*)calloc(n+1,sizeof(int));
	while(fscanf(fp,"%d%d%d",&a,&b,&c)!=EOF)
	{
		w[a][b]=c;
		deg[a]=deg[a]+1;
	}
	for(i=0;i<=n;i++)
	{	adj[i]=(int*)malloc((deg[i]+1)*sizeof(int));
		adj[i][0]=i;
	}
	rewind(fp);
	fscanf(fp,"%d",&garbage);
	while(fscanf(fp,"%d%d%d",&a,&b,&c)!=EOF)
	{
		if(start!=a)j=1;
		adj[a][j++]=b;
		start=a;
	}	
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=deg[i];j++)
		{
			printf("%d\t",adj[i][j]);
		}
		printf("\n");
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j)w[i][j]=0;
			else if(w[i][j]==0 && i!=j)
				w[i][j]=inf;
			printf("%d\t",w[i][j]);
		}
		printf("\n");
	}
	fclose(fp);
	dijkstra(temp);
	return 0;
}


