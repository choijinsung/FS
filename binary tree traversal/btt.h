#include <iostream>
using namespace std;

template <class T>
class TreeNode
{
public:
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;
	TreeNode(T d) 
	{
		data = d;
		leftChild = NULL;
		rightChild = NULL;
	}
};

template <class T>
void PreOrder(TreeNode<T> *t)
{
	if(t != NULL)
	{
		cout << t -> data << ' ';
		PreOrder(t -> leftChild);
		PreOrder(t -> rightChild);
	}
}

template <class T>
void InOrder(TreeNode<T> *t)
{
	if(t != NULL)
	{
		InOrder(t -> leftChild);
		cout << t -> data << ' ';
		InOrder(t -> rightChild);
	}
}

template <class T>
void PostOrder(TreeNode<T> *t)
{
	if(t != NULL)
	{
		PostOrder(t -> leftChild);
		PostOrder(t -> rightChild);
		cout << t -> data << ' ';
	}
}