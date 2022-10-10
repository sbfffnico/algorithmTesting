/////////////////////////////////////////
/////////////////////////////////////////

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

long long int busyCount;

void doBusyWork() {
  for (int i = 0; i < 10000; i++) {
    busyCount++;
  }
}

// give argument of 1 to run
void busyAlgorithm_N3(long long int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < i - 1; j++) {
      for (int k = 0; k < j - 1; k++) {
        doBusyWork();
      }
    }
  }
}

double n3_doublingRatio(long long int N) {
  double thirdPower = N * N * N / 1.000000;
  double n_halved = N/2;
  double halved_thirdPower = n_halved * n_halved * n_halved;

  return thirdPower / halved_thirdPower;
}

// give argument of 2 to run   
void busyAlgorithm_NlogN(long long int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 1; j < i; j = j * 2) {
      doBusyWork();
    }
  }
}

double logN(long long int N) {
  while (N > 1) {
    return 1 + logN(N/2);
  }
  return 0;
}

double NlogN_doublingRatio(long long int N) {
  double firstLog = logN(N);
  double secondLog = logN(N/2);

  return (N * firstLog) / (N/2 * secondLog);
}

// give argument of 3 to run - recursive
double busyAlgorithm_logN(long long int N) {
  if (N > 1) {
    busyAlgorithm_logN(N/2);
  }

  doBusyWork();
  return 0;
}

double logN_doublingRatio(long long int N) {
  return logN(N) / logN(N/2);
}

// give argument of 4 to run - recursive
double busyAlgorithm_N2logN(long long int N) {

  for(int i = 0; i < N; i++) {
    for(int j= 0; j < i; j++) {
      doBusyWork();
    }
  }

  if (N > 1) {
    busyAlgorithm_N2logN(N/2);
  }

  return 0;
}

double N2logN_doublingRatio(long long int N) {
  double firstLog = logN(N);
  double secondLog = logN(N/2);

  return (N * N * firstLog) / ((N/2) * (N/2) * secondLog);
}

// give argument of 5 to run
void busyAlgorithm_N6(long long int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < j; k++) {
        for (int l = 0; l < j; l++) {
          for (int m = 0; m < l; m++) {
            for (int n = 0; n < m; n++) {
              doBusyWork();
            }
          }
        }
      }
    }
  }
}

double N6_doublingRatio(long long int N) {
  return (N * N * N * N * N * N) / ((N/2)*(N/2)*(N/2)*(N/2)*(N/2)*(N/2));
}

// give argument of 6 to run
void busyAlgorithm_logN_squared(long long int N) {
  for (int i = 1; i < N; i = i * 2) {
    for (int j = 1; j < N; j = j * 2) {
      doBusyWork();
    }
  }
}

double logN_squared_doublingRatio(long long int N) {
  double firstLog = logN(N);
  double secondLog = (logN(N/2));

  return (firstLog * firstLog) / (secondLog * secondLog);
}

// give argument of 7 to run
int busyAlgorithm_exp(long long int N) {
  for (int i = 0; i < N; i++) {
    doBusyWork();
    return busyAlgorithm_exp(N*2);
  }
}

double exp_doublingRatio(long long int N) {
  double firstExp = 1;
  double secondExp = 1;

  for (int i = 1; i <= N; i++) {
    firstExp = 2 * firstExp;
  }

  for (int i = 1; i <= N/2; i++) {
    secondExp = 2 * secondExp;
  }

  return firstExp / secondExp;
}

// give argument of 8 to run
double busyAlgorithm_factorial(long long int N) {
  if (N == 0) {
    return 0;
  }

  //printf("%d ", N);

  for (int i = 0; i < N; i++){
    doBusyWork;
    return busyAlgorithm_factorial(N-1);
  }
}

double factorial_doublingRatio(long long int N) {
  double firstFactorial = 1.0, secondFactorial = 1.0;
  
  for (int i = N; i > 0; i--) {
    firstFactorial = firstFactorial * i;
  }

  for (int i = N/2; i > 0; i--) {
    secondFactorial = secondFactorial * i;
  }

  return firstFactorial / secondFactorial;
  
}

