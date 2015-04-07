#include <iostream>
using namespace std;

class TreeNode 
{
public:
	char key;
	int bf;
	TreeNode *left;
	TreeNode *right;
	TreeNode()
	{
		key = 0;
		bf = 0;
		left = NULL;
		right = NULL;
	}
	TreeNode(char k) 
	{
		key = k;
		bf = 0;
		left = NULL;
		right = NULL;
	}
};

void insertAVL(TreeNode*, char);	// ���ο� ��带 �����ϴ� �Լ�
int height(TreeNode*);				// Ʈ���� ���̸� ���ϴ� �Լ�
void inOrder(TreeNode*);			// Ʈ���� ���� ��ȸ�ϴ� �Լ�

TreeNode *avl = new TreeNode();
TreeNode **avlPtr = &avl; // Ʈ����带 ����Ű�� ������

int main()
{
	char alphabet[16] = { 'k', 'o', 'm', 'i', 'n', 'u', 'v', 'e',
						  'r', 's', 't', 'y', 'c', 'd', 'a', 'b' };
 
	for(int i=0; i<16; i++) {
		cout << alphabet[i] << " ����" << endl;
		insertAVL(*avlPtr, alphabet[i]);
		
		cout << "��ȸ ��� : ";
		inOrder(*avlPtr);
		cout << endl;
		
		cout << "Ʈ���� ���� : " << height(*avlPtr) << endl << endl;
	}

	return 0;
}

void insertAVL(TreeNode* r, char nkey) {
	if(r -> key == 0) {// Ʈ���� ó�� ������ ���
		r -> key = nkey;
		return;
	}

	TreeNode *f = NULL;
	TreeNode *a = r;
	TreeNode *p = r;
	TreeNode *q = NULL;
	TreeNode *y = NULL;
	TreeNode *b = NULL;
	TreeNode *c = NULL;
	bool found = false;
	bool unbalanced = true;
	int d = 0;

	// terminal node�� �ٴٸ��ų� ������ key ���� ã�� ������
	while((p != NULL) && (found == false)) { 
		if(p -> bf != 0) {
			a = p;	// �����μ��� ������ ������
			f = q;	// �������� �θ���
		}
		if(nkey < p -> key) { // ������ key���� ���� key������ ������
			q = p;
			p = p -> left; // ���� �ڽ� ���� ���� ��ġ �̵�
		}
		else if(nkey > p -> key) { // ������ key���� ���� key������ ũ��
			q = p;
			p = p -> right;	// ������ �ڽ� ���� ���� ��ġ �̵�
		}
		else {	// ������ key���� �̹� �����ϸ�
			y = p;
			found = true;
		}
	}
	
	if(found == false) {
		y = new TreeNode(nkey);
		if(nkey < q -> key)	// ������ key���� ���� ���ο� ��� ����
			q -> left = y;
		else
			q -> right = y;

		if(nkey > a -> key) {// ���Ե� ���� ���� ��庸�� Ŭ ���
			p = a -> right;
			b = p;
			d = -1;	// ���� �μ� 1 ����
		}
		else {				// ���Ե� ���� ���� ��庸�� ���� ���
			p = a -> left;
			b = p;
			d = 1;	// ���� �μ� 1 ����
		}
		
		while(p != y) {
			if(nkey > p -> key) {
				p -> bf = -1;
				p = p -> right;
			}
			else {
				p -> bf = 1;
				p =  p -> left;
			}
		}

		unbalanced = true;	// Ʈ���� ���� or �ұ��� ����
		
		if((a -> bf == 0) || ((a -> bf) + d == 0)) { // �����μ��� -1~1�̸�
			(a -> bf) += d;
			unbalanced = false;	// Ʈ���� ������ ������ ����
		}
		if(unbalanced == true) {	// Ʈ���� ������ �ٽ� ����� ��
			if(d == 1) {	// a�� ���� �μ� : 2
				if(b -> bf == 1) {	
					cout << "ȸ�� ���� : LL" << endl;
					a -> left = b -> right;
					b -> right = a;
					a -> bf = 0;
					b -> bf = 0;
				}
				else {				
					cout << "ȸ�� ���� : LR" << endl;
					c = b -> right;
					b -> right = c -> left;
					a -> left = c -> right;
					c -> left = b;
					c -> right = a;
					switch(c -> bf) {
					case 1:
						a -> bf = -1;
						b -> bf = 0;
						break;
					case -1:
						b -> bf = 1;
						a -> bf = 0;
						break;
					case 0:
						b -> bf = 0;
						a -> bf = 0;
						break;
					}
					c -> bf = 0;
					b = c;
				}
			}
			else {	// a�� ���� �μ� : -2
				if(b -> bf == -1) {	
					cout << "ȸ�� ���� : RR" << endl;
					a -> right = b -> left;
					b -> left = a;
					a -> bf = 0;
					b -> bf = 0;
				}
				else {
					cout << "ȸ�� ���� : RL" << endl;
					c = b -> left;
					b -> left = c -> right;
					a -> right = c -> left;
					c -> left = a;
					c -> right = b;
					
					switch(c -> bf) {
					case 0:
						a -> bf = 0;
						b -> bf = 0;
						break;
					case -1:
						a -> bf = 1;
						b -> bf = 0;
						break;
					case 1:
						a -> bf = 0;
						b -> bf = -1;
						break;
					}
					c -> bf = 0;
					b = c;
				}
			}
			if(f == NULL) // ������� �̷� �� ��Ʈ��带 ����Ű���� �����Ϳ� ����
				*avlPtr = b;
			else if(a == f -> left) 
				f -> left = b;
			else if(a == f -> right) 
				f -> right = b;
		}
	}
}

int height(TreeNode* node) {	
	if(node == NULL)
		return 0;
	return (height(node -> left) > height(node -> right) ? height(node -> left) : height(node -> right)) + 1;
}

void inOrder(TreeNode* b) {
	if(b != NULL) {
		if(b -> left != NULL)
			inOrder(b -> left);
		if(b -> key != NULL)
			cout << b -> key << ' ';
		if(b -> right != NULL)
			inOrder(b -> right);
	}
}