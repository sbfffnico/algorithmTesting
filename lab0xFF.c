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
    //printf("best path: 0");
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
    //strcpy(bestPath, currentPerm);
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
  //printVerticesI(vertices, x, y);

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

// https://www.geeksforgeeks.org/c-program-for-factorial-of-a-number/
long long int factorial(long long int n) {
  if (n == 0) {
    return 1;
  }
  return n * factorial(n-1);
}

long long int expectedBruteForce(long long int n) {
  long long int nHalved = n/2;
  long long int top = factorial(n);
  long long int bottom = factorial(nHalved);
  long long int expected = top/bottom;

  return expected;
}

double logN(long long int N) {
  while (N > 1) {
    return 1 + logN(N/2);
  }
  return 0;
}

long long int expectedHeuristicInc(long long int n) {
  long long int nHalved = n/2;
  long long int top = logN(n);
  long long int bottom = logN(n/2);
  top = top * n;
  bottom = bottom * n/2;
  long long int expected = top/bottom;

  return expected;
}

void bruteForceTimer() {

    double trialsTime_max = 0.25; // in seconds (0.25)
    long long int trialsCount_max = 1000000,
                  N_min = 1,
                  N_max = 1000000000000, // adjust as needed, keep small for debugging ( 10000000 )
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial;

    long long int power = 0;
    double previousTimeTrialPeriod = 0;

	// If you are printing a results table directly, print your header line here.
	
  printf("N\t\t");
  printf("Time\t\t\t");
  printf("Experimental\t\t");
  printf("Expected\t\t\t");
  printf("\n");
  
  // for ( n=1; n<N_max; n=2*n )

	// start at 4 for tsm
    for ( n=4; n<N_max; n=n+1 ) {

        /********* any preparations, test input generation, to be used for entire trial set ********/

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

        GenerateRandomCostMatrix(matrix, n, 20);
              
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/
            

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //for(int x=0;x<1000000;x+=2) x--;
            
            permutate(matrix, n, path, 0, strlen(path)-1, bestPath, &cost);

            /******* do any "clean up" after running your algorithm ********/
            
            // get split time -- "split time" just means the total time so far for this trial set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h 
        }
        trialSetCount = trial; // value of trial when loop ends is how many we did
        trialSetTime = splitTime; // total time for trial set is the last split time
        averageTrialTime = trialSetTime / trialSetCount; // this is the average tiem per trial, including any prep/overhead

        /********* NOW DO A "DUMMY" TRIAL SET TO ESTIMATE THE OVERHEAD TIME ********/
        /* We can just repeat this trialSetCount times, which we know should be faster than above */
        
        splitTime=0.0;
        // get timestamp before set of dummy trials are run:
        trialSetStart = clock();
        for ( trial=0; trial < trialSetCount  && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/

            /**** DO NOT Call the algorithm function!!! ******/

            /******* do any "clean up" after running your algorithm ********/

            // get split time -- "split time" just means the total time so far for this tiral set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h ( seconds )
        }
        dummySetCount = trial; // value of trial when loop ends is how many we did, should be same as trialsSetCount
        dummySetTime = splitTime; // total time for dummy trial set is the last split time
        averageDummyTrialTime = dummySetTime / dummySetCount; // this is the average time per dummy trial, including any prep/overhead

        estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime; // should be a decent measurement of time taken to run your algorithm

        if (estimatedTimePerTrial < 0) {
          estimatedTimePerTrial = estimatedTimePerTrial * -1;
        }

        /************ save and/or print your results here to generate your table of results **************/
        // You should be able to print one row of your results table here.
        // Calculate doubling ratios and any other results for desired columns in table.
        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results.
        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at
        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs
        // can also save data to array(s) for later printing/processing

        // n
        printf("%8lld", n);
        // measured time
        printf("\t%9fsecs", estimatedTimePerTrial);
        // doubling ratio 
        if (n == 4) {
          printf("\t%23s", "n/a"); // no measured doubling ratio when n = 1
        }
        else {
          printf("\t%23f", estimatedTimePerTrial / previousTimeTrialPeriod); // Measured Doubling Ratio
        }
        // expected doubling ratio
        if (n == 4) {
          printf("\t%23s", "n/a"); // no expected doubling ration when n = 1
        }
        else {
          printf("\t%23lld", expectedBruteForce(n));
        }
        printf("\n");
        /*
        else if (strcmp(argv[1],"1") == 0) {
          printf("\t%23f", n3_doublingRatio(n));
        }
        */
       
       previousTimeTrialPeriod = estimatedTimePerTrial;

      for (int i = 0; i < n; i++) {
          free(matrix[i]);
        }
        free(matrix);

    }
}

