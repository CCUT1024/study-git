#include <stdio.h>
int main() 
{
	int i, j, n, a[10][10], sum = 0;
	printf("请输入矩阵的阶数：");
	scanf("%d", &n);
	printf("请输入%d个整数：\n", n * n);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	for (j = n - 1; j >= 0; j--)
	{
		for (i = j; i >= 0; i--)
		sum += a[i][j];
	}
	printf ("主对角线上方所有元素之和（含主对角线元素）：%d\n", sum);
   return 0;
}
