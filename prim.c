#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h> // memset
#define MAX_VERTEX 10
#define MAX_QUEUE 11
#define INF 1000L
/*------------Prim------------*/
typedef struct EDGE {
    int n;
    int** key;
}Edge;
/*----------------------------*/
/*---------Graph ADT---------*/
Edge* Init_Edge(int max_vertex); // 이중 포인터를 사용하기 위해 초기화 한다.
void Init_Graph(Edge* e, int n); // n을 최대값으로 갖는 랜덤 변수를 생성하고, 간선 정보를 생성한다.
void Insert_Edge(Edge* e, int v1, int v2, int weight); // 생성된 랜덤 가중치를 사용해 간선정보를 설정한다.
int Check_Weight(Edge* e, int v1, int v2); // 특정 간선의 가중치를 반환한다.
void Prim(Edge* e, int start_vertex); // Prim 알고리즘을 실행한다.
/*---------------------------*/
void Add_Queue(int n); // Prim 알고리즘에서 그래프에 추가된 모든 정점이 큐에 저장됐다가 하나씩 빠져나오며연결된 최소의 간선을 찾는다
int Delete_Queue(void); // 큐에 저장된 데이터를 반환한다.
/*---------------------------*/
/*-----------Queue-----------*/
int front = 0;
int rear = 0;
int queue[MAX_QUEUE];
/*---------------------------*/ 
/*-------Lecture Note-------*/
// 강의 노트에 있는 Prim 알고리즘
int selected[MAX_VERTEX];
int dist[MAX_VERTEX];
int get_min_vertex(int n);
void prim(Edge* e, int s, int n);
/*--------------------------*/
int selected_gm[MAX_VERTEX];
int main(void) {
    Edge* e = Init_Edge(MAX_VERTEX);
    Init_Graph(e, 300);
#if 0
    int v1 = 0;
    int v2 = 0;
    printf("[%d] and [%d]'s key: %d\n", v1, v2, e->key[v1][v2]);
    printf("[%d] and [%d]'s key: %d\n", v2, v1, e->key[v2][v1]);
#endif
    //prim(e, 0, MAX_VERTEX);
    Prim(e, 0);
    return 0;
}

/*-------Lecture Note-------*/
int get_min_vertex(int n) {
    // 선택된 애들이 아닌 애들 중에 가장 dist가 작은 애를 반환한다.
    int v, i;
    v = -1;
    for (i = 0; i < n; i++)
        if (!selected[i]) { // 그래프에 선택되지 않은 정점을 발견할 때까지 반복합니다.
            v = i;
            break;
        }
    for (i = 0; i < n; i++)
        if (!selected[i] && (dist[i] < dist[v]))
            // 선택되지 않은 간선 중에 더 작은 간선이 발견될때까지 반복한다.
            v = i;
    return v;
}
void prim(Edge* e, int s, int n) {
    // s는 시작점, n은 전체 갯수
    int i, u, v;
    for (u = 0; u < n; u++) {
        dist[u] = INF;
        selected[u] = 0;
    }
    dist[s] = 0;

    for (i = 0; i < n; i++) {
        u = get_min_vertex(n); // 무조건 처음엔 시작 정점이 선택된다.
        selected[u] = 1;    // 항상 그래프의 모든 정점 중에 선택되지 않고, 제일 가중치가 작은 정점이선택된다.
        if (dist[u] == INF) // 위에서 선택된 애가 제일 작은데 무한대면, 반복문을 중지 합니다.
            return;
        printf("%d ", u);
        for (v = 0; v < n; v++)
            if (e->key[u][v] != INF) // 시작 정점과 다른 정점이 끊기지 않고,
                if (!selected[v] && e->key[u][v] < dist[v]) {
                    // 이전에 선택된 적이 없고, 다른 가중치보다 시작점에서 가는게 빠를 때
                    dist[v] = e->key[u][v]; // 시작점에서 가는걸 dist로 갱신한다.
//                    printf("[u -- v] == [%d -- %d] == dist[%d]\n", u, v, dist[v]);
                }
        // 해당 for 문을 시작점과 모든 정점에 대해 진행한다.
        // 자연스럽게 끊긴 애들은 무한대가 유지되어 위에 if문으로 제외된다.
    }
    printf("\n\nShow each weight from start vertex to the others\n");

    for (i = 0; i < n; i++) {
        printf("dist[%d] = %d\n", i, dist[i]);
    }
    printf("\n\n");

}