int main (int argc, char* argv[]) {

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
	
  if (argc < 2) {
    printf("Need an argument to run function --- exiting\n");
    return 0;
  }

  //printf("argc: %d , argv: %s --- \n\n", argc, argv[1]);

  if(strcmp(argv[1],"1") == 0) {
    printf("n^3 algorithm\n");
    printf("---------------\n");
  }
  else if (strcmp(argv[1],"2") == 0) {
    printf("n*log(n) algorithm\n");
    printf("------------------\n");
  }
  else if (strcmp(argv[1],"3") == 0) {
    printf("recursive log(n) algorithm\n");
    printf("----------------\n");
  }
  else if (strcmp(argv[1],"4") == 0) {
    printf("recursive n^2*log(n) algorithm\n");
    printf("--------------------------\n");
  }
  else if (strcmp(argv[1],"5") == 0) {
    printf("n^6 algorithm\n");
    printf("----------------\n");
  }
  else if (strcmp(argv[1],"6") == 0) {
    printf("log(n)^2 algorithm\n");
    printf("----------------\n");
  }
  else if (strcmp(argv[1],"7") == 0) {
    printf("recursive 2^N algorithm\n");
    printf("----------------\n");
  }
  else if (strcmp(argv[1],"8") == 0) {
    printf("N! algorithm\n");
    printf("----------------\n");
  }
  else {
    printf("Not a valid number to run algorithm --- exiting\n");
    return 0;
  }

  // table header
  // length cheat sheet: 
  printf("Doublings of N"); // 14 in length
  printf("\tSize of N"); // 9 in length
  printf("\tMeasured Time"); // 13 in length
  printf("\tMeasured Doubling Ratio"); // 23 in length
  printf("\tExpected Doubling Ratio"); // 23 in length
  printf("\t      Busy Count"); // 16 in length
  printf("\tMeasured Time / Busy Count"); // 26 in length
  printf("\n");
  // reference length for padding : 14 9 13 23 23 16 26
  for (int i = 0; i < 14; i++) {
    printf("-");
  }
  printf("\t");
  for (int i = 0; i < 9; i++) {
    printf("-");
  }
  printf("\t");
  for (int i = 0; i < 13; i++) {
    printf("-");
  }
  printf("\t");
  for (int i = 0; i < 23; i++) {
    printf("-");
  }
  printf("\t");
  for (int i = 0; i < 23; i++) {
    printf("-");
  }
  printf("\t");
  for (int i = 0; i < 16; i++) {
    printf("-");
  }
  printf("\t");
  for (int i = 0; i < 26; i++) {
    printf("-");
  }
  printf("\n");
  // end of table header
  // reference length for padding : 14 9 13 23 23 16 26
  
  // for ( n=1; n<N_max; n=2*n )

	// For each size N of input we want to test -- typically start N at 1 and double each repetition
    for ( n=1; n<N_max; n=2*n ) {

        /********* any preparations, test input generation, to be used for entire trial set ********/

        
        if(strcmp(argv[1],"7")==0) {
          if(n != 1) {
            //printf("before n: %d, ",n);
            n = n/2;
            n++;
            //printf("after n: %d\n",n);
          }
        }
        if(strcmp(argv[1],"8")==0) {
          if(n != 1) {
            //printf("before n: %d, ",n);
            n = n/2;
            n++;
            //printf("after n: %d\n",n);
          }
        }

        splitTime=0.0;
        // get timestamp before set of trials are run:
        trialSetStart = clock();
	    // For each trial trialNumber=1 to Number of Trials per input size:
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {

            /******** any preparations, test input generation, for a single trial run *********/
            busyCount = 0;

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/
            //for(int x=0;x<1000000;x+=2) x--;
            if(strcmp(argv[1],"1") == 0) {
              busyAlgorithm_N3(n);
            }
            else if(strcmp(argv[1],"2") == 0) {
              busyAlgorithm_NlogN(n);
            }
            else if(strcmp(argv[1],"3") == 0) {
              busyAlgorithm_logN(n);
            }
            else if(strcmp(argv[1],"4") == 0) {
              busyAlgorithm_N2logN(n);
            }
            else if(strcmp(argv[1],"5") == 0) {
              busyAlgorithm_N6(n);
            }
            else if(strcmp(argv[1],"6") == 0) {
              busyAlgorithm_logN_squared(n);
            }
            else if(strcmp(argv[1],"7") == 0) {
              busyAlgorithm_exp(n);
            }
            else if(strcmp(argv[1],"8") == 0) {
              busyAlgorithm_factorial(n);
            }
            else {
              printf("How did it even get here? -- exiting");
              return 0;
            }
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

        // print table row
        // reference length for padding : 14 9 13 23 23 10 26
        //
        printf("%14lld", power++); // Doublings of N
        //
        printf("\t%9d", n); // Size of N 
        //
        printf("\t%9fsecs", estimatedTimePerTrial); // Measured Time
        //
        if (n == 1) {
          printf("\t%23s", "n/a"); // no measured doubling ratio when n = 1
        }
        else {
          printf("\t%23f", estimatedTimePerTrial / previousTimeTrialPeriod); // Measured Doubling Ratio
        }
        //
        if (n == 1) {
          printf("\t%23s", "n/a"); // no expected doubling ration when n = 1
        }
        else if (strcmp(argv[1],"1") == 0) {
          printf("\t%23f", n3_doublingRatio(n));
        }
        else if (strcmp(argv[1],"2") == 0) {
          printf("\t%23f", NlogN_doublingRatio(n));
        }
        else if (strcmp(argv[1],"3") == 0) {
          printf("\t%23f", logN_doublingRatio(n));
        }
        else if (strcmp(argv[1],"4") == 0) {
          printf("\t%23f", N2logN_doublingRatio(n));
        }
        else if (strcmp(argv[1],"5") == 0) {
          printf("\t%23f", N6_doublingRatio(n));
        }
        else if (strcmp(argv[1],"6") == 0) {
          printf("\t%23f", logN_squared_doublingRatio(n));
        }
        else if (strcmp(argv[1],"7") == 0) {
          if (n % 2 != 0) {
            printf("\t%23s", "n/a");
          }
          else {
            printf("\t%23f", exp_doublingRatio(n));
          }
        }
        else if (strcmp(argv[1],"8") == 0) {
          if (n % 2 != 0) {
            printf("\t%26s", "n/a");
          }
          else {
            printf("\t%26f", factorial_doublingRatio(n));
          }
        }
        //
        printf("\t%16lld", busyCount); // Busy Count
        //
        printf("\t%26lld", estimatedTimePerTrial / busyCount); // Measured Time / Busy Count
        //
        printf("\n");

        previousTimeTrialPeriod = estimatedTimePerTrial;

        /************ save and/or print your results here to generate your table of results **************/
        // You should be able to print one row of your results table here.
        // Calculate doubling ratios and any other results for desired columns in table.
        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results.
        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at
        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs
        // can also save data to array(s) for later printing/processing

    }
}

//////////////////////////////////
/////////////////////////////////