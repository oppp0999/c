#include <stdio.h>
#include <stdlib.h>

#define ListSize 100

typedef int Element;
typedef enum {FALSE, TRUE} bool;

typedef struct {
   Element *data;		// array to store elements
   int size;			    // maximum size
   int pos;
   int rear;		// rear
} List;

List* createList(int size)
{
	List *pList = (List *)malloc(sizeof(List));
	if(pList == NULL)
		return NULL;
	
	pList->data = (Element *)malloc(size * sizeof(Element));
	if(pList->data == NULL){
		free(pList);
		return NULL;
	}
	pList->size = size;
  pList->pos = -1;
	pList->rear = 0;

	return pList;
}

void _insertList(List *pList, int loc, Element data)
{
  int i;

	for(i=pList->rear; i>loc ; i--)
    pList->data[i] = pList->data[i-1];
  pList->data[loc] = data;
  pList->rear++;
}

bool _searchList(List *pList, int *p, Element data)
{
	for(*p=0; *p < pList->rear ; (*p)++){
		if(pList->data[*p] == data)	// data was found
			return TRUE;
		else if(pList->data[*p] > data){
			break;
    }  
	}
  
	return FALSE;
}

void _deleteList(List *pList, int p)
{
	int i,j;

  if(p >=0 ){
    for(; p < pList->rear ; p++)
      pList->data[p] = pList->data[p+1];

	  pList->rear--;
  }  
}

void addNodeList(List *pList, Element data)
{
	int loc;
	bool found ;
  
  if(pList->size == pList->rear){
    printf("List is full !\n");
    return;
  } 

  found = _searchList(pList, &loc, data);

	if(!found)
		_insertList(pList, loc, data);
}

void removeList(List *pList, Element data)
{
	int loc;
	bool found;
  
  if(pList->rear==0){
    printf("List is empty !\n");
    return;
  }

  found = _searchList(pList, &loc, data);

	if(found){
		_deleteList(pList, loc);
    printf("%d was removed !\n", data);
  }
  else
    printf("My list doe not have %d !\n", data);  
}

void destroyList(List *pList)
{
  if(pList->data)
    free(pList->data);
	free(pList);
}

bool traverseList(List *pList, int fromWhere, Element *pDataOut)
{
	if(fromWhere == 0 || pList->pos == -1)
		pList->pos = 0;
  else
		(pList->pos)++;

	if(fromWhere < pList->rear){
		*pDataOut = pList->data[pList->pos];
		 return TRUE;
	} 
  else {
		*pDataOut = 0;
		 return FALSE;
	}
  return FALSE;
} 

void FullList(List *pList)
{
  int n = 0;		// current index
  int data = 0;
  int ret;

  printf("The current status of List :");
  do {
	  ret = traverseList(pList, n++, &data);
	  if(ret){
      if(n==1)
        printf(" %d", data);
      else  
	      printf(", %d", data);
    }  
  } while(ret);
  printf("\n");

  pList->pos = -1;
}