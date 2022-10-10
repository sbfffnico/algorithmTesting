///////////////////////////////////////// 
///////////////////////////////////////// 

#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h>

#define SIZE 6
#define MAXVALUE 3
#define NFORCEDTRIPLETS 2

long long int * generateTriSumTestInput(long long int array[], long long int arraySize, long long int maxValue, int nForcedTriplets) {
  // fill array
  //printf("Array Size: %lld, Max Value: %lld, n Forced Triplets: %lld\n", arraySize, maxValue, nForcedTriplets);
  for (long long int i = 0; i < arraySize; i++) {
    array[i] = (rand() % ((maxValue*2) + 1)) - maxValue;
  }

  /*
  // set size to 6 to test
  array[0] = 1;
  array[1] = 2;
  array[2] = 3;
  array[3] = 4;
  array[4] = 5;
  array[5] = -9;
  */

  /*
  for (long long int i = 0; i < arraySize; i++) {
    printf("%lld ", array[i]);
  }
  printf("\n");
  */

  long long int returnSize = nForcedTriplets * 3;
  static long long int returnArray[20];

  for (long long int i = 0; i < nForcedTriplets; i++) {
    //printf("Round %lld\n========", i);
    int random1 = 0, random2 = 0, random3 = 0;
    //printf("Randoms: %d, %d, %d\n", random1, random2, random3);

    do {
      random1 = rand() % arraySize;
      //printf("rand1: %d, ", random1);
      random2 = rand() % arraySize;
      //printf("rand2: %d, ", random2);
      random3 = rand() % arraySize;
      //printf("rand3: %d\n", random3);
    } while (random1 == random2 || random2 == random3 || random3 == random1);

    //printf("Random indexes: %lld, %lld, %lld\n", random1, random2, random3);

    /*
    for (long long int j = 0; j < returnSize; j++) {
        returnArray[j] = random1;
        returnArray[j+1] = random2;
        returnArray[j+2] = random3;
        //printf("Random3: %lld\n", random3);
        j = j + 2;
    }
    */

    int returnArrayIndex = i * 3;
    returnArray[returnArrayIndex] = random1;
    returnArray[returnArrayIndex+1] = random2;
    returnArray[returnArrayIndex+2] = random3;
    
    //printf("Random1: index - %lld, value - %lld\n", random1, array[random1]);
    //printf("Random2: index - %lld, value - %lld\n", random2, array[random2]);
    //printf("Random3: index - %lld, value - %lld\n", random3, array[random3]);

    array[random3] = (array[random1] + array[random2]) * -1;

    //printf("Random1: index - %lld, value - %lld\n", random1, array[random1]);
    //printf("Random2: index - %lld, value - %lld\n", random2, array[random2]);
    //printf("Random3: index - %lld, value - %lld\n", random3, array[random3]);

    
    /*
    printf("Test for return array: ");
    for (long long int i = 0; i < returnSize; i++) {
      printf("%lld ", returnArray[i]);
    }
    printf("\n");
    */

    random1 = 0, random2 = 0, random3 = 0;
  }

  return returnArray;

  /*
  for (long long int i = 0; i < arraySize; i++) {
    printf("%d:%lld", i, array[i]);
    if ( array[i] == 0) {
      printf(" --- NEG FOUND");
    }
    if ( array[i] == 0) {
      printf(" --- POS FOUND");
    }
    printf("\n");
  }
  //printf("\n");
  */
}

void sumZero1(long long int array[], long long int arraySize) {
  for (int i = 0; i < arraySize - 2; i++) {
    for (int j = i + 1; j < arraySize - 1; j++) {
      for (int k = j + 1; k < arraySize; k++) {
        if (array[i] + array[j] + array[k] == 0) {
          if (arraySize <= 100) {
            printf("FOUND: (array[%lld]: %3lld, array[%lld]: %3lld, array[%lld]: %3lld)", i, array[i], j, array[j], k, array[k]);
            printf(" ----- %2lld + %2lld + %2lld  = %2lld\n", array[i], array[j], array[k], array[i] + array[j] + array[k]);
          }
        }
      }
    }
  }
}

// left needs to start at 0, right needs to start at array length - 1
long long int partition(long long int array[], long long int left, long long int right) {
  int pivot = array[right];

  int i = left - 1, temp;
  for (int j = left; j < right; j++) {
    if (array[j] < pivot) {
      i++;
      temp = array[j];
      array[j] = array[i];
      array[i] = temp;
    }
  }

  temp = array[right];
  array[right] = array[i+1];
  array[i+1] = temp;

  return i + 1;
}

// left needs to start at 0, right needs to start at array length - 1
long long int quicksort(long long int array[], long long int left, long long int right) {
  if (left < right) {
    int index = partition(array, left, right);

    quicksort(array, left, index-1);
    quicksort(array, index+1, right);
  }
}

void sumZero2(long long int array[], long long int arraySize) {
  // sort first
  quicksort(array, 0, arraySize - 1);

  for(long long int i = 0; i < arraySize - 2; i++) {
    long long int setVal = array[i];
    long long int start = i + 1;
    long long int end = arraySize - 1;
    //printf("Run #%lld: i = %lld, j = %lld, k = %lld\n", i + 1, i, start, end);
    while (start < end) {
      int count = 1;
      //printf("Inner loop run#%d: i = %lld, j = %lld, k = %lld\n", count, i, start, end);
      long long int startVal = array[start];
      long long int endVal = array[end];
      if (setVal + startVal + endVal == 0) {
        if (arraySize <= 100) {
          printf("FOUND: (array[%lld]: %3lld, array[%lld]: %3lld, array[%lld]: %3lld)", i, setVal, start, startVal, end, endVal);
          printf(" ----- %2lld + %2lld + %2lld  = %2lld\n", setVal, startVal, endVal, setVal + startVal + endVal);
        }
        start = start + 1;
        end = end - 1;
      }
      else if (setVal + startVal + endVal > 0) {
        end = end - 1;
      }
      else {
        start = start + 1;
      }
    }
  }
}

void sumZero3(long long int array[], long long int arraySize) {

}



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

            long long int arr[n];

            /*
            printf("Array size: %d\n", n);
            for (int i = 0; i < n; i++) {
              printf("%d ", arr[i]);
            }
            */

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/ 

            generateTriSumTestInput(arr, n, 10, 0);
            
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

            double arr[n];

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
          double doublingRatio = pow((n/1.000), 1.585);
          double halvedDoubling = pow((n/2.000), 1.585);
          doublingRatio = doublingRatio / halvedDoubling;

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