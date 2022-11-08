#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSIZE 2

#define ERR 0
#define DUP 1
#define NOR 2

typedef enum{false, true} bool;

typedef struct vertex
{
  struct vertex* pNextVertex;
  void* dataPtr;
  int inDegree;
  int outDegree;
  bool processed;
  struct arc* pArc;
} VERTEX;

typedef struct
{
  int count;
  struct vertex* first;
  int (*compare)(void* arg1, void* arg2);
} GRAPH;

typedef struct arc
{
  struct vertex* dest;
  struct arc* pNextArc;
} ARC;

int comp(void* arg1, void* arg2)
{
  return strcmp((char *)arg1, (char *)arg2) ;
}

void DisplayGraph(GRAPH *g)
{
  ARC *aP;
  VERTEX *vP;

  if(!g)
    return ;

  printf("\nThe graph is :");
  for(vP=g->first; vP ; vP=vP->pNextVertex){
    printf("\n%s :", (char *)vP->dataPtr);
    for(aP=vP->pArc; aP ; aP=aP->pNextArc){
      printf(" %s", (char *)aP->dest->dataPtr);
    }
  }
  printf("\n");
  return ;
}

int InsertVertex(GRAPH *g, void *data)
{
  VERTEX *vtemp = NULL;
  VERTEX *pre, *post;
  int test;

  if( (vtemp = (VERTEX *)malloc(sizeof(VERTEX))) )
  {
    vtemp->pNextVertex = NULL;
    vtemp->dataPtr = data;
    vtemp->inDegree = 0;
    vtemp->outDegree = 0;
    vtemp->processed = false;
    vtemp->pArc = NULL;
  }
  else
    return ERR;

  for(pre=NULL, post = g->first ; post != NULL ; pre=post, post=post->pNextVertex){
    test = g->compare(data, post->dataPtr);   

    if(test==0){
      free(vtemp);
      return DUP;
    }   
    else if(test<0)
    {
      if(pre==NULL)
      {
        vtemp->pNextVertex = post;
        g->first = vtemp;
      }  
      else
      {
        vtemp->pNextVertex = post;
        pre->pNextVertex = vtemp;
      }
      (g->count)++;

      return NOR;
    }  
  }
  
  if(g->first == NULL)
  {
    g->first = vtemp;
    (g->count)++;
  }
  else{
    pre->pNextVertex = vtemp;
    (g->count)++;
  }

  return NOR;
}

GRAPH* CreateGraph(void *data, int (*compare)(void* arg1, void* arg2))
{
  GRAPH *temp=NULL;
  
  if( (temp = (GRAPH *)malloc(sizeof(GRAPH))) )
  {
    temp->count = 0;
    temp->first = NULL;
    temp->compare =compare;

    if( InsertVertex(temp, data) == ERR )
    {
      free(temp);
      return NULL;
    }  
  }  

  return temp;
}

int DeleteVertex(GRAPH *g, void *data)
{
  ARC *aPre, *aNext;
  VERTEX *vPre, *vNext;
  int status=ERR;

  for(vPre=NULL, vNext=g->first; vNext!=NULL; )
  {
    if(g->compare(vNext->dataPtr, data) == 0)
    {
      for(aPre=NULL, aNext=vNext->pArc; aNext!=NULL; aPre=aNext, aNext=aNext->pNextArc, free(aPre));
      vPre=vNext;
      vNext=vNext->pNextVertex;
      free(vPre);
      status = NOR;
    }
    else if(vNext->outDegree > 0)
    {
      for(aPre=NULL, aNext=vNext->pArc; aNext!=NULL; ){
        if(g->compare(aNext->dest->dataPtr, data)==0){
          aPre=aNext;
          aNext=aNext->pNextArc;
          (vNext->inDegree)--;
          free(aPre);
        }
        else{
          aPre=aNext;
          aNext=aNext->pNextArc;
        }
      }  
      vPre=vNext;
      vNext=vNext->pNextVertex;  
    }
  }

  return status;
}

int AddEdge(GRAPH *g, void *from, void *to)
{
  ARC *aPre=NULL, *atemp=NULL, *aP=NULL;
  VERTEX *vFrom=NULL, *vTo=NULL, *vtemp=NULL;

  if( !(aP = (ARC *)malloc(sizeof(ARC))) )
  {
    printf("Can't add edge from %s to %s !\n", (char *)from, (char *)to);
    return ERR ;
  }  

  for(vtemp=g->first ; vtemp!=NULL && (vFrom == NULL || vTo == NULL) ;vtemp=vtemp->pNextVertex)
  {
    if(g->compare(vtemp->dataPtr, from) == 0)
      vFrom = vtemp;
    if(g->compare(vtemp->dataPtr, to) == 0)
      vTo = vtemp;
  }    

  if(vFrom == NULL || vTo == NULL)
  {
    printf("Vertex Error !\n");
    free(aP);
    return ERR;
  }

  for(aPre=NULL, atemp=vFrom->pArc;atemp!=NULL; aPre=atemp, atemp=atemp->pNextArc)
  {
    if( g->compare(atemp->dest->dataPtr, to) == 0 )
    {
      printf("There is the same arc from %s to %s in the graph !\n", (char *)from, (char *)to);
      free(aP);
      return DUP;
    }  
  }

  aP->pNextArc = NULL;
  aP->dest = vTo;

  if(aPre==NULL)
    vFrom->pArc = aP;
  else  
    aPre->pNextArc = aP;
  (vFrom->outDegree)++;
  (vTo->inDegree)++;

  return NOR ;
}

int DeleteEdge(GRAPH *g, void *from, void *to)
{
  ARC *aPre, *aNext;
  VERTEX *vPre, *vNext;

  for(vPre=NULL, vNext=g->first; vNext!=NULL; vPre=vNext, vNext=vNext->pNextVertex)
  {
    if(g->compare(vNext->dataPtr, from) == 0 )
    {
      if(vNext->outDegree > 0)
      {
        for(aPre=NULL, aNext=vNext->pArc; aNext!=NULL; aPre=aNext, aNext=aNext->pNextArc)
        {
          if(g->compare(aNext->dest->dataPtr, to)==0){          
            aPre->pNextArc = aNext->pNextArc;
            (aNext->dest->inDegree)--;
            (vNext->outDegree)--;
            free(aNext);
            return NOR;
          }
        }
      }
      break;
    }
  }

  printf("There is no arc from %s to %s !\n", (char *)from, (char *)to);
  return ERR;
}

void DelGraph(GRAPH *g)
{
  ARC *aPre, *aNext;
  VERTEX *vPre, *vNext;

  for(vPre=NULL, vNext=g->first; vNext!=NULL; vPre=vNext, vNext=vNext->pNextVertex, free(vPre))
    for(aPre=NULL, aNext=vNext->pArc; aNext!=NULL; aPre=aNext, aNext=aNext->pNextArc, free(aPre));
    
  free(g);
}

void clearProcessedMark(GRAPH *g)
{
  VERTEX *temp;

  if(!g)
    return ;

  for( temp = g->first; temp!=NULL ; temp=temp->pNextVertex )
    temp->processed = false;

  return;  

}