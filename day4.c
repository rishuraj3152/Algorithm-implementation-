#include<stdio.h>
#include<stdlib.h>
int** matrix_chain_order(int *p,int n,int **m,int **s)
{
	int i,j,k,q=0,l;
	for(l=2;l<=n;l++)
	{
		for(i=1;i<=n-l+1;i++)
		{
			j=i+l-1;
			m[i][j]=100000000;
			for(k=i;k<=(j-1);k++)
			{
				q=m[i][k]+m[k+1][j]+(p[i-1]*p[k]*p[j]);
				if(q<m[i][j])
				{
					m[i][j]=q;
					printf("%d\t",k);
					s[i][j]=k;
				}
			}
		}
	}
	return s;
}
void print_optimal_parens(int **s, int i,int j)
{
	if(i==j)printf("m%d",i-1);
	else
	{
		printf("(");
		print_optimal_parens(s,i,s[i][j]);
		print_optimal_parens(s,s[i][j]+1,j);
		printf(")");
	}
}
int main(void)
{
	int i,n,j,*p,**m,**s;
	printf("enter the no. of matrices to be multiplied.\n");
	scanf("%d",&n);
	p=(int*)calloc(n+1,sizeof(int));
	m=(int**)calloc(n+1,sizeof(int*));
	s=(int**)malloc(n*sizeof(int*));
	for(i=0;i<=n;i++)
		m[i]=(int*)calloc(n,sizeof(int));
	for(i=0;i<=n;i++)
		s[i]=(int*)malloc(n*sizeof(int));
	printf("enter the sequence of dimensions.\n");
	for(i=0;i<=n;i++)
		scanf("%d",&p[i]);
	s=matrix_chain_order(p,n,m,s);
	print_optimal_parens(s,1,n);
	printf("\nthe multiplication matrix M is \n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{printf("%d\t",m[i][j]);}
		printf("\n");
	}
	printf("the intermediate element matrix S is \n");
	for(i=1;i<n;i++)
	{
		for(j=2;j<=n;j++)
			printf("%d\t",s[i][j]);
		printf("\n");
	}
	

	return 0;
}
