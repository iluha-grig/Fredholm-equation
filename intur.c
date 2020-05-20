#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846264338327950288419716939937510L
#define N 2000 //parametr of algorithm

long double *slau(long n, long double (*matrix)[n + 1]);

static const int A = -20, B = 20; //parametrs of algorithm

long double g1 (long double x)
{
	x = fabs(x);
	x = -x;
	return 1.0L + exp(x) / (3.0L * (1.0L + exp(x)));
}

long double g2 (long double x)
{
	x = fabs(x);
	return 2.0L / 3.0L * exp((-2.0L) * x);
}

long double g3 (long double x)
{
	x = fabs(x);
	x = -x;
	return exp(x) / (3.0L * (1.0L + exp(x)));
}

long double f1 (long double x)
{
	return 1.0L + 1.0L / (x * x + 9.0L);
}

long double f2 (long double x)
{
	return 27.0L / (71.0L * (1.0L + x * x));
}

long double f3 (long double x)
{
	return 1.0L / (9.0L + x * x);
}

int main (int argc, char *argv[])
{
	if (argc == 1)
	{
		fprintf(stderr, "Should be one more argument!\n");
		exit(1);
	}
	long double (*matrix)[N] = malloc(N * N * sizeof(long double));
	long double *right = malloc(N * sizeof(long double));
	long double *res;
	long double xi, xk, xi1;
	double arg;
	char buf[100];
	FILE *f = fopen("fx.txt", "w");
	if (*argv[1] == '1')
	{
		long double kof = (long double)(B - A) / (PI * (long double)N);
		for (long i = 0; i < N; i++)
		{
			xi = (long double)A + (long double)i * (long double)(B - A) / (long double)N;
			fprintf(f, "%.6Lf\n", xi);
			right[i] = f2(xi) - f3(xi);
			for (long k = 0; k < N; k++)
			{
				xk = (long double)A + (long double)k * (long double)(B - A) / (long double)N;
				if (i == k)
				{
					matrix[i][k] = f1(xi) - kof;
				}
				else
				{
					matrix[i][k] = -kof / (1.0L + (xk - xi) * (xk - xi));
				}
			}
		}
	}
	else if (*argv[1] == '2')
	{
		long double kof = (long double)(B - A) / (long double)N;
		for (long i = 0; i < N; i++)
		{
			xi = (long double)A + (long double)i * (long double)(B - A) / (long double)N;
			fprintf(f, "%.6Lf\n", xi);
			right[i] = g2(xi) - g3(xi);
			for (long k = 0; k < N; k++)
			{
				xk = (long double)A + (long double)k * (long double)(B - A) / (long double)N;
				if (i == k)
				{
					matrix[i][k] = g1(xi) - kof;
				}
				else
				{
					matrix[i][k] = -kof * exp((-2.0L) * fabs(xk - xi));
				}
			}
		}
	}
	fclose(f);
	long double (*fullmatrix)[N + 1] = malloc(N * (N + 1) * sizeof(long double));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N + 1; j++)
		{
			if (j < N)
			{
				fullmatrix[i][j] = matrix[i][j];
			}
			else
			{
				fullmatrix[i][j] = right[i];
			}
		}
	}
	free(matrix);
	free(right);
	res = slau(N, fullmatrix);
	for (int i = 0; i < N; i++)
	{
		res[i] += 1.0L;
	}
	f = fopen("fy.txt", "w");
	for (int i = 0; i < N; i++)
	{
		fprintf(f, "%.6Lf\n", res[i]);
	}
	fclose(f);
	printf("Function found!\n");
	printf("Input dot in range from %d to %d. If you want to exit input 'exit'\n", A, B);
	scanf("%s", buf);
	while (buf[0] != 'e' || buf[1] != 'x')
	{
		arg = atof(buf);
		for (long i = 0; i < N - 1; i++)
		{
			xi = (long double)A + (long double)i * (long double)(B - A) / (long double)N;
			xi1 = (long double)A + (long double)(i + 1) * (long double)(B - A) / (long double)N;
			if (arg == xi)
			{
				printf("%Lf\n", res[i]);
				break;
			}
			else if (arg == xi1)
			{
				printf("%Lf\n", res[i + 1]);
				break;
			}
			else if (arg > xi && arg < xi1)
			{
				long double ans = res[i] + (arg - xi) / (xi1 - xi) * (res[i + 1] - res[i]);
				printf("%Lf\n", ans);
				break;
			}
		}
		scanf("%s", buf);
	}
	return 0;
}
