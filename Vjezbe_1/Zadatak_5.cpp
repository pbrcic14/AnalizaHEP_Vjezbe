#include <stdio.h>

int _my_cube(int num)
{
	return num*num*num;
}

int main()
{
	int num, num3;
	printf("Type a number: ");
	scanf("%d", &num);
	num3 = _my_cube(num);
	printf("The cube is: %d\n", num3);
	return 0;
}
