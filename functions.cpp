#include <iostream>
#include "functions.hpp"
using namespace std;


int findHeight(node* ptr)
{
    return (ptr==NULL ? -1 : ptr->height);
}

int findMax(int h1,int h2)
{
    return (h1>h2 ? h1 : h2);
}


/* Return the Balance Factor of a node (height of left subtree - height of right subtree) */ 
int getBalanceFactor(node* ptr)
{

    if(ptr==NULL)
        return 0;
    int lHeight=findHeight(ptr->left);
    int rHeight=findHeight(ptr->right);

    return lHeight-rHeight;
}



node* leftRotate(node* ptr)
{
    node* leftOfPtr=ptr->left;
    node* migrate=leftOfPtr->right;

    leftOfPtr->right=ptr;
    ptr->left=migrate;

    ptr->height=findMax(findHeight(ptr->left),findHeight(ptr->right))+1;
    leftOfPtr->height=findMax(findHeight(leftOfPtr->left),findHeight(leftOfPtr->right))+1;

    return leftOfPtr;
}

node* rightRotate(node* ptr)
{
    node* rightOfPtr=ptr->right;
    node* migrate=rightOfPtr->left;

    rightOfPtr->left=ptr;
    ptr->right=migrate;

    ptr->height=findMax(findHeight(ptr->left),findHeight(ptr->right))+1;
    rightOfPtr->height=findMax(findHeight(rightOfPtr->left),findHeight(rightOfPtr->right))+1;

    return rightOfPtr;
}



/* Insert a node with the given value to the root of the AVL tree */
node* insert(node* ptr,int value)
{
    if(ptr==NULL)
    {
        ptr = new node;
        ptr->data=value;
        ptr->height=0;
        ptr->right=NULL;
        ptr->left=NULL;
		cout << endl << value << " inserted to the AVL Tree.";
        return ptr;
    }
    else if(ptr->data>value)
    {
        ptr->left=insert(ptr->left,value);
    }
    else if(ptr->data<value)
    {
        ptr->right=insert(ptr->right,value);
    }

    ptr->height=findMax(findHeight(ptr->right),findHeight(ptr->left))+1;
    int balanceFactor=getBalanceFactor(ptr);

    if(balanceFactor<=-2 && value>ptr->right->data)
    {
        return rightRotate(ptr);
    }
    if(balanceFactor>=2 && value<ptr->left->data)
    {
        return leftRotate(ptr);
    }
    if(balanceFactor<=-2 && value<ptr->right->data)
    {
        ptr->right=leftRotate(ptr->right);
        return rightRotate(ptr);
    }
    if(balanceFactor>=2 && value>ptr->left->data)
    {
        ptr->left=rightRotate(ptr->left);
        return leftRotate(ptr);
    }


    return ptr;

}


/* Prints inorder traversal of the AVL tree */
void inorder(node* ptr)
{
    if(ptr!=NULL)
    {
        inorder(ptr->left);
        cout<<ptr->data<<" ";
        inorder(ptr->right);
    }
}


/* Search a given value in the AVL tree */
void search(node* ptr,int get)
{
    if(ptr==NULL)
    {
        cout<<"The value "<<get<<" is not in the BST.\n";
        return;
    }
    if(get<ptr->data)
    {
        search(ptr->left,get);
    }
    else if(get>ptr->data)
    {
        search(ptr->right,get);
    }
    else
    {
        cout<<"The value "<<get<<" is in the BST. Height is "<<ptr->height<<endl;
    }
}


/* Recursive function to update the height of every node in the Tree */ 
int updateHeight(node* ptr)
{
    if(ptr==NULL)
    {
        return -1;
    }
    int lHeight=updateHeight(ptr->left);
    int rHeight=updateHeight(ptr->right);

    ptr->height=findMax(lHeight,rHeight)+1;
    return ptr->height;
}


/* Delete a node from the AVL tree and perform the neccessary rotations to balance the tree */
node* remove(node* ptr,int get)
{
    if(ptr==NULL)
    {
        cout<<"\n\nThe value is not in the AVL Tree.";
        return ptr;
    }
    else if(get<ptr->data)
    {
        ptr->left=remove(ptr->left,get);
    }
    else if(get>ptr->data)
    {
        ptr->right=remove(ptr->right,get);
    }
    else if( ptr->right!=NULL && ptr->left!=NULL )
    {
        
        node *successor;
        successor=ptr->right;
        while(successor->left!=NULL)
        {
            successor=successor->left;
        }
        ptr->data=successor->data;
        ptr->right=remove(ptr->right,successor->data);
    }
    else
    {
        node* oldNode=ptr;
        if(ptr->right==NULL && ptr->left==NULL)
        {
            ptr=NULL;
        }
        else if(ptr->right==NULL)
        {
            ptr=ptr->left;
        }
        else
        {
            ptr=ptr->right;
        }
        delete oldNode;
		cout << "\n\n" << get << " deleted from the AVL tree.\n";
        return ptr;
    }
    ptr->height=findMax(findHeight(ptr->right),findHeight(ptr->left))+1;
    int balanceFactor=getBalanceFactor(ptr);

    if(balanceFactor<=-2 && getBalanceFactor(ptr->right)<=0)
    {
        return rightRotate(ptr);
    }
    if(balanceFactor>=2 && getBalanceFactor(ptr->left)>=0)
    {
        return leftRotate(ptr);
    }
    if(balanceFactor<=-2 && getBalanceFactor(ptr->right)>0)
    {
        ptr->right=leftRotate(ptr->right);
        return rightRotate(ptr);
    }
    if(balanceFactor>=2 && getBalanceFactor(ptr->left)<0)
    {
        ptr->left=rightRotate(ptr->left);
        return leftRotate(ptr);
    }
    return ptr;
}



/* A sub-routine for printing the given level in a level order traversal */
void printGivenLevel(struct node* root, int level, int level1)
{
	if (root == NULL)
    {
        for(int i=0;i<=level1;i++)
            cout<<" ";
        cout<<"x";
        for(int i=0;i<=level1;i++)
            cout<<" ";
        return;
    }
		
	if (level == 1)
    {
        for(int i=0;i<=level1;i++)
            cout<<" ";
        cout<<root->data<<"";
        for(int i=0;i<=level1;i++)
            cout<<" ";
    }
	else if (level > 1)
	{
        printGivenLevel(root->left, level-1, level1);  
        printGivenLevel(root->right, level-1, level1); 
	}
}


/* Print the level order traversal of the AVL tree */
void printLevelOrder(struct node* root)
{
	int h = findHeight(root)+1;
	for(int i=h; i>=1; i--)
    {
        for(int j=i;j>=0;j--)
            cout<<"  ";
        printGivenLevel(root,h-i+1,i-1);
        cout<<endl;
    }	
}
