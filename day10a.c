#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
#define inf 999
int stack[10],w[9][9],top=-1,n,*deg,**adj,*visited,*white,*grey,*black,*parent;
void push(int item)
{
	if(top==SIZE)
	printf("stack overflow.\n");
	else
		stack[++top]=item;
}
int pop()
{
	int temp1;
	if(top<0){printf("stack underflow.\n");return 0;}
	else
	{	
		temp1=stack[top];
		top--;
		return temp1;
	}
}
void topsort(int temp1)
{
	int i,flag=0,temp2;
	visited[temp1]=1;
	for(i=1;i<=deg[temp1];i++)
	{
		if(visited[adj[temp1][i]]==0)flag=1;
	}
	if(deg[temp1]==0)push(temp1);
	else if(flag==0)push(temp1);
	else
	{
		for(i=1;i<=deg[temp1];i++)
		{
			if(visited[adj[temp1][i]]==0)
			{
				temp2=adj[temp1][i];
				topsort(temp2);
			}
		}
		push(temp1);
	}
}
void dag(int v)
{
	int flag=0,i,temp2,loop,k;
	grey[v]=1;
	white[v]=1;
	for(i=1;i<=deg[v];i++)
	{
		if(black[adj[v][i]]==0)flag=1;
	}
	if(deg[v]==0){black[v]=1;grey[v]=0;}
	else if(flag==0)
	{
		black[v]=1;grey[v]=0;
	}
	else
	{
		for(i=1;i<=deg[v];i++)
		{
			if(grey[adj[v][i]]!=0)
			{
					parent[adj[v][i]]=v;
					printf("there is a cycle in the graph which is following.\n");
					loop=v;
					while(visited[loop]==0)
					{
						printf("%d<--",loop);
						visited[loop]=1;
						loop=parent[loop];
					}
					printf("%d",v);
					exit(0);
			}
			else if(black[adj[v][i]]==0)
			{
				parent[adj[v][i]]=v;
				temp2=adj[v][i];
				dag(temp2);
			}
		}
		black[v]=1;
		grey[v]=0;
	}
}
int main(void)
{
	int i=0,j=1,a,b,c,temp,garbage,start,store,v;
	FILE *fp;
	fp=fopen("day10a_input.txt","r");
	fscanf(fp,"%d",&n);
	printf("enter the starting vertex within range.\n");
	scanf("%d",&temp);
	adj=(int**)malloc((n+1)*sizeof(int*));
	deg=(int*)calloc(n+1,sizeof(int));
	black=(int*)calloc(n+1,sizeof(int));
	grey=(int*)calloc(n+1,sizeof(int));
	white=(int*)calloc(n+1,sizeof(int));
	parent=(int*)calloc(n+1,sizeof(int));
	visited=(int*)calloc(n+1,sizeof(int));
	while(fscanf(fp,"%d%d",&a,&b)!=EOF)
	{
		deg[a]=deg[a]+1;
		w[a][b]=1;
		//deg[b]=deg[b]+1;
	}
	for(i=0;i<=n;i++)
	{
		adj[i]=(int*)malloc((deg[i]+1)*sizeof(int));
		adj[i][0]=i;	
	}
	rewind(fp);
	fscanf(fp,"%d",&garbage);
	while(fscanf(fp,"%d%d",&a,&b)!=EOF)
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
	parent[temp]=-1;
	dag(temp);
	for(i=1;i<=n;i++)
	{
		if(white[i]==0)dag(i);
	}
	for(i=0;i<=n;i++)visited[i]=0;
	topsort(temp);
	for(i=1;i<=n;i++)
	{
		if(visited[i]!=1)
			topsort(i);
	}
	printf("the topological sorting order.\n");
	while(top!=-1)
	{
		temp=pop();
		printf("%d\t",temp);
	}
	return 0;
}
