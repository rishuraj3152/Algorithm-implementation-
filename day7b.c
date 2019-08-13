#include<stdio.h>
#include<stdlib.h>
int max(int a,int b)
{
	if(a>b)return a;
	else return b;
}
int main(void)
{
	int *p,*w,**t,i,j,n,m,x,left;
	FILE *fp;
	fp=fopen("day7b_input.txt","r");
	fscanf(fp,"%d %d",&n,&m);
	p=(int*)malloc((n+1)*sizeof(int));
	w=(int*)malloc((n+1)*sizeof(int));
	t=(int**)malloc((n+1)*sizeof(int*));
	for(i=0;i<=n;i++)
	{
		t[i]=(int*)malloc((m+1)*sizeof(int));
		t[i][0]=0;
	}
	p[0]=0;w[0]=0;
	for(i=1;i<=n;i++)
		fscanf(fp,"%d",&p[i]);
	for(i=1;i<=n;i++)
		fscanf(fp,"%d",&w[i]);
	for(j=0;j<=m;j++)t[0][j]=j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(i==1)
			{
				if(j<w[i])t[i][j]=0;
				else t[i][j]=p[i];
			}
			else if(j<w[i])t[i][j]=t[i-1][j];
			else
			{
				t[i][j]=max(p[i]+t[i-1][j-w[i]],t[i-1][j]);
			}
			//printf("%d\n",t[i][j]);
		}
		
	}
	fclose(fp);
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=m;j++)
		{
			printf("%d\t",t[i][j]);
		}
		printf("\n");
	}
	printf("the maximum value the thief can store is %d",t[n][m]);
	return 0;
}
