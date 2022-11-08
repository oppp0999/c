#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"

#define MAXLEN 100

//struct for node


//use typedef to make calling the compare function easier
typedef int (*Compare)(const char *, const char *);

//inserts elements into the tree
void insert(char* key, struct node** leaf, Compare cmp)
{
    int res;
    if( *leaf == NULL ) {
        *leaf = (struct node*) malloc( sizeof( struct node ) );
        (*leaf)->value = malloc( strlen (key) +1 );     // memory for key
        strcpy ((*leaf)->value, key);                   // copy the key
        (*leaf)->p_left = NULL;
        (*leaf)->p_right = NULL;
        //printf(  "\nnew node for %s" , key);
    } else {
        res = cmp (key, (*leaf)->value);
        if( res < 0)
            insert( key, &(*leaf)->p_left, cmp);
        else if( res > 0)
            insert( key, &(*leaf)->p_right, cmp);
        else                                            // key already exists
            printf ("Key '%s' already in tree\n", key);
    }
}

//compares value of the new node against the previous node
int CmpStr(const char *a, const char *b)
{
    return (strcmp (a, b));     // string comparison instead of pointer comparison
}

char *input( void )
{
    static char line[MAXLEN+1];       // where to place key    
    printf("Please enter a string : ");
    fgets( line, sizeof line, stdin );
    return ( strtok(line, "\n" ));    // remove trailing newline
}

//recursive function to print out the tree inorder
void in_order(struct node *root)
{
    if( root != NULL ) {
        in_order(root->p_left);
        printf("   %s\n", root->value);     // string type
        in_order(root->p_right);
    }
}

//searches elements in the tree
void search(char* key, struct node* leaf, Compare cmp)  // no need for **
{
    int res;
    if( leaf != NULL ) {
        res = cmp(key, leaf->value);
        if( res < 0)
            search( key, leaf->p_left, cmp);
        else if( res > 0)
            search( key, leaf->p_right, cmp);
        else
            printf("\n'%s' found!\n", key);     // string type
    }
    else printf("\nNot in tree\n");
    return;
}

void delete_tree(struct node** leaf)
{
    if( *leaf != NULL ) {
        delete_tree(&(*leaf)->p_left);
        delete_tree(&(*leaf)->p_right);
        free( (*leaf)->value );         // free the key
        free( (*leaf) );
    }
}

//displays menu for user
void menu()
{
    printf("\nPress 'i' to insert an element\n");
    printf("Press 's' to search for an element\n");
    printf("Press 'p' to print the tree inorder\n");
    printf("Press 'f' to destroy current tree\n");
    printf("Press 'q' to quit\n");
}

int main()
{
    NODE *p_root = NULL;
    char *value;
    char option = 'x';



    while( option != 'q' ) {
        //displays menu for program
        menu();
        scanf("%c", &option);

        //gets the char input to drive menu
        getchar();          // instead of two getchar() calls

        if( option == 'i') {
            value = input();
            printf ("Inserting %s\n", value);
            insert(value,  &p_root, (Compare)CmpStr);
        }
        else if( option == 's' ) {
            value = input();
            search(value, p_root, (Compare)CmpStr);     // no need for **
        }
        else if( option == 'p' ) {
            in_order(p_root);
        }
        else if( option == 'f' ) {
            delete_tree(&p_root);
            printf("Tree destroyed");
            p_root = NULL;
        }
        else if( option == 'q' ) {
            printf("Quitting");
        }
    }

    printf("pre");
    Preorder(p_root);
    printf("\nin");
    Inorder(p_root);
    printf("\npost");
    Postorder(p_root);


return 0;
}