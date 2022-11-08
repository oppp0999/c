#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "bst.h"
#include "hash_s.h"

#define LEN 100

int main(void) {
  int n;
  FILE *fp = NULL;
  int *data;
  char filename[LEN];

  printf("Input file name : ");
  scanf("%s", filename);



  fp = fopen(filename, "r");
  if(fp != NULL){
    fscanf(fp, "%d", &n);

    data = (int*)malloc(sizeof(int)*n);

    for(int i = 0; i<n; i++){
      fscanf(fp, "%d", &data[i]);
    }
    fclose(fp);
  }

 else{
    printf("not file");
    return 0;
  }

 /* for(int i = 0; i<n; i++){
    printf("data[%d] = %d\n", i, data[i]);
  }
*/
getchar();


int in;
printf("Choose a sorting method to use (Selection : 0, Insertion : 1, Bubble : 2, Quick : 3, Merge : 4 ) : ");
scanf("%d", &in);
int *sort;
switch(in){
  case 0: selection_sort(data, n); break;
  case 1: insertion_sort(data, n); break;
  case 2: bubble_sort(data, n); break;
  case 3: quick_sort(data, n, 0, n-1); break;
  case 4: {
  sort = (int*)malloc(sizeof(int)*n);
  merge_sort(data, sort, 0, n-1); 
  break;}
}

printf("\nThe numbers sorted : ");
for(int i = 0; i<n; i++){
    printf("%d ", data[i]);
  }



return 0;







}