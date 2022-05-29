#include <iostream>
#include <algorithm>
using namespace std;


struct Node
{
	char data;		
	int height;
	Node* left;
	Node* right;
};

int return_height(Node* n)
{
	if (n != NULL)
		return n->height;
	return 0; //for an unexistent node the height would be -1
}

int height_difference(Node* n) //we need this function to help us balance the tree, it essentially gives us the balance at any given node
{
	if (n != NULL)
		return return_height(n->left) - return_height(n->right);
	return 0; //for an unexistent node the difference of heights would be -1
}

Node* left_rotation(Node* n) //implemented according to provided resources
{
	Node* right = n->right;         //creating a temporary storage for right node of n    
	Node* rightleft = right->left;  //-||- for left node of right of n
									//
	right->left = n;				//we replace the left node of right of n with the root (n)
	n->right = rightleft;			//we flip the tree by setting the right node by the left and then setting the right node of the left by the right left node we had before
	
	n->height = max(return_height(n->right), return_height(n->left)) + 1;
	right->height = max(return_height(right->right), return_height(right->left)) + 1;

	return right; //new root
}

Node* right_rotation(Node* n) //algebraically symmetrical operation for left_rotation(Node* n), meaning a = right_rotation(left_rotation(a))
{
	Node* left = n->left;
	Node* leftright = left->right;

	left->right = n;
	n->left = leftright;

	n->height = max(return_height(n->left), return_height(n->right)) + 1;
	left->height = max(return_height(left->left), return_height(left->right)) + 1;

	return left;
}

Node* balance_tree(Node* n)
{
	if (height_difference(n) > 1)
	{
		if (height_difference(n->left) > 0)
			return right_rotation(n);
		else
		{
			n->left = left_rotation(n->left);
			return right_rotation(n);
		}
	}
	else if (height_difference(n) < -1)
	{
		if (height_difference(n->right) > 0)
		{
			n->right = right_rotation(n->right);
			return left_rotation(n);
		}
		else
			return left_rotation(n);
	}
	else return n;
}

Node* insert_node(Node* n, char data) //basic Binary Tree insertion just calling balance at the end
{
	if (n == NULL)
	{
		n = new Node();
		n->data = data;
		n->height = 0;
		return n;
	}

	if (data < n->data)
		n->left = insert_node(n->left, data);
	else if (data > n->data)
		n->right = insert_node(n->right, data);
	else
		return n;

	n->height = max(return_height(n->left), return_height(n->right)) + 1;

	balance_tree(n);
}

void print_tree(Node* n)
{
	if (n != NULL)
	{
		cout << n->data << endl;
		print_tree(n->left);
		print_tree(n->right);
	}
}

int main()
{
	Node* root = NULL;

	root = insert_node(root, 'H');
	root = insert_node(root, 'I');
	root = insert_node(root, 'J');
	root = insert_node(root, 'B');
	root = insert_node(root, 'A');
	root = insert_node(root, 'E');
	root = insert_node(root, 'C');
	root = insert_node(root, 'F');
	root = insert_node(root, 'D');
	root = insert_node(root, 'G');
	root = insert_node(root, 'K');
	root = insert_node(root, 'L');

	print_tree(root);

	return 0;
}