#include "Ad_Matrix3.h"

void proc(void* data)
{
  printf(" %s", (char *)data);
}

bool makeGraph(GRAPH **g, int (*compare)(void* arg1, void* arg2))
{
  FILE *fp;
  char fname[20], temp[INSIZE], *ptemp;
  char *node[MAX_NODE];
  char from[INSIZE], to[INSIZE] ;
  int count, i, j, start, weight;

  printf("File name of a graph : ");
  scanf("%s", fname);
  if(!(fp = fopen(fname, "r")))
  {
    printf("Can't find the file, %s !\n", fname);
    return false;
  }

  for(count=0; fscanf(fp, "%s", temp)!=EOF ;)
  {
    if( isdigit(temp[0]) )
      continue;
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

    if( fscanf(fp, " %[^\n]s", fname) == EOF )
      break;

    if( (ptemp = strtok(fname, " ")) ){
      strcpy(from, ptemp);
      if( (ptemp = strtok(NULL, " ")) ){
        strcpy(to, ptemp);
        if( (ptemp = strtok(NULL, " ")) )
          weight = atoi(ptemp);
      }  
    }  
    if(weight == -1)
    {
      printf("Input error!\n");
      fclose(fp);
      DelGraph(*g);
      return false;
    }

    if( AddEdge(*g, from, to, weight) == ERR )
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

bool In_vSet(int *vSet, int n, int v)
{
  for(int i=0; i<n; i++)
    if(vSet[i]==v)
      return true;

  return false;
}

void MST(GRAPH *g)
{
  int vSet[g->count];
  ARC aSet[g->count-1];
  int aMin, from, to, i, j;
  int n_vertex=0, n_arc=0;

  vSet[n_vertex++] = g->start;
  while(n_arc < (g->count-1)){
    for(i=0, aMin=-1; i<n_vertex ; i++)
    {
      for(j=0; j< g->count ; j++)
      {
        if( g->adjM[vSet[i]][j] > 0 && !In_vSet(vSet, n_vertex, j) ){
          if( (aMin == -1) || ( aMin > 0 && (aMin >= g->adjM[vSet[i]][j]) )){
            aMin = g->adjM[vSet[i]][j];
            from = vSet[i];
            to = j;
          }  
        }
      }
    }
    if(aMin > 0)
    {
      printf("%s %s (%d)\n", (char *)g->vector[from].dataPtr, (char *)(char *)g->vector[to].dataPtr, aMin);
      vSet[n_vertex++] = to;
      aSet[n_arc].weight = aMin; 
      aSet[n_arc].from = from;
      aSet[n_arc++].to = to;
    }    
  }
}

int choose(GRAPH *g, bool *found)
{
  int i, j, k, aMin, to=-1;

  for(i=0, aMin=-1; i<g->count ; i++)
  {
    if(found[i]){
      for(j=0; j<g->count ; j++)
      {
        if(!found[j] && g->adjM[i][j] > 0 && (aMin == -1 || aMin >= g->adjM[i][j] )){
            aMin = g->adjM[i][j];
            to = j;
        }
      }
    }  
  } 

  return to;
}

void SP(GRAPH *g)
{
  int i, u, w;
  bool found[g->count];
  int distance[g->count];

  for(i = 0; i < g->count ; i++){
	  found[i] = false;		                  // if found[i] == TRUE, i is in S
	  distance[i] = g->adjM[g->start][i];		// v : source vertex
    if(distance[i]==0)
      distance[i] = INFINI;
  }

  found[g->start] = true;		// initially S = { v }
  distance[g->start] = 0;
  
  printf("\n");
  for(u=0; u<g->count; u++)
  {
    if( g->start != u )
      printf("%s %s : %d\n", (char *)g->vector[g->start].dataPtr, (char *)g->vector[u].dataPtr, distance[u]);
  }     

  for(i = 0; i < g->count-1 ; i++){
	  u = choose(g, found);  // find a vertex with minimum distance
	  found[u] = true;		                    // add u into S
	  for(w = 0; w < g->count; w++){	        // adjust distances to the vertices not in S
		  if(!found[w]){
       if( g->adjM[u][w] > 0 && distance[u]+g->adjM[u][w] < distance[w])
		    distance[w] = distance[u]+g->adjM[u][w];
      }  
	  }

    printf("\n");
    for(u=0; u<g->count; u++)
    {
      if( g->start != u )
        printf("%s %s : %d\n", (char *)g->vector[g->start].dataPtr, (char *)g->vector[u].dataPtr, distance[u]);
    }     
  }

}

int main(void) {
  GRAPH *g;
  int choice;
  
  if( !makeGraph(&g, comp) )
    return 0;

  if( IsConnected(g) )
  {
    printf("\nMinimum spanning tree :\n");
    MST(g);

    printf("\nShortest path from %s :\n", (char *)g->vector[g->start].dataPtr);
    SP(g);
  }
  else
    printf("The graph is not connected!\n");

  DelGraph(g);

  return 0;
}