#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h>

int main(int argc, char* argv[]) {
  srand(time(NULL));

  int N = 32;
  int arr[N];

  for (int i = 0; i < N; i++) {
    arr[i] = i;
  }

  for (int i = 0; i < N; i++) {
    printf("%d ", arr[i]);
  }

  return 0;
}