/*--------------------------*/
Edge* Init_Edge(int max_vertex) {// MAX_VERTEX*MAX_VERTEX 크기의 key 행렬 생성
    Edge* e;
    e = (Edge*)malloc(sizeof(Edge));
    e->n = 0;
    e->key = (int**)malloc(sizeof(int*) * max_vertex);
    for (int i = 0; i < max_vertex; i++) {
        // 이중 포인터를 이중 배열로 사용하기 위해 메모리를 할당한다.
        // 즉, 10x10 배열을 사용할 때, 10개의 행을 만들어주는 것과 같다.
        e->key[i] = (int*)malloc(sizeof(int) * max_vertex);
        // 여기선 각 행 마다 10개의 열을 만들어주는 것과 같다.
        memset(e->key[i], 0, sizeof(int) * max_vertex);
        // 할당된 메모리를 NULL로 초기화 해준다.
    }
    return e;
}


void Init_Graph(Edge* e, int n) {
    //    srand((unsigned int)time(NULL));
    srand((unsigned int)10);
    int ran_num;
    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = i; j < MAX_VERTEX; j++) {
            if (j != i) {
                // i, j를 잇는 간선 정보를 생성한다.
                // i->j 가 한번 생기고, j->i가 또 한번 생기는데
                // 결국 후자로 초기화된다
                ran_num = (rand() % n) + 1;
                printf("[%d] and [%d]: %d\n", i, j, ran_num);
                Insert_Edge(e, i, j, ran_num);
            }
            else {
                // 같은 정점에 대한 간선은 없으므로, 가중치를 0으로 설정한다.
                printf("[%d] and [%d]: %d\n", i, j, 0);
                Insert_Edge(e, i, j, 0);
            }
        }
        printf("Finish [%d]\n\n", i);
    }
    printf("\nInit graph complete\n\n");

}


void Insert_Edge(Edge* e, int v1, int v2, int weight) {

    // 랜덤하게 생성된 가중치를 이용해, v1과 v2를 잇는 간선 정보를 설정한다.
    e->key[v1][v2] = weight;
    e->key[v2][v1] = weight;
}

int Check_Weight(Edge* e, int v1, int v2) {

    int tmp;

 

    tmp = e->key[v1][v2];

 

    return tmp;

}

 

void Prim(Edge* e, int start_vertex) {

    int u = start_vertex;
    if (e->n == 0) {
        Add_Queue(u);    // start_vertex를 큐에 저장한다.
        for (int i = 0; i < MAX_VERTEX; i++) {
            selected_gm[i] = 0;
        }
        selected_gm[u] = 1;
        e->n++;
        Prim(e, start_vertex);    // 다시 prim을 실행한다. (재귀함수)
    }
    else if (e->n <= MAX_VERTEX) {
        int a;
        int cur;
        int tmp = 1000;
        int v1, v2;
        v1 = -1;
        v2 = -1;
        for (int i = 0; i < e->n; i++) {
            // e->n까지 큐에 있는 데이터를 가져온다.
            // 즉, 큐에 있는 모든 데이터가 나올 때까지 반복한다.
            a = Delete_Queue();
            for (int j = 0; j < MAX_VERTEX; j++) {
                // 모든 정점에 대해 큐에서 나온 정점과의 가중치를 검사한다.
                if (selected_gm[j] == 0) {
                    cur = Check_Weight(e, a, j); // 가중치를 반환하고
                    if (cur < tmp) {
                        // 최솟값을 찾기 위해 검사 이전까지의 최소값과 비교한다.
                        v1 = a;
                        v2 = j;
                        tmp = cur; // 최소값을 갱신해준다.
                    }
                }
            }
            Add_Queue(a);
            // 사용했던 걸 다시 큐에 넣어준다
            // 나중에 연결된 모든 정점에 대해 또 검사를 해줘야하기 때문에 빼냈던 데이터를 다시 큐에 저장한다.
        }
        if (v1 != -1 && v2 != -1) {
            printf("[%d] and [%d] are connected: %3d\n", v1, v2, e->key[v1][v2]);

            Add_Queue(v2); // 최소 가중치를 가졌던 정점을 큐에 추가한다. (그래프에도 추가된다는 의미를가진다.)
            selected_gm[v2] = 1;
            e->n++;

        }
        if(e->n != MAX_VERTEX)
            Prim(e, start_vertex);
        // 마찬가지로 재귀 함수를 활용한다.
    }
}
// 항상 front가 가리키는 배열은 비어있다.
void Add_Queue(int n) {
    if ((rear + 1) % MAX_QUEUE == front) {
        // puts("Queue is full.");
    }
    else {
        rear = (rear + 1) % MAX_QUEUE;
        queue[rear] = n;
        // 1번부터 찬다.
    }
}

int Delete_Queue(void) {
    int tmp = -1;
    if (front == rear) {
        // puts("Queue is empty.");
    }
    else {
        front = (front + 1) % MAX_QUEUE;
        tmp = queue[front];
    }
    return tmp;
}