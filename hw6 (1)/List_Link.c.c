//#include "List_Array.h"
#include "List_Link.h"
  
int main(){
  int input=-1;
  bool found;
  List* list=NULL;
  ListNode *pPre = NULL, *pLoc = NULL;

  if((list = createList()) == NULL ){
    printf("Fail to allocate for List!\n");
    return 0;
  }

  printf("In (0), Search (1), Out (2), Exit (3) : ");
  while( scanf("%d", &input) && input != 3 )
  {
    switch(input){
      case 0 :
        printf("In : ");
        scanf("%d", &input);
        addNodeList(list, input);
        FullList(list);
        break;
      case 1 :
        printf("Search : ");
        scanf("%d", &input);
        found = _searchList(list, &pPre, &pLoc, input);
        if(found)
          printf("My List has %d !\n", input);
        else 
          printf("My List does not have %d !\n", input); 
        FullList(list);   
        break;
      case 2 : 
        printf("Out : ");
        scanf("%d", &input);
        removeList(list, input);
        FullList(list);
        break;
      default :
        printf("Input Error !\n");
        break;
    }
    printf("\nIn (0), out (1), exit (2) : ");
  }

  destroyList(list);

  return 0;
}  