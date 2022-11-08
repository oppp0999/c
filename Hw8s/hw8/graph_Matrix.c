#include "Ad_Matrix.h"
#include "Graph_Queue_Matrix.h"

void proc(void* data)
{
  printf(" %s", (char *)data);
}

void DepthFirstTraversal(GRAPH *g, int root, void (*process)(void *dataPtr))
{
	int i, j;

	if(g->vector[root].processed)
		return;

	(*process)(g->vector[root].dataPtr);
	g->vector[root].processed = true;

	for( j=0; j<g->count; j++ ){
		if(g->adjM[root][j]==1 && !g->vector[j].processed)
		   DepthFirstTraversal(g, j, process);
	}
}

void BreadthFirstTraversal(GRAPH *g, void (*process)(void *dataPtr))
{
  Queue* qGraph;
  int temp;
  int i;

  if( (qGraph = CreateQueue()) == NULL ){
    printf("Can't create queue !\n");
    return;
  }

  Enqueue(qGraph, g->start);
  while( !IsEmptyQueue(qGraph) ){
    temp = Dequeue(qGraph);
    if(!g->vector[temp].processed){
      (*process)(g->vector[temp].dataPtr);
      g->vector[temp].processed = true;
    }
    for(i=0; i<g->count ; i++){
      if(g->adjM[temp][i] == 1)
        Enqueue(qGraph, i);
    }  
  }
  DestroyQueue(qGraph);
}


bool makeGraph(GRAPH **g, int (*compare)(void* arg1, void* arg2))
{
  FILE *fp;
  char fname[20], temp[INSIZE];
  char *node[MAX_NODE];
  char from[INSIZE], to[INSIZE] ;
  int count, i, j, start;

  printf("File name of a graph : ");
  scanf("%s", fname);
  if(!(fp = fopen(fname, "r")))
  {
    printf("Can't find the file, %s !\n", fname);
    return false;
  }

  for(count=0; fscanf(fp, "%s", temp)!=EOF ;)
  {
    for(i=0;i<count;i++)
      if(!strcmp(node[i], temp))
        break;
    if(count==0 || i==count){
      node[count] = (char *)malloc(INSIZE);
      if(!node[count])
      {
        printf("Memory Allocation Error!\n");
        while((--count)>=0)
          free(node[count]);
        fclose(fp);
        return false;
      }
      strcpy(node[count++],temp);  
    }   
  }

  for(i=0; i<count;i++)
    for(j=i+1; j<count ; j++)
      if(strcmp(node[i], node[j])>0)
      {
        strcpy(temp, node[i]);
        strcpy(node[i], node[j]);
        strcpy(node[j], temp);
      }

  fseek(fp, 0, SEEK_SET);

  if( fscanf(fp, "%s", temp) == EOF )
  {
    printf("There is no data !\n");
    while((--count)>=0)
      free(node[count]);
    fclose(fp);
    return false;
  }

  for(i=0; i<count; i++)
  {
    if(!strcmp(node[i], temp))
    {
      start = i;
      break;
    }  
  }

  if( (*g=CreateGraph(start, node, count, compare)) == NULL )
  {
    printf("Can't make a grpah !\n");
    fclose(fp);
    while((--count)>=0)
      free(node[count]);
    return false;
  }

  do{

    if( fscanf(fp, "%s", from) == EOF )
      break;
    if( fscanf(fp, "%s", to) == EOF )
    {
      printf("Input error!\n");
      fclose(fp);
      DelGraph(*g);
      return false;
    } 

    if( AddEdge(*g, from, to) == ERR )
    {
      fclose(fp);
      DelGraph(*g);
      return false;
    }

  } while(1);

  fclose(fp);
  DisplayGraph(*g);

  return true;
}

int main(void) {
  GRAPH *g;
  int choice;
  
  if( !makeGraph(&g, comp) )
    return 0;

  printf("\nDepth First Traversal :");
  DepthFirstTraversal(g, g->start, proc);
  
  clearProcessedMark(g);

  printf("\nBreadth First Traversal :");
  BreadthFirstTraversal(g, proc); 

  DelGraph(g);

  return 0;
}