void heuristicTime() {
  double trialsTime_max = 0.25; // in seconds (0.25)
    long long int trialsCount_max = 1000000,
                  N_min = 1,
                  N_max = 100, // adjust as needed, keep small for debugging ( 10000000 )
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial;

    long long int power = 0;
    double previousTimeTrialPeriod = 0;

    long long int nextDouble = 8;

	// If you are printing a results table directly, print your header line here.
	
  printf("N\t\t");
  printf("Time\t\t\t");
  printf("Experimental\t\t");
  printf("Expected\t\t\t");
  printf("\n");
  
  // for ( n=1; n<N_max; n=2*n )

	// start at 4 for tsm
    for ( n=4; n<N_max; n=n+1 ) {

        /********* any preparations, test input generation, to be used for entire trial set ********/

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

        GenerateRandomCostMatrix(matrix, n, 20);
              
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/
            

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //for(int x=0;x<1000000;x+=2) x--;
            
            greedyHeuristic(matrix, n, bestPath, &cost);

            /******* do any "clean up" after running your algorithm ********/
            
            // get split time -- "split time" just means the total time so far for this trial set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h 
        }
        trialSetCount = trial; // value of trial when loop ends is how many we did
        trialSetTime = splitTime; // total time for trial set is the last split time
        averageTrialTime = trialSetTime / trialSetCount; // this is the average tiem per trial, including any prep/overhead

        /********* NOW DO A "DUMMY" TRIAL SET TO ESTIMATE THE OVERHEAD TIME ********/
        /* We can just repeat this trialSetCount times, which we know should be faster than above */
        
        splitTime=0.0;
        // get timestamp before set of dummy trials are run:
        trialSetStart = clock();
        for ( trial=0; trial < trialSetCount  && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/

            /**** DO NOT Call the algorithm function!!! ******/

            /******* do any "clean up" after running your algorithm ********/

            // get split time -- "split time" just means the total time so far for this tiral set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h ( seconds )
        }
        dummySetCount = trial; // value of trial when loop ends is how many we did, should be same as trialsSetCount
        dummySetTime = splitTime; // total time for dummy trial set is the last split time
        averageDummyTrialTime = dummySetTime / dummySetCount; // this is the average time per dummy trial, including any prep/overhead

        estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime; // should be a decent measurement of time taken to run your algorithm

        if (estimatedTimePerTrial < 0) {
          estimatedTimePerTrial = estimatedTimePerTrial * -1;
        }

        /************ save and/or print your results here to generate your table of results **************/
        // You should be able to print one row of your results table here.
        // Calculate doubling ratios and any other results for desired columns in table.
        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results.
        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at
        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs
        // can also save data to array(s) for later printing/processing

        // n
        printf("%8lld", n);
        // measured time
        printf("\t%9fsecs", estimatedTimePerTrial);
        // doubling ratio 
        if (n == 4) {
          printf("\t%23s", "n/a"); // no measured doubling ratio when n = 1
        }
        else {
          printf("\t%23f", estimatedTimePerTrial / previousTimeTrialPeriod); // Measured Doubling Ratio
        }
        // expected doubling ratio
        if (n != nextDouble) {
          printf("\t%23s", "n/a"); // no expected doubling ration when n = 1
          //printf("%lld",nextDouble);
        }
        else {
          printf("\t%23lld", expectedHeuristicInc(n));
          nextDouble = nextDouble * 2;
        }
        printf("\n");
        /*
        else if (strcmp(argv[1],"1") == 0) {
          printf("\t%23f", n3_doublingRatio(n));
        }
        */
       
       previousTimeTrialPeriod = estimatedTimePerTrial;

      for (int i = 0; i < n; i++) {
          free(matrix[i]);
        }
        free(matrix);

    }
}

