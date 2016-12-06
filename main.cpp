#include <iostream>
#include "functions.hpp"

using namespace std;

int main()
{
    int num[] = {8,4,2,1,3,6,7,12,10,14,9,11,13,15};

    int n=sizeof(num)/sizeof(int);

    node* root=NULL;

    for (int i=0;i<n;i++)
    {
        root=insert(root,num[i]);
    }
	
	cout << "\n\nLevel order traversal of the tree :\n";
    printLevelOrder(root);
	cout << "\nIn order traversal of the tree :\n";
	inorder(root);
    remove(root,9);
	cout << "\nLevel order traversal of the tree :\n";
    printLevelOrder(root);
	cout << "\nIn order traversal of the tree :\n";
	inorder(root);
	cout << endl;
  
    return 0;
}
