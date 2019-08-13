#include<stdio.h>
#include<stdlib.h>
float *r;int *inx,*p,*w;
int partition(float *r,int beg,int end)
{
	int i,j,pindex=beg+1,temp1,temp2,temp3;
	float pivot,temp;
	pivot=r[beg];
	for(i=beg+1;i<=end;i++)
	{
		if(r[i]<pivot)
		{
			temp=r[i];
			temp1=inx[i];
			temp2=p[i];
			temp3=w[i];
			r[i]=r[pindex];
			inx[i]=inx[pindex];
			p[i]=p[pindex];
			w[i]=w[pindex];
			r[pindex]=temp;
			inx[pindex]=temp1;
			p[pindex]=temp2;
			w[pindex]=temp3;
			pindex++;
		}
	}
	temp=r[pindex-1];
	temp1=inx[pindex-1];
	temp2=p[pindex-1];
	temp3=w[pindex-1];
	r[pindex-1]=r[beg];
	inx[pindex-1]=inx[beg];
	p[pindex-1]=p[beg];
	w[pindex-1]=w[beg];
	r[beg]=temp;
	inx[beg]=temp1;
	p[beg]=temp2;
	w[beg]=temp3;
	return pindex-1;
}
void sort(float *r,int beg,int end)
{
	int q;
	if(beg<end)
	{
		q=partition(r,beg,end);
		sort(r,beg,q-1);
		sort(r,q+1,end);	
	}
}
int main(void)
{
	int i,n,m,x,left;
	float res;
	FILE *fp;
	fp=fopen("day7_input.txt","r");
	fscanf(fp,"%d %d",&n,&m);
	p=(int*)malloc(n*sizeof(int));
	w=(int*)malloc(n*sizeof(int));
	r=(float*)malloc(n*sizeof(float));
	inx=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&p[i]);
	for(i=0;i<n;i++)
	{	fscanf(fp,"%d",&w[i]);
		r[i]=(float)p[i]/w[i];
		inx[i]=i+1;
	}
	fclose(fp);
	sort(r,0,n-1);
	i=n-1;left=m;x=0;res=0;
	while(x<m)
	{
		if(w[i]<=left)
		{
			res=res+p[i];
			printf("\n1.00 of object %d\n",inx[i]);
			x=x+w[i];
			left=left-w[i];
			inx[i]=0;
		}
		else if(w[inx[i]]>left)
		{
			printf("\n%f of object %d\n",(float)left/w[i],inx[i]);
			res=res+r[i]*left;
			x=x+left;
			inx[i]=0;
		}
		i--;
	}
	for(i=0;i<n;i++)
	{
		if(inx[i]!=0)
		printf("\n%d is not required.\n",inx[i]);
	}
	printf("the total value of stolen item is %f",res);
	return 0;
}
