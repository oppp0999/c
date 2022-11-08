typedef struct node {
    char *value;            // all void* types replaced by char*
    struct node *p_left;
    struct node *p_right;
}NODE;

void Preorder(NODE *root)
{
	if(root == NULL)
		return;

	printf("%s ", root->value);
	Preorder(root->p_left);
	Preorder(root->p_right);
}

void Inorder(NODE *root)
{
  if(root == NULL)
    return;
  Inorder(root->p_left);
  printf("%s ", root->value);
  Inorder(root->p_right);
}

void Postorder(NODE *root)
{
	if(root == NULL)
		return;

	Postorder(root->p_left);
	Postorder(root->p_right);
	printf("%s ", root->value);
}