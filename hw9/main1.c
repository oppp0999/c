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

NODE * root = NULL;
for(int i = 0; i<n; i++){
insert_node(&root, data[i]);}

int b;
printf("Target integer : ");
scanf("%d", &b);
getchar();
printf("\n");

int s;
printf("Choose a searching method (Binary : 1, Hashed : 2) : ");
scanf("%d", &s);

if(s == 1){

selection_sort(data, n);

if((int)search_node(root,b)== 0){
  printf("%d is not found !", b);
}
else{
  printf("%d is found !", b);
}
}



else if(s == 2){
hash_t *hashtable[n];

init_hashtable(hashtable, n); 

for(int i = 0; i<n; i++){
  add_value(hashtable, data[i], n);
}

//int b = 99;
//print_index(hashtable ,16, n);
if(hash_search(hashtable, b, n)){
  printf("%d is found !", b);
}
else {
  printf("%d is not found !", b);
}
}




return 0;







}