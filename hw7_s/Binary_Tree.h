#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Element;
typedef enum{false, true} bool;

typedef struct tTreeNode {
	Element data;
	struct tTreeNode *left, *right;
} TreeNode ;

TreeNode* CreateTree(TreeNode *left, Element item, TreeNode *right)
{
	TreeNode *pNewNode = (TreeNode*)malloc(sizeof(TreeNode));
	if(pNewNode == NULL)
		return NULL;

  pNewNode->data = item;

	pNewNode->left = left;
	pNewNode->right = right;

	return pNewNode;
}

bool IsEmpty(TreeNode *root)
{
  if(root==NULL)
    return true;
  else 
    return false;
}

TreeNode* LeftTree(TreeNode *root)
{
  if(IsEmpty(root))
    return NULL;
  else
    return root->left;  
}

TreeNode* RightTree(TreeNode *root)
{
  if(IsEmpty(root))
    return NULL;
  else
    return root->right;  
}

bool TreeData(TreeNode *root, Element *d)
{
  if(IsEmpty(root))
    return false;
  else{
    *d = root->data;
    return true;
  }  
}

void DestroyTree(TreeNode *root)
{
	if(root == NULL)
		return;

	if(root->left)
		DestroyTree(root->left);
	if(root->right)
		DestroyTree(root->right);
	
	free(root);
}