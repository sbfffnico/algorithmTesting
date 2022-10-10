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

int main(int argc, int argv) {
  double trialsTime_max = .250; // in seconds 

    long long int trialsCount_max = 10000, // increase as needed to avoid time measurements of zero 

                  N_min = 1, 

                  N_max = SIZE, // adjust as needed, keep small for debugging 

                  n, trial; 

    clock_t splitTimeStamp, trialSetStart; 

    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial; 

    long long int power = 0;
    double previousTimeTrialPeriod = 0;

    srand(time(NULL));

    n = SIZE;

    long long int arr[n];

    int sum = 0;

    long long int *array = generateTriSumTestInput(arr, n, MAXVALUE, NFORCEDTRIPLETS); //array[], arraySize, maxValue, nForcedTriplets
    //int sizeOfArray = sizeof(array)/sizeof(array[0]);
    //printf("\nsize of array: %d", sizeOfArray);

    //printf("\nTest for pointer to array: %lld, %lld, %lld", array[0], array[1], array[2]);

    /*
    printf("\n");
    for (int i = 0; i < NFORCEDTRIPLETS * 3; i++) {
      printf("%lld ", array[i]);
    }
    printf("\n");
    */

    /*
    for (long long int i = 0; i < SIZE; i++) {
      printf("%lld ", arr[i]);
    }
    printf("\n");
    //printf("%d", sum);
    */

    printf("\n---------------------------------------------\n");
    printf("N Forced Triplets Check: \n");
    for (long long int i = 0; i < NFORCEDTRIPLETS * 3; i = i + 3) {
      printf("array[%lld] = %lld, array[%lld] = %lld, array[%lld] = %lld, ", array[i], arr[array[i]], array[i+1], arr[array[i + 1]], array[i+2], arr[array[i + 2]]);
      printf("----- Sum = %lld ", arr[array[i]] + arr[array[i + 1]] + arr[array[i + 2]]);
      printf("\n");
    }
    printf("---------------------------------------------");
    printf("\n\n");

    printf("Array used: [");
    for (long long int i = 0; i < SIZE; i++) {
      printf("%lld, ", arr[i]);
      if (i == SIZE - 1) {
        printf("%lld]", arr[i]);
      }
    }
    printf("\n");
    //printf("%d", sum);

    printf("n^3 algorithm here\n");
    sumZero1(arr, n);

    printf("Array used: [");
    for (long long int i = 0; i < SIZE; i++) {
      printf("%lld, ", arr[i]);
      if (i == SIZE - 1) {
        printf("%lld]", arr[i]);
      }
    }
    printf("\n");
    //printf("%d", sum);

    printf("faster algorithm here (not yet time tested)\n");
    sumZero2(arr, n);

    printf("Sorted Array: [");
    for (long long int i = 0; i < SIZE; i++) {
      printf("%lld, ", arr[i]);
      if (i == SIZE - 1) {
        printf("%lld]", arr[i]);
      }
    }
    printf("\n");

    return 0;
}