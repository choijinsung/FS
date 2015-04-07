#include "btt.h"

void main()
{
	TreeNode<char> *A = new TreeNode<char>('A');
	TreeNode<char> *B = new TreeNode<char>('B');
	TreeNode<char> *C = new TreeNode<char>('C');
	TreeNode<char> *D = new TreeNode<char>('D');
	TreeNode<char> *E = new TreeNode<char>('E');
	TreeNode<char> *F = new TreeNode<char>('F');
	TreeNode<char> *G = new TreeNode<char>('G');
	TreeNode<char> *H = new TreeNode<char>('H');

	A -> leftChild = B;
	A -> rightChild = C;
	B -> leftChild = D;
	C -> leftChild = E;
	C -> rightChild = F;
	E -> rightChild = G;
	F -> leftChild = H;

	PreOrder(A);
	cout << endl;
	InOrder(A);
	cout << endl;
	PostOrder(A);
	cout << endl;
}