int parent[MAX_VERTICES]; // 각 정점의 부모 노드
int num[MAX_VERTICES];    // 각 집합의 크기
 
// 초기화
void set_init(int n)
{
  int i;
   
  // 0 ~ n-1 인덱스까지 부모노드 배열은 모두 -1로
  // 집합의 크기 배열은 모두 1로 초기화한다.
  for (i = 0; i < n; i++)
  {
    parent[i] = -1;
    num[i] = 1;
  }
}
 
// 정점(vertex)이 속하는 집합을 반환한다.
int set_find(int vertex)
{
  int p, s, i = -1; // p: 부모노드
 
  // 루트노드까지 반복한다. p가 -1이 되면 반복문은 종료한다.
  // p가 -1이라는 건 현재 노드(i)가 루트라는 뜻이다.
  for (i = vertex; (p = parent[i]) >= 0; i = p);
 
  s = i;  // 루트노드 정보를 s에 저장
 
  // 모든 노드들(i로 순회)의 부모가 s(루트 노드)에 되도록 설정한다.
  for (i = vertex; (p = parent[i]) >= 0; i = p)
    parent[i] = s;
 
  return s; // 모든 노드의 부모인 루트를 반환한다.
}
 
// 두 개의 원소의 크기 정보 s1, s2를 받아 두 집합을 합친다.
void set_union(int s1, int s2)
{
  // 더 큰 쪽을 기준으로 집합을 합친다.
  if (num[s1] < num[s2])
  {
    // 집합 s2가 더 크다면
    parent[s1] = s2;  // s1의 부모를 s2로 설정
    num[s2] += num[s1]; // s2의 크기를 s1만큼 더해준다.
  }
  else
  {
    parent[s2] = s1;
    num[s1] += num[s2];
  }
}
