07. Dijkstra의 최단 경로 함수를 그래프가 인접 리스트로 표현되어 있다고 가정하고 재작성하라.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphNode {
	int vertex;
	int weight;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	struct GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int u, int v,int w) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점의 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->weight = w;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (p != NULL) {
			printf("-> %d", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];		/* 방문한 정점 표시 */

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void print_status(GraphType* g) {
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	GraphNode* p = g->adj_list[start];

	for (i = 0; i < g->n; i++) {//초기화
		distance[i] = INF;
		found[i] = FALSE;
	}
	while (p != NULL) {	//초기화
		distance[p->vertex] = p->weight;
		p = p->link;
	}

	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				p = g->adj_list[u];
				while (p != NULL) {
					if (p->vertex == w) break;
					else {
						p = p->link;
					}
				}
				if (p != NULL) {
					if (distance[u] + p->weight < distance[w])
						distance[w] = distance[u] + p->weight;
				}

			}

		}
	}
}

int main(void){
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 6; i++) {
		insert_vertex(g, i);
	}
	insert_edge(g, 0, 1, 50);
	insert_edge(g, 0, 2, 45);
	insert_edge(g, 0, 3, 10);
	insert_edge(g, 1, 2, 10);
	insert_edge(g, 1, 3, 15);
	insert_edge(g, 2, 4, 30);
	insert_edge(g, 3, 0, 20);
	insert_edge(g, 3, 4, 15);
	insert_edge(g, 4, 1, 20);
	insert_edge(g, 4, 2, 35);
	insert_edge(g, 5, 4, 3);

	shortest_path(g, 0);

}