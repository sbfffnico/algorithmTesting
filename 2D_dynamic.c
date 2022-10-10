#include <stdio.h>
#include <stdlib.h>

void assign(double** arr, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      arr[i][j] = i + j;
    }
  }
}

int main(void) {
  int n = 5;

  double **matrix = (double **)malloc(n*sizeof(double *));

  for (int i = 0; i < n; i++) {
    matrix[i] = (double *)malloc(n*sizeof(double));
  }

  assign(matrix, n);

  // print
  for(int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%3.2f  ", matrix[i][j]);
    }
    printf("\n");
  }

  // deallocate memory
  for(int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return 0;
}