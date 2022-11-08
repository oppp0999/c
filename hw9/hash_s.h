#include <stdio.h>
#include <stdbool.h>

//해시테이블 구조체, 연결리스트
//연결리스트를 사용하여 충돌현상을 막습니다.
typedef struct hash_s{
    struct hash_s   *next;
    int             value;
}hash_t;

// 해시테이블 초기화 함수
void init_hashtable(hash_t **hashtable, int n)
{
    for (int i = 0; i < n; i++)
        hashtable[i] = NULL;
}

//해시테이블 메모리해제 함수
void deshash(hash_t **hashtable, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(hashtable[i]);
        hashtable[i] = NULL;
    }
}

// 지정된 해시값으로 변경하는 함수
int hash(int value, int n)
{
    int hs;

    hs = value % n;
    if (hs < 0)
        hs += n;
    return (hs);
}

//새로운 데이터가 들어올 때마다 노드를 생성하고 동적할당을 하여 충돌현상을 막습니다.
//새로운 노드 생성 하고 valude를 삽입
void add_index(hash_t **hashtable, int val)
{
    hash_t *new_node;

    new_node = (hash_t *)malloc(sizeof(hash_t));
    new_node->value = val;
    new_node->next = *hashtable;
    *hashtable = new_node;
}

//해시테이블 내에 값 찾기
bool hash_search(hash_t **hashtable, int val, int n)
{
    int hs;
    hash_t *finder;

    hs = hash(val, n);
    finder = hashtable[hs];
    while (finder != NULL)
    {
        if (finder->value == val)
            return true;
        finder = finder->next;
    }
    return false;
}

// 새로운 value를 해시테이블에 추가해주는 함수
void add_value(hash_t **hashtable, int val, int n)
{
    int hs;

    if (hash_search(hashtable, val, n) == true)
        return;
    hs = hash(val, n);
    while (*hashtable != NULL)
        *hashtable = (*hashtable)->next;
    add_index(&hashtable[hs], val);
}

// 해당 테이블 저장된 모든 value를 출력하는 함수
void print_index(hash_t **hashtable, int index, int n)
{
    hash_t *finder;

    finder = hashtable[index];

    if(index >= n){
      printf("not table\n");
      return;
    }
    if (finder == NULL)
    {
        printf("not data\n");
        return ;
    }
    printf("[%d]: ", index);
    while(finder != NULL)
    {
        printf("%d ", finder->value);
        finder = finder->next;
    }
    printf("\n");
}

// 해당 value가 저장된 노드를 삭제하는 함수
int delete_value(hash_t **hashtable, int val, int n)
{
    int hs;
    hash_t *temp;
    hash_t *finder;

    hs = hash(val, n);
    finder = hashtable[hs];
    if (finder == NULL)
        return false;
    if (hashtable[hs]->value == val)
    {
        temp = hashtable[hs]->next;
        free(hashtable[hs]);
        hashtable[hs] = temp;
        return true;
    }
    while (finder->next != NULL)
    {
        if ((finder->next)->value == val)
        {
            temp = (finder->next)->next;
            free(finder->next);
            finder->next = temp;
            return true;
        }
        finder = finder->next;
    }
    return false;
}