///////////////////////////////////////// 
///////////////////////////////////////// 

#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h>

#define SIZE 32

int array[SIZE];

void fillArray(int arr[SIZE]) {
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 10;
    }
}

int algorithm_A(int N, int list[SIZE]) {
    int a = 0; 
    int b = N;

    while (a < b) {
        if (list[a] < list[b]) {
            a = a + 1;
        }
        else {
            b = b - 1;
        }
    }
}

int main (int argc, int argv) { 

    fillArray(array);

    for (int i = 0; i < 32; i++) {
        printf("%d ", array[i]);
    }

    double trialsTime_max = .250; // in seconds 

    long long int trialsCount_max = 10000, // increase as needed to avoid time measurements of zero 

                  N_min = 1, 

                  N_max = SIZE, // adjust as needed, keep small for debugging 

                  n, trial; 

    clock_t splitTimeStamp, trialSetStart; 

    double splitTime, trialSetCount, trialSetTime, dummySetCount, dummySetTime, averageTrialTime, averageDummyTrialTime, estimatedTimePerTrial; 

// If you are printing a results table directly, print your header line here. 

// For each size N of input we want to test -- typically start N at 1 and double each repetition 

    for ( n=1; n<N_max; n=2*n ) { 
        /********* any preparations, test input generation, to be used for entire trial set ********/ 
        splitTime=0.0; 
        // get timestamp before set of trials are run: 
        trialSetStart = clock(); 
    // For each trial trialNumber=1 to Number of Trials per input size: 
        for ( trial=0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {  
            /******** any preparations, test input generation, for a single trial run *********/ 

            /**** >>>> Call the algorithm function we are testing, using the generated test input <<<<< ******/ 
            
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

            /**** DO NOT Call the algorithm function!!! ******/ 

            /******* do any "clean up" after running your algorithm ********/ 

            // get split time -- "split time" just means the total time so far for this tiral set 

            splitTimeStamp = clock(); //  

            // split time is the difference between current split timestamp and the starting time stamp for trial set 

            splitTime = (splitTimeStamp-trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h  
        } 
        dummySetCount = trial; // value of trial when loop ends is how many we did, should be same as trialsSetCount 
        dummySetTime = splitTime; // total time for dummy trial set is the last split time 
        averageDummyTrialTime = dummySetTime / dummySetCount; // this is the average tiem per dummy trial, including any prep/overhead 

        estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime; // should be a decent measurement of time taken to run your algorithm 

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