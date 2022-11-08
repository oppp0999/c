#include "Binary_Tree.h"
#include "Tree_Queue.h"

void linkTree(TreeNode** root, TreeNode* newNode, Queue *queue)
{
  TreeNode* front;

  if(!*root)
    *root = newNode;
  else if(!(*root)->left)
    linkTree(&((*root)->left), newNode, queue);
  else if(!(*root)->right)
    linkTree(&((*root)->right), newNode, queue);
  else{
    front = Front(queue);
    while(front->left && front->right){
        Dequeue(queue);
        front = Front(queue);
    }

    if( !front )
      return;
    else if(!front->left)
      front->left = newNode;
    else{
      front->right = newNode; 
      Dequeue(queue);
    }  
  }
  Enqueue(queue, newNode);

  return;
}

TreeNode* makeTree(char *str)
{
  int i, len=strlen(str);
  TreeNode* root=NULL;
  Queue *queue = NULL;

  queue = CreateQueue();

  for(i=0;i<len;i++)
    linkTree(&root, CreateTree(NULL, str[i], NULL), queue);

  DestroyQueue(queue);

  return root;
}

void Preorder(TreeNode *root)
{
	if(root == NULL)
		return;

	printf("%c", root->data);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder(TreeNode *root)
{
  if(root == NULL)
    return;
  Inorder(root->left);
  printf("%c", root->data);
  Inorder(root->right);
}

void Postorder(TreeNode *root)
{
	if(root == NULL)
		return;

	Postorder(root->left);
	Postorder(root->right);
	printf("%c", root->data);
}

void breadthFirst(TreeNode *root)
{
  Queue *queue = NULL;

  if(root == NULL)
      return;

  queue = CreateQueue();
  while(root){
    printf("%c", root->data);
    if(root->left) 
      Enqueue(queue, root->left);
    if(root->right) 
      Enqueue(queue, root->right);
    if(!IsEmptyQueue(queue))
      root = Dequeue(queue);
    else
      root = NULL;
  }
  DestroyQueue(queue);
}

int main(void) {
  TreeNode* root;
  char input[100];

  printf("Input a string : ");
  scanf(" %[^\n]s", input);
  root = makeTree(input);
  
  printf("\nPre-order : ");
  Preorder(root);

  printf("\n\nIn-order : ");
  Inorder(root);

  printf("\n\nPost-order : ");
  Postorder(root);

  printf("\n\nBreadth First : ");
  breadthFirst(root);
  printf("\n");

  return 0;
}