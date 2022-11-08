#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//typedef int* elements;

void insertion_sort (int arr[], int n ) {
  int i;
  int tt;
  
  for(i = 1; i<n; i++){
    tt= arr[i];
      while(i>0 && arr[i-1]>tt){
      arr[i]=arr[i-1];
      i--;
      }
     	arr[i]=tt;
  }
}

void selection_sort(int arr[], int n) {
  int i, j;
  int s = 0;
  int tt = 0;
  
  for(i =0; i < n-1; i++){
    s = i;
    for(j = i+1; j<n; j++){
       if(arr[j] < arr[s]){
          s = j;
       }
    }
    tt = arr[i];
    arr[i] = arr[s];
    arr[s] = tt;
  }
}

void bubble_sort(int arr[], int n) {
	int i, j;
	int tt;
	for(i = n-1; i>0; i--){
	  for(j=0; j<i; j++){
	     if(arr[j]>arr[j+1]){
	         tt=arr[j];
	         arr[j]=arr[j+1];
	         arr[j+1]=tt;
	     }
	  }
	}
}

void quick_sort(int data[], int n, int start, int end)
{
    int i, j;
    int temp; 
    int p;

    if (start < end) {
        p = data[start]; 
        i = start + 1; 
        j = end;
        do {
            while (i < end && data[i] < p) {
                i++; 
            } 
            while (start < j && data[j] > p) {
                j--; 
            }
            if (i < j) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        } while (i < j);
       // p = data[start];
        data[start] = data[j];
        data[j] = p;
        quick_sort(data, n, start, j - 1); 
        quick_sort(data, n, j + 1, end); 
    }
}


void merge(int list[], int sorted[], int i, int m, int n){
  int j,k,t;
  int a = i;
  j = m + 1;
  k = i;
  while(a <= m && j <= n){
    if(list[a] < list[j]){
      sorted[k++] = list[a++];
    }
    else{
      sorted[k++] = list[j++];
    }
  }
  if(a>m){
    for(t = j; t <= n; t++){
      sorted[k++] = list[t];
    }
  }
  else {
    for(t = a; t <= m; t++){
      sorted[k++] = list[t];
    }
  }
  for(t = i; t<=n; t++){
    list[t] = sorted[t];
  }
}

void merge_sort(int list[], int sorted[] , int low, int high){
  if(low < high){
    int mid = (low + high)/2;
    merge_sort(list,sorted, low, mid);
    merge_sort(list,sorted, mid+1, high);
    merge(list,sorted, low, mid, high);
  }
}