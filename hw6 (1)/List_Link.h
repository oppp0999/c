#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef enum {FALSE, TRUE} bool;

typedef struct tListNode {
	Element data;	
	struct tListNode *next;
} ListNode;

typedef struct {
	int   count; 
	ListNode *pos; 
	ListNode *head; 
} List;

List *createList()
{
	List *pNewList = (List*)malloc(sizeof(List));
	if(pNewList == NULL)
		return NULL;

	pNewList->count = 0;
	pNewList->head = NULL;

	return pNewList;
}

void _insertList(List *pList, ListNode *pPre, Element data)
{
	ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode));
	pNewNode->data = data;

	if(pPre == NULL){		// insert before head node
		pNewNode->next = pList->head;
		pList->head = pNewNode;
	} else {
		pNewNode->next = pPre->next;
		pPre->next = pNewNode;
	}
	pList->count++;
}

bool _searchList(List *pList, ListNode **ppPre, ListNode **ppLoc, Element data)
{
	for(*ppPre = NULL, *ppLoc = pList->head; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->next){
		if((*ppLoc)->data == data)	// data was found
			return TRUE;
		else if((*ppLoc)->data > data)
			break;
	}

	return FALSE;
}

void _deleteList(List *pList, ListNode *pPre, ListNode *pLoc)
{
	if(pPre == NULL) 
		pList->head = pLoc->next;
	else
		pPre->next = pLoc->next;

	free(pLoc);	
	pList->count--;
}

void addNodeList(List *pList, Element data)
{
	ListNode *pPre = NULL, *pLoc = NULL;
	bool found = _searchList(pList, &pPre, &pLoc, data);

	if(!found)
		_insertList(pList, pPre, data);
}

void removeList(List *pList, Element data)
{
	ListNode *pPre = NULL, *pLoc = NULL;
	bool found = _searchList(pList, &pPre, &pLoc, data);

	if(found){
		_deleteList(pList, pPre, pLoc);
    printf("%d was removed !\n", data);
  }
  else
    printf("My list doe not have %d !\n", data);  
}

void destroyList(List *pList)
{
	ListNode *pDel = NULL, *pNext = NULL;

	for(pDel = pList->head; pDel != NULL; pDel = pNext){
		pNext = pDel->next;
		free(pDel);
	}

	free(pList);
}

bool traverseList(List *pList, int fromWhere, Element *pDataOut)
{
	if(fromWhere == 0 || pList->pos == NULL)
		pList->pos = pList->head;
  else
		pList->pos = pList->pos->next;

	if(pList->pos != NULL){
		*pDataOut = pList->pos->data;
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
	  if(ret)
	    printf(" %d,", data);
  } while(ret);
  printf("\b\n");
}