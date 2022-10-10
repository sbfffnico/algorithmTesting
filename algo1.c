///////////////////////////////////////// 
///////////////////////////////////////// 

#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h>

#define SIZE 750000

int main (int argc, int argv) { 

    double trialsTime_max = .250; // in seconds 

    long long int trialsCount_max = 10000, // increase as needed to avoid time measurements of zero 

                  N_min = 1, 

                  N_max = SIZE, // adjust as needed, keep small for debugging 

                  n, trial; 

    clock_t splitTimeStamp, trialSetStart; 

    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial; 

    long long int power = 0;
    double previousTimeTrialPeriod = 0;

// If you are printing a results table directly, print your header line here. 

printf("Doublings of N"); // 14 in length
printf("\tSize of N"); // 9 in length
printf("\tMeasured Time"); // 13 in length
printf("\tMeasured Doubling Ratio"); // 23 in length
printf("\tExpected Doubling Ratio"); // 23 in length
printf("\n");

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
printf("\n");

// For each size N of input we want to test -- typically start N at 1 and double each repetition 

    for ( n=1; n<N_max; n=2*n ) { 
        /********* any preparations, test input generation, to be used for entire trial set ********/ 
        splitTime=0.0; 
        // get timestamp before set of trials are run: 
        trialSetStart = clock(); 
    // For each trial trialNumber=1 to Number of Trials per input size: 
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {  
            /******** any preparations, test input generation, for a single trial run *********/ 

            srand(time(NULL));

            int arr[n];

            for (int i = 0; i < n; i++) {
              arr[i] = rand() % 10;
            }

            /*
            printf("Array size: %d\n", n);
            for (int i = 0; i < n; i++) {
              printf("%d ", arr[i]);
            }
            */

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/ 

            int a = 0;
            int b = n;
            while (a < b) {
              if (arr[a] < arr[b]) {
                a = a + 1;
              }
              else {
                b = b - 1;
              }
            }
            
            /******* do any "clean up" after running your algorithm ********/ 

            // get split time -- "split time" just means the total time so far for this tiral set 

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

            srand(time(NULL));

            int arr[n];

            for (int i = 0; i < n; i++) {
              arr[i] = rand() % 10;
            }

            /*
            printf("Array size: %d\n", n);
            for (int i = 0; i < n; i++) {
              printf("%d ", arr[i]);
            }
            */

            /**** DO NOT Call the algorithm function!!! ******/ 

            /******* do any "clean up" after running your algorithm ********/ 

            // get split time -- "split time" just means the total time so far for this tiral set 

            splitTimeStamp = clock(); //  

            // split time is the difference between current split timestamp and the starting time stamp for trial set 

            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h  
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
        printf("%14lld", power++); // Doublings of N
        printf("\t%9d", n); // Size of N 
        printf("\t%9fsecs", estimatedTimePerTrial); // Measured Time
        if (n == 1) {
          printf("\t%23s", "n/a"); // no measured doubling ratio when n = 1
        }
        else {
          printf("\t%23f", estimatedTimePerTrial / previousTimeTrialPeriod); // Measured Doubling Ratio
        }
        if (n == 1) {
          printf("\t%23s", "n/a"); // no expected doubling ration when n = 1
        }
        else {
          double doublingRatio = n / 1.00000;
          double nHalved = n / 2.00000;
          doublingRatio = doublingRatio / nHalved;

          printf("\t%23f", doublingRatio); // expected doubling ratio
        }
        printf("\n");

        previousTimeTrialPeriod = estimatedTimePerTrial;

        // Calculate doubling ratios and any other results for desired columns in table. 

        // Consider additional columns you include in a more detailed table that may help with debugging or just making sense of results. 

        // May be a good idea to print a row of results to output terminal window or a file, so if your program crashes you still have results to look at 

        // use the fflush(stdout) or fflush(filePointer) or equivalent in C++, to force output so nothing is lost if a crash occurs 

        // can also save data to array(s) for later printing/processing 
    } 

} 

 

////////////////////////////////// 

///////////////////////////////// 