#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h>
#include <float.h>

#define _USE_MATH_DEFINES

void greedyHeuristic(double** matrix, long long int vertices, char* bestPath, double* cost) {
  int visited[vertices];
  int k, kSum;
  double shortest;
  double sum = 0.00;
  int count = 0;
  int print = 0; // 1 for true, 0 for false , bool not recognized as data type
  //char* path[vertices - 1];

  if (print) {
    printf("best path: 0");
  }
  for (int i = 0; i < vertices; i++) {
    visited[i] = 0;
  }

    for (int i = 0; kSum != vertices;) {
        shortest = DBL_MAX;
        kSum = 0;
        visited[0] = 1;
        for (int j = 0; j < vertices; j++) {
          if(i == j || visited[j] == 1) {
            // do nothing
          }
          /*
          else if(visited[j] == 1) {
            printf("j is %d\n", j);
          }
          */
          else if (matrix[i][j] < shortest){
            shortest = matrix[i][j];
            k = j;
          }
        }
        sum += shortest;
        visited[k] = 1;
        //bestPath[count] = k+'0';
        count++;
        i = k;
        if(print) {
          printf("%d", k);
        }
        for (int z = 0; z < vertices; z++) {
          if (visited[z] == 1) {
            kSum++;
          }
        }
        //printf("kSum: %d\n", kSum);
      }
      sum += matrix[k][0];
      *cost = sum;
      if(print) {
        printf("0\n");
      }
      //printf("%s\n", bestPath);
  /*
  printf("Visited of: ");
  for (int i = 0; i < vertices; i++) {
    printf("[%d]:%d ", i, visited[i]);
  }
  printf("\n");
  */
}

// full string size is equal to number of vertices by adding 0 starting and ending
void fullPathCreation(char* bestPath, long long int vertices, char* fullPath) {
  
  fullPath[0] = '0';
  for (int i = 0; i < vertices - 1; i++){
    //printf("i is: %d\n", i);
    fullPath[i+1] = bestPath[i];
  }
  fullPath[vertices] = '0';
  
  /*
  for (int i = 0; i < vertices - 1; i++) {
    printf("%c ", bestPath[i]);
  }
  printf("\n");
  /*
  fullPath[0] = '0';
  fullPath[1] = '0';
  fullPath[2] = '0';
  fullPath[3] = '0';
  fullPath[4] = '0';
  */
}

void reverseStr(char* fullPath, char* reversal, long long int vertices) {
  int j = 0;
  for(int i = vertices; i >= 0; i--) {
    reversal[j] = fullPath[i];
    j++;
  }
}

void bruteForce(double** matrix, long long int vertices, char* currentPerm, char* bestPath, double* cost) {
  double sum = 0;
  //printf("%s\n", currentPerm);
  //printf("Adding to sum: %f\n", matrix[0][currentPerm[0]-'0']);
  sum += matrix[0][currentPerm[0]-'0'];
  //printf("sum is %f\n", sum);
  for(int i = 0; i < vertices - 1 - 1; i++) {
    //printf("Adding to sum: %f\n", matrix[currentPerm[i]-'0'][currentPerm[i+1]-'0']);
    sum+= matrix[currentPerm[i]-'0'][currentPerm[i+1]-'0'];
  }
  //printf("Adding to sum: %f\n", matrix[currentPerm[vertices-2]-'0'][0]);
  sum += matrix[currentPerm[vertices-2]-'0'][0];
  //printf("sum is %f\n", sum);

  if (sum < *cost) {
    *cost = sum;
    strcpy(bestPath, currentPerm);
  }
}

