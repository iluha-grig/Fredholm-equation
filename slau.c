#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double *slau(long n, long double (*matrix)[n+1])
{
	long qn;
	long double matr_max = (long double)0;
	long double exch, temp;
	long double *res;
	long double *resh = malloc(n * sizeof(long double));
	for (int i = 0; i < n; i++)
	{
		fprintf(stderr, "%d\n", i);
		for (int q = i; q < n; q++)
		{
			if (fabs(matrix[q][i]) > matr_max)
			{
				matr_max = fabs(matrix[q][i]);
				qn = q;
			}
		}
		matr_max = 0;
		for (int u = 0; u <= n; u++)
		{
			exch = matrix[i][u];
			matrix[i][u] = matrix[qn][u];
			matrix[qn][u] = exch;
		}
		temp = matrix[i][i];
		for (int j = i; j <= n; j++)
		{
			matrix[i][j] /= temp;
		}
		for (int j = i + 1; j < n; j++)
		{
			temp = matrix[j][i];
			for (int k = i; k <= n; k++)
			{
				matrix[j][k] -= temp * matrix[i][k];
			}
		}
		for (int i = n - 1; i >= 0; i--)
		{
			resh[i] = matrix[i][n];
			for (int j = i + 1; j < n; j++)
			{
				resh[i] -= matrix[i][j] * resh[j];
			}
		}
	}
	res = &resh[0];
	return res;
}
