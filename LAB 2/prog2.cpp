#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {

	int z;
	printf("Size\t\tT1\t\t\tT2\t\t\tT4\t\t\tT8");
	for (z = 50; z <= 1000; z = z = z + 50)
	{
		printf("\n%d\t", z);
		int** arr1, **arr2, **arr3;
		int size = z;
		int i, j, k;

		// Init
		arr1 = (int**)malloc(size * sizeof(int*));
		for (i = 0; i < size; i++)
			arr1[i] = (int*)malloc(size * sizeof(int));

		arr2 = (int**)malloc(size * sizeof(int*));
		for (i = 0; i < size; i++)
			arr2[i] = (int*)malloc(size * sizeof(int));

		arr3 = (int**)malloc(size * sizeof(int*));
		for (i = 0; i < size; i++)
			arr3[i] = (int*)malloc(size * sizeof(int));

		// Assigning values
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++)
				arr1[i][j] = (i + 1) * (j + 1);
		}

		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++)
				arr2[i][j] = (i + 1) * (j + 1);
		}

		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++)
				arr3[i][j] = 0;
		}
		for (int t = 1; t <= 8; t = t * 2)
		{
			double start = omp_get_wtime();

#pragma omp parallel for private(j, k) num_threads(t)
			// Multiplication
			for (i = 0; i < size; i++) {
				for (j = 0; j < size; j++) {
					int sum = 0;
					for (k = 0; k < size; k++) {
						sum += arr1[i][k] * arr2[k][j];
					}
					arr3[i][j] = sum;
				}
			}
			double stop = omp_get_wtime();
			printf("%lfs\t\t", stop - start);
		}

		/*for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++)
			{
				printf("%d", arr3[i][j]);
				printf("\t\t");

			}
			printf("\n");
		}*/
	}
}