void heuristicTimeDoubling() {
  double trialsTime_max = 0.25; // in seconds (0.25)
    long long int trialsCount_max = 1000000,
                  N_min = 1,
                  N_max = 1000000, // adjust as needed, keep small for debugging ( 10000000 )
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial;

    long long int power = 0;
    double previousTimeTrialPeriod = 0;

    //long long int nextDouble = 8;

	// If you are printing a results table directly, print your header line here.
	
  printf("N\t\t");
  printf("Time\t\t\t");
  printf("Experimental\t\t");
  printf("Expected\t\t\t");
  printf("\n");
  
  // for ( n=1; n<N_max; n=2*n )

	// start at 4 for tsm
    for ( n=4; n<N_max; n=n+1 ) {

        /********* any preparations, test input generation, to be used for entire trial set ********/

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

        GenerateRandomCostMatrix(matrix, n, 20);
              
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/
            

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //for(int x=0;x<1000000;x+=2) x--;
            
            greedyHeuristic(matrix, n, bestPath, &cost);

            /******* do any "clean up" after running your algorithm ********/
            
            // get split time -- "split time" just means the total time so far for this trial set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h 
        }
        trialSetCount = trial; // value of trial when loop ends is how many we did
        trialSetTime = splitTime; // total time for trial set is the last split time
        averageTrialTime = trialSetTime / trialSetCount; // this is the average tiem per trial, including any prep/overhead

        /********* NOW DO A "DUMMY" TRIAL SET TO ESTIMATE THE OVERHEAD TIME ********/
        /* We can just repeat this trialSetCount times, which we know should be faster than above */
        
        splitTime=0.0;
        // get timestamp before set of dummy trials are run:
        trialSetStart = clock();
        for ( trial=0; trial < trialSetCount  && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/

            /**** DO NOT Call the algorithm function!!! ******/

            /******* do any "clean up" after running your algorithm ********/

            // get split time -- "split time" just means the total time so far for this tiral set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h ( seconds )
        }
        dummySetCount = trial; // value of trial when loop ends is how many we did, should be same as trialsSetCount
        dummySetTime = splitTime; // total time for dummy trial set is the last split time
        averageDummyTrialTime = dummySetTime / dummySetCount; // this is the average time per dummy trial, including any prep/overhead

        estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime; // should be a decent measurement of time taken to run your algorithm

        if (estimatedTimePerTrial < 0) {
          estimatedTimePerTrial = estimatedTimePerTrial * -1;
        }

        /************ save and/or print your results here to generate your table of results **************/
        // You should be able to print one row of your results table here.
        // Calculate doubling ratios and any other results for desired columns in table.
        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results.
        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at
        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs
        // can also save data to array(s) for later printing/processing

        // n
        printf("%8lld", n);
        // measured time
        printf("\t%9fsecs", estimatedTimePerTrial);
        // doubling ratio 
        if (n == 4) {
          printf("\t%23s", "n/a"); // no measured doubling ratio when n = 1
        }
        else {
          printf("\t%23f", estimatedTimePerTrial / previousTimeTrialPeriod); // Measured Doubling Ratio
        }
        // expected doubling ratio
        if (n == 4) {
          printf("\t%23s", "n/a"); // no expected doubling ration when n = 1
          //printf("%lld",nextDouble);
        }
        else {
          printf("\t%23lld", expectedHeuristicInc(n));
          //nextDouble = nextDouble * 2;
        }
        printf("\n");
        /*
        else if (strcmp(argv[1],"1") == 0) {
          printf("\t%23f", n3_doublingRatio(n));
        }
        */
       
       previousTimeTrialPeriod = estimatedTimePerTrial;

      for (int i = 0; i < n; i++) {
          free(matrix[i]);
        }
        free(matrix);

    }
}

void solutionQuality() {
  double trialsTime_max = 0.25; // in seconds (0.25)
    long long int trialsCount_max = 1000000,
                  N_min = 1,
                  N_max = 1000000, // adjust as needed, keep small for debugging ( 10000000 )
                  n, trial;
    clock_t splitTimeStamp, trialSetStart;
    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial;

    long long int power = 0;
    double previousTimeTrialPeriod = 0;

    double heuristicCost = 0.0;
    double bruteCost = 0.0;

    //long long int nextDouble = 8;

	// If you are printing a results table directly, print your header line here.
	
  printf("N\t\t");
  printf("Avg Solution\t\t\t");
  printf("Avg Exact\t\t");
  printf("Avg SQR\t\t\t");
  printf("\n");
  
  // for ( n=1; n<N_max; n=2*n )

	// start at 4 for tsm
    for ( n=4; n<N_max; n=2*n ) {

        /********* any preparations, test input generation, to be used for entire trial set ********/

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

        GenerateRandomEuclideanCostMatrix(matrix, n, 100, 100);
              
        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/
            

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //for(int x=0;x<1000000;x+=2) x--;
            
            greedyHeuristic(matrix, n, bestPath, &cost);
            heuristicCost += cost;
            permutate(matrix, n, path, 0, strlen(path)-1, bestPath, &cost);
            bruteCost += cost;
            

            /******* do any "clean up" after running your algorithm ********/
            
            // get split time -- "split time" just means the total time so far for this trial set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h 
        }
        trialSetCount = trial; // value of trial when loop ends is how many we did
        trialSetTime = splitTime; // total time for trial set is the last split time
        averageTrialTime = trialSetTime / trialSetCount; // this is the average tiem per trial, including any prep/overhead

        /********* NOW DO A "DUMMY" TRIAL SET TO ESTIMATE THE OVERHEAD TIME ********/
        /* We can just repeat this trialSetCount times, which we know should be faster than above */
        
        splitTime=0.0;
        // get timestamp before set of dummy trials are run:
        trialSetStart = clock();
        for ( trial=0; trial < trialSetCount  && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/

            /**** DO NOT Call the algorithm function!!! ******/

            /******* do any "clean up" after running your algorithm ********/

            // get split time -- "split time" just means the total time so far for this tiral set
            splitTimeStamp = clock(); // 
            // split time is the difference between current split timestamp and the starting time stamp for trial set
            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h ( seconds )
        }
        dummySetCount = trial; // value of trial when loop ends is how many we did, should be same as trialsSetCount
        dummySetTime = splitTime; // total time for dummy trial set is the last split time
        averageDummyTrialTime = dummySetTime / dummySetCount; // this is the average time per dummy trial, including any prep/overhead

        estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime; // should be a decent measurement of time taken to run your algorithm

        if (estimatedTimePerTrial < 0) {
          estimatedTimePerTrial = estimatedTimePerTrial * -1;
        }

        /************ save and/or print your results here to generate your table of results **************/
        // You should be able to print one row of your results table here.
        // Calculate doubling ratios and any other results for desired columns in table.
        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results.
        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at
        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs
        // can also save data to array(s) for later printing/processing

        heuristicCost = heuristicCost/ trialSetCount;
        bruteCost = bruteCost / trialSetCount;
        double avgSQR = heuristicCost/bruteCost;

        // n
        printf("%8lld", n);
        // average solution cost
        printf("\t%9.2f", heuristicCost);
        // average exact solution cost
        printf("\t%9.2f", bruteCost); 
        // average sqr
        printf("\t%9.2f", avgSQR); 
          
        
       
       previousTimeTrialPeriod = estimatedTimePerTrial;

      for (int i = 0; i < n; i++) {
          free(matrix[i]);
        }
        free(matrix);

    }
}

int main (int argc, char* argv[]) {
  //bruteForceTimer();
  //heuristicTime();
  //heuristicTimeDoubling();
  solutionQuality();
}

//////////////////////////////////
/////////////////////////////////