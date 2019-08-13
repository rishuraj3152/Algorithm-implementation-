#include<stdio.h>
#include<math.h>
#include<time.h>
void hanoi(int n){
	int x,from, to;
	unsigned int i,j;
	for(x=1;x<(1<<n);x++)
	{
		from =(x &(x-1))%3;
		to = ((x|x-1)+1)%3;
		for(i=x,j=1;;i>>=1,j++){
			if(i&1)
				break;
		}
		printf("\nMove disc %d from %d to %d",j,from,to);

	}
	
}
int main(){
	int n;
	//clock_t begin = clock();
	printf("Enter n: ");
	scanf("%d",&n);
	clock_t begin = clock();
	hanoi(n);
	clock_t end = clock();
	double Ttime = (double)(end - begin)/CLOCKS_PER_SEC;
	printf("Total time: %lf",Ttime);
	return 0;
}
