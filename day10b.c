#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
#define inf 999
int stack[10],w[9][9],top=-1,n,*deg,**adj,*visited,*ind;
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
void display()
{
	int i;
	for(i=top;i>=0;i--)printf("%d\t",stack[i]);
}
void stcc(int temp1)
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
				stcc(temp2);
			}
		}
		push(temp1);
	}
}
void gt(int temp1)
{
	int i,flag=0,temp2;
	visited[temp1]=0;
	for(i=1;i<=deg[temp1];i++)
	{
		if(visited[adj[temp1][i]]==1)flag=1;//this time i m working with vertices visited as 0
	}
	if(deg[temp1]==0 || flag==0)printf("%d\n",temp1);
	else printf("%d-->",temp1);
	for(i=1;i<=deg[temp1];i++)
	{
		if(visited[adj[temp1][i]]==1)
		{
			temp2=adj[temp1][i];
			gt(temp2);
		}
	}
}
int main(void)
{
	int i=0,j=1,a,b,c,temp,garbage,start,store,v;
	FILE *fp;
	fp=fopen("day10b_input.txt","r");
	fscanf(fp,"%d",&n);
	printf("enter the starting vertex within range.\n");
	scanf("%d",&temp);
	start=temp;
	v=temp;
	adj=(int**)malloc((n+1)*sizeof(int*));
	deg=(int*)calloc(n+1,sizeof(int));
	visited=(int*)calloc(n+1,sizeof(int));
	ind=(int*)calloc(n+1,sizeof(int));
	while(fscanf(fp,"%d%d",&a,&b)!=EOF)
	{
		deg[a]=deg[a]+1;
		w[a][b]=1;
	}
	for(i=0;i<=n;i++)
	{
		adj[i]=(int*)malloc((deg[i]+1)*sizeof(int));
		adj[i][0]=i;	
	}
	printf("\n");
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
	stcc(temp);
	for(i=1;i<=n;i++)
	{
		if(visited[i]==0)stcc(i);
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j)w[i][j]=0;
			else if(w[i][j]!=1 && i!=j)
				w[i][j]=inf;
			printf("%d\t",w[i][j]);
		}
		printf("\n");
		deg[i]=0;
		ind[i]=1;
	}
	rewind(fp);
	fscanf(fp,"%d",&garbage);
	while(fscanf(fp,"%d%d",&a,&b)!=EOF)
	{
		deg[b]=deg[b]+1;
	}
	rewind(fp);
	fscanf(fp,"%d",&garbage);
	while(fscanf(fp,"%d%d",&a,&b)!=EOF)
	{
		adj[b][ind[b]++]=a;
	}
	printf("after reversal of the edges,the adjacency matrix are.\n");
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=deg[i];j++)
		{
			printf("%d\t",adj[i][j]);
		}
		printf("\n");
	}
	fclose(fp);
	printf("the strongly connected component are \n");
	while(top!=-1)
	{
		temp=pop();
		if(visited[temp]==1)
			gt(temp);
	}
	return 0;
}