void swap(char *x, char *y) {
  char tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

// permutation algorithm of a string from https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
void permutate(double** matrix, long long int vertices, char *toPerm, int start, int end, char *bestPath, double* cost){
  if (start == end) {
    //printf("%s\n", toPerm);
    bruteForce(matrix, vertices, toPerm, bestPath, cost);
  }
  else {
    for (int i = start; i <= end; i++) {
      swap((toPerm+start), (toPerm+i));
      permutate(matrix, vertices, toPerm, start+1, end, bestPath, cost);
      swap((toPerm+start), (toPerm+i));
    }
  }
}

void Generate4By4StandardCostMatrix(double ** matrix, long long int vertices) {
  matrix[0][0] = 0;
  matrix[1][1] = 0;
  matrix[2][2] = 0;
  matrix[3][3] = 0;

  matrix[0][1] = 5;
  matrix[1][0] = 5;

  matrix[0][2] = 8;
  matrix[2][0] = 8;

  matrix[0][3] = 2;
  matrix[3][0] = 2;

  matrix[1][2] = 6;
  matrix[2][1] = 6;

  matrix[1][3] = 3;
  matrix[3][1] = 3;

  matrix[2][3] = 1;
  matrix[3][2] = 1;
}

void GenerateTestCaseCostMatrix(double** matrix, long long int vertices) {
  for (int i = 0; i < vertices; i++) {
    for (int j = i; j < vertices; j++) {
      if (i == j) {
        matrix[i][j] = 0;
      }
      else {
        if (i % 2 == 0) {
          matrix[i][j] = 2;
          matrix[j][i] = matrix[i][j];
        }
        else {
          matrix[i][j] = i;
          matrix[j][i] = matrix[i][j];
        }
      }
    }
  }
  
}

void GenerateRandomCostMatrix(double** matrix, long long int vertices, int maximumEdgeCost) {
  srand(time(NULL));

  for (int i = 0; i < vertices; i++) {
    //printf("i is %d\n", i);
    //printf("j is ");
    for (int j = i; j < vertices; j++) {
      //printf("%d ", j);
      if (i == j) {
        matrix[i][j] = 0;
      }
      else {
        matrix[i][j] = rand() % (maximumEdgeCost + 1);
        matrix[j][i] = matrix[i][j];
      }
    }
    //printf("\n");
  }
}

void printCostMatrix(double **matrix, long long int vertices) {
  printf("-----------\nCOST MATRIX\n----------\n");
  for (int i = 0; i < vertices; i++) {
    for (int j = 0; j < vertices; j++) {
      printf("%8.2f ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("------------------------------------\n");
}

void printVerticesI(int vertices, int* x, int* y) {
  for (int i = 0; i < vertices; i++) {
    printf("(%d,%d) ", x[i], y[i]);
    
  }
  printf("\n");
}

void GenerateRandomEuclideanCostMatrix(double** matrix, long long int vertices, int maxX, int maxY) {
  srand(time(NULL));
  
  int x[vertices];
  int y[vertices];

  for (int i = 0; i < vertices; i++) {
    x[i] = (rand() % (maxX + 1));
    y[i] = (rand() % (maxY + 1));
  }

  //printf("Test index 0: (%d, %d) ", verticesX[0], verticesY[0]);
  //printf("(%d, %d) ", verticesX[1], verticesY[1]);
  //printf("(%d, %d) ", verticesX[2], verticesY[2]);
  //printf("(%d, %d) ", verticesX[3], verticesY[3]);
  //printf("(%d, %d) ", verticesX[4], verticesY[4]);
  //printf("(%d, %d) ", verticesX[5], verticesY[5]);
  //printf("\n");
  printVerticesI(vertices, x, y);

  for (int i = 0; i < vertices; i++) {
    for (int j = i; j < vertices; j++){
      if (i == j) {
        matrix[i][j] = 0;
      }
      else {
        //printf("(%d, %d) vs (%d, %d)\n", verticesX[i], verticesY[i], verticesX[j], verticesX[j]);
        matrix[i][j] = pow(pow(x[i]-x[j], 2)+pow(y[i]-y[j],2),0.5);
        matrix[j][i] = matrix[i][j];
      }
    }
  }
}

void printVerticesD(long long int  vertices, double* x, double* y) {
  for (int i = 0; i < vertices; i++) {
    printf("#%d: (%1.2f,%1.2f) ", i, x[i], y[i]);
  }
  printf("\n");
}

// something wrong here
void randomizeVertices(int vertices, double* x, double* y) {
  srand(time(NULL));
  
  int randomIndex;
  double tmp;

  for (int j = 0; j < 100; j++) {
    for (int i = 0; i < vertices; i++) {

      randomIndex = (rand() % vertices - 1) + 1;

      tmp = x[randomIndex];
      x[randomIndex] = x[i];
      x[i] = tmp;

      tmp = y[randomIndex];
      y[randomIndex] = y[i];
      y[i] = tmp;
    }
  }
}

void GenerateRandomCircularGraphCostMatrix(double** matrix, long long int vertices, int radius) {
  double stepAngle = (2 * M_PI)/vertices, x[vertices], y[vertices];
  int print = 0; // 1 for true, zero for false
  //printf("\n%f\n", M_PI);
  for (int step = 0; step < vertices; step++) {
    x[step] = radius * sin(step * stepAngle);
    y[step] = radius * cos(step * stepAngle);
    //printf("(%1.2f,%1.2f) ", x, y);
  }
  //printf("\n");
  for (int i = 0; i < vertices; i++) {
    for (int j = i; j < vertices; j++){
      if (i == j) {
        matrix[i][j] = 0;
      }
      else {
        //printf("(%d, %d) vs (%d, %d)\n", verticesX[i], verticesY[i], verticesX[j], verticesX[j]);
        matrix[i][j] = pow(pow(x[i]-x[j], 2)+pow(y[i]-y[j],2),0.5);
        matrix[j][i] = matrix[i][j];
      }
    }
  }
  if (print) {
    if (vertices < 30) {
      printf("Original Circular Graph indices: \n");
      printVerticesD(vertices, x, y); // just print this to confirm original fastest answer
    }
  }
  
  randomizeVertices(vertices, x, y);
  if (print) {
    if (vertices < 30) {
      printf("Randomized Circular Graph indices: \n");
      printVerticesD(vertices, x, y);
    }
  }
  
  double expectedCost = 0.00;
  int j = 1;
  printf("Expected cost: ");
  for (int i = 0; i < vertices; i++) {
    if (j == vertices) {
      j = 0;
    }
    expectedCost += matrix[i][j];
    //printf("[%d][%d] = %1.2f", i, j, expectedCost);
    j++;
  }
  printf("%1.2f\n", expectedCost);

  for (int i = 0; i < vertices; i++) {
    for (int j = i; j < vertices; j++){
      if (i == j) {
        matrix[i][j] = 0;
      }
      else {
        //printf("(%d, %d) vs (%d, %d)\n", verticesX[i], verticesY[i], verticesX[j], verticesX[j]);
        matrix[i][j] = pow(pow(x[i]-x[j], 2)+pow(y[i]-y[j],2),0.5);
        matrix[j][i] = matrix[i][j];
      }
    }
  }
}

void print2DArray(double** matrix, long long int n) {
  for(int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%f ", matrix[i][j]);
    }
  }
}

void simple2DArray(double** matrix, long long int n){
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      matrix[i][j] = i + j;
    }
  }
}


// https://www.techiedelight.com/pass-2d-array-function-parameter/
int main (void) { 
  for (long long int n = 4; n < 400; n++) {
    printf("\n\n***************THE START*****************\n");

    printf("Number of vertices: %d\n", n);
  // allocate memory for array of pointers
  double **matrix = (double **)malloc(n*sizeof(double *));

  // allocate memory for each row
  for (int i = 0; i < n; i ++) {
    matrix[i] = (double *)malloc(n*sizeof(double));
  }

  char* path = (char *)malloc((n-1)*sizeof(char));

  char* bestPath = (char*)malloc((n-1)*sizeof(char));

  char* fullPath = (char*)malloc((n+1)*sizeof(char));

  char* revFullPath = (char*)malloc((n+1)*sizeof(char));

  double cost = DBL_MAX;

  // creates a string converted turn char into int equivalent
  for (int i = 0; i < n - 1; i++) {
    path[i] = (i+1) +'0';
  }

  for (int i = 0; i < n - 1; i++) {
    bestPath[i] = 'z';
  }
  /*
  if (n == 4) {
    printf("Standard 4x4\n");
    Generate4By4StandardCostMatrix(matrix, n);
    printCostMatrix(matrix, n);
    printf("\n");
  }
  */

  //printf("Random Cost Matrix\n");
  //GenerateRandomCostMatrix(matrix, n, 5);
  //printCostMatrix(matrix,n );
  //printf("\n");

  //printf("Random Euclidean Cost Matrix\n");
  //GenerateRandomEuclideanCostMatrix(matrix, n, 5, 5);
  //printCostMatrix(matrix,n );
  //printf("\n");

  //printf("Test Case Cost Matrix\n");
  //GenerateTestCaseCostMatrix(matrix, n);
  //printCostMatrix(matrix, n);
  //printf("\n");

  /*
  printf("Brute force version testing:\n");
  printf("Circular Graph Cost Matrix\n");
  GenerateRandomCircularGraphCostMatrix(matrix, n, 100);
  printCostMatrix(matrix, n);

  //printf("The real test\n");
  //permutate(path, 0, strlen(path)-1, bestPath, &cost);
  permutate(matrix, n, path, 0, strlen(path)-1, bestPath, &cost);
  printf("Cost: %1.2f, Best path: %s\n", cost, bestPath);
  fullPathCreation(bestPath, n, fullPath);
  reverseStr(fullPath, revFullPath, n);
  printf("Full path: %s or %s\n", fullPath, revFullPath);
  */

  printf("Greedy heuristic version testing:\n");
  printf("Circular Graph Cost Matrix\n");
  GenerateRandomCircularGraphCostMatrix(matrix, n, 100);
  if (n < 30) {
    printCostMatrix(matrix, n);
  }
  
  greedyHeuristic(matrix, n, bestPath, &cost);

  printf("Cost: %1.2f\n", cost);

  // deallocate memory
  for (int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);
  }

  printf("****************THE END******************\n");
  return 0;
}