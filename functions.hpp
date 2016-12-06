/* AVL Node structure */
struct node
{
    int data;
    node* left;
    node* right;
    int height;
};


node* insert(node* , int);
void inorder(node*);
void search(node* , int);
int findHeight(node*);
int findMax(int , int);
int getBalanceFactor(node*);
node* leftRotate(node*);
node* rightRotate(node*);
int updateHeight(node*);
node* remove(node* , int);
void printGivenLevel(node* , int , int);
void printLevelOrder(node*);
