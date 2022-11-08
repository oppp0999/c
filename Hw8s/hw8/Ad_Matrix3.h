#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INSIZE 2
#define MAX_NODE 10

#define ERR 0
#define DUP 1
#define NOR 2

#define INFINI 1000

typedef enum{false, true} bool;

typedef struct vertex
{
  void* dataPtr;
  int degree;
  bool processed;
} VERTEX;

typedef struct arc
{
  int weight;
  int from;
  int to;
} ARC;

typedef struct
{
  int count;
  VERTEX *vector;
  int start;
  int** adjM;
  int (*compare)(void* arg1, void* arg2);
} GRAPH;

int comp(void* arg1, void* arg2)
{
  return strcmp((char *)arg1, (char *)arg2) ;
}

void DisplayGraph(GRAPH *g)
{
  int i, j;

  if(!g)
    return ;

  printf("\nThe graph is :");
  for(i=0; i<g->count ; i++){
    printf("\n%s :", (char *)(g->vector[i]).dataPtr);
    for(j=0; j<g->count ; j++)
    {
      if(g->adjM[i][j] > 0)
        printf(" %s (%d)", (char *)(g->vector[j]).dataPtr, g->adjM[i][j]);
    }
  }
  printf("\n");
  return ;
}

GRAPH* CreateGraph(int start, char **node, int count, int (*compare)(void* arg1, void* arg2))
{
  GRAPH *temp=NULL;
  int i, j;
  
  if( (temp = (GRAPH *)malloc(sizeof(GRAPH))) )
  {
    temp->count = count;
    temp->start = start;
    temp->compare = compare;
    if( !(temp->vector = (VERTEX *)malloc(count*sizeof(VERTEX)) ) ||
    !(temp->adjM = (int **)malloc(count*sizeof(int *)) ) )
    {
      free(temp);
      return NULL;
    }
    if( !(temp->adjM = (int **)malloc(count*sizeof(int *)) ) )
    {
      free(temp->vector);
      free(temp);
      return NULL;
    }
    for(i=0; i<count; i++){
      temp->adjM[i] = (int *)malloc(count*sizeof(int));
      if(!temp->adjM[i]){
        free(temp->vector);
        while(--count>=0)
          free(temp->adjM[count]);
        free(temp->adjM);  
        free(temp);
        return NULL;
      }
    }

    for(i=0; i<count; i++)
      for(j=0; j<count ; j++)
        temp->adjM[i][j] = 0;

    for(i=0; i<count; i++){
      (temp->vector[i]).degree = 0;
      (temp->vector[i]).processed = false;
      (temp->vector[i]).dataPtr = node[i];
    }  
  }

  return temp;
}

int AddEdge(GRAPH *g, void *from, void *to, int weight)
{
  int i, j;
  int f, t;

  for(i=0, f=-1, t=-1; i<g->count && (f==-1 || t==-1) ; i++)
  {
    if(g->compare((g->vector[i]).dataPtr, from) == 0)
      f = i;
    if(g->compare((g->vector[i]).dataPtr, to) == 0)
      t = i;
  }    

  if( f == -1 || t == -1 ){
    printf("Can't add an arc from %s to %s !\n", (char *)from, (char *)to);
    return ERR;
  }
  else if( g->adjM[f][t] == 1 )
  {
    printf("There is already an arc from %s to %s !\n", (char *)from, (char *)to);
    return DUP;
  }

  g->adjM[f][t] = weight;
  g->adjM[t][f] = weight;
  ((g->vector[f]).degree)++;
  ((g->vector[t]).degree)++;

  return NOR ;
}

int DeleteEdge(GRAPH *g, void *from, void *to)
{
  int i, j;
  int f, t;

  for(i=0, f=-1, t=-1; i<g->count && (f!=-1 || t!=-1) ; i++)
  {
    if(g->compare(g->vector[i].dataPtr, from) == 0)
      f = i;
    if(g->compare(g->vector[i].dataPtr, to) == 0)
      t = i;
  }

  if(i == g->count || g->adjM[i][j] == 0){
    printf("There is no arc from %s to %s !\n", (char *)from, (char *)to);
    return ERR;
  }

  g->adjM[i][j] = 0;
  (g->vector[i].degree)--;
  (g->vector[j].degree)--;
  return NOR;

}

void DelGraph(GRAPH *g)
{
  int i;

  for(i=0; i<g->count;i++)
    free(g->vector[i].dataPtr);
  free(g->vector);
  free(g->adjM);
    
  free(g);
}

void clearProcessedMark(GRAPH *g)
{
  VERTEX *temp;
  int i;

  if(!g)
    return ;

  for( i=0, temp = g->vector; i<g->count ; i++ )
    temp[i].processed = false;

  return;  
}

bool IsConnected(GRAPH *g)
{
  int i, j;
  bool connect;

  if(!g)
    return false;

  for(i=0, connect=false; i<g->count-1 ; i++){
    for(j=i+1; j<g->count; j++)
      if(g->adjM[i][j] > 0)
        connect = true;
    if(connect == false)
      return false;    
  }

  return true;  
}