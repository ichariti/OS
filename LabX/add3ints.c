#include <stdio.h>

int add(int *a, int *b, int *c){
	int sum=*a+*b+*c;
	return sum;
}

int main(){
	int x,y,z,s;
	printf("Enter the first integer:\n");
	scanf("%d", &x);
	printf("Enter the second integer:\n");
	scanf("%d", &y);
	printf("Enter the third integer:\n");
	scanf("%d", &z);
	s=add(&x,&y,&z);
	printf("Sum: %d\n",s);
	return 0;
}
