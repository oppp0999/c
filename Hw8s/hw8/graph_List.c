#include "Ad_List.h"
#include "Graph_Queue.h"

void proc(void* data)
{
  printf(" %s", (char *)data);
}

void DepthFirstTraversal(VERTEX *root, void (*process)(void *dataPtr))
{
	ARC *arc = NULL;

	if(root->processed)
		return;

	(*process)(root->dataPtr);
	root->processed = true;

	for(arc = root->pArc; arc != NULL; arc = arc->pNextArc){
		if(!arc->dest->processed)
		   DepthFirstTraversal(arc->dest, process);
	}
}

void BreadthFirstTraversal(VERTEX *root, void (*process)(void *dataPtr))
{
  Queue* qGraph;
  VERTEX *temp;
  ARC *atemp;

  if( (qGraph = CreateQueue()) == NULL ){
    printf("Can't create queue !\n");
    return;
  }

  Enqueue(qGraph, root);
  while( !IsEmptyQueue(qGraph) ){
    temp = Dequeue(qGraph);
    if(!temp->processed){
      (*process)(temp->dataPtr);
      temp->processed = true;
    }
    for(atemp = temp->pArc; atemp != NULL ; atemp=atemp->pNextArc)
      Enqueue(qGraph, atemp->dest);
  }
  DestroyQueue(qGraph);
}

bool makeGraph(GRAPH **g, int (*compare)(void* arg1, void* arg2))
{
  FILE *fp;
  char fname[20];
  char *from=NULL, *to=NULL, *start=NULL;

  printf("File name of a graph : ");
  scanf("%s", fname);
  if(!(fp = fopen(fname, "r")))
  {
    printf("Can't find the file, %s !\n", fname);
    return false;
  }

  start = (char *)malloc(INSIZE);
  if(!start)
  {
    printf("Memory Allocation Error!\n");
    fclose(fp);
    return false;
  }

  if( fscanf(fp, "%s", start) == EOF )
  {
    printf("There is no data !\n");
    fclose(fp);
    free(start);
    return false;
  }

  if( (*g=CreateGraph(start, compare)) == NULL )
  {
    printf("Can't make a grpah !\n");
    fclose(fp);
    free(start);
    return false;
  }

  do{

    from = (char *)malloc(INSIZE);
    to = (char *)malloc(INSIZE);

    if(from == NULL || to == NULL)
    {
      printf("Memory Allocation Error!\n");
      fclose(fp);
      DelGraph(*g);
      if(from)
        free(from);
      if(to)
        free(to);
      return false;
    }

    if( fscanf(fp, "%s", from) == EOF )
      break;
    if( fscanf(fp, "%s", to) == EOF )
    {
      printf("Input error!\n");
      fclose(fp);
      DelGraph(*g);
      free(from);
      free(to);
      return false;
    } 

    if( InsertVertex(*g, from) == ERR || InsertVertex(*g, to) == ERR || AddEdge(*g, from, to) == ERR )
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
  DepthFirstTraversal(g->first, proc);
  
  clearProcessedMark(g);

  printf("\nBreadth First Traversal :");
  BreadthFirstTraversal(g->first, proc); 

  DelGraph(g);

  return 0;
}