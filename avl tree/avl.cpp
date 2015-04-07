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

void insertAVL(TreeNode*, char);	// 새로운 노드를 삽입하는 함수
int height(TreeNode*);				// 트리의 높이를 구하는 함수
void inOrder(TreeNode*);			// 트리를 중위 순회하는 함수

TreeNode *avl = new TreeNode();
TreeNode **avlPtr = &avl; // 트리노드를 가리키는 포인터

int main()
{
	char alphabet[16] = { 'k', 'o', 'm', 'i', 'n', 'u', 'v', 'e',
						  'r', 's', 't', 'y', 'c', 'd', 'a', 'b' };
 
	for(int i=0; i<16; i++) {
		cout << alphabet[i] << " 삽입" << endl;
		insertAVL(*avlPtr, alphabet[i]);
		
		cout << "순회 결과 : ";
		inOrder(*avlPtr);
		cout << endl;
		
		cout << "트리의 깊이 : " << height(*avlPtr) << endl << endl;
	}

	return 0;
}

void insertAVL(TreeNode* r, char nkey) {
	if(r -> key == 0) {// 트리가 처음 생성된 경우
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

	// terminal node에 다다르거나 삽입할 key 값을 찾을 때까지
	while((p != NULL) && (found == false)) { 
		if(p -> bf != 0) {
			a = p;	// 균형인수를 관찰할 조상노드
			f = q;	// 조상노드의 부모노드
		}
		if(nkey < p -> key) { // 삽입할 key값이 현재 key값보다 작으면
			q = p;
			p = p -> left; // 왼쪽 자식 노드로 현재 위치 이동
		}
		else if(nkey > p -> key) { // 삽입할 key값이 현재 key값보다 크면
			q = p;
			p = p -> right;	// 오른쪽 자식 노드로 현재 위치 이동
		}
		else {	// 삽입할 key값이 이미 존재하면
			y = p;
			found = true;
		}
	}
	
	if(found == false) {
		y = new TreeNode(nkey);
		if(nkey < q -> key)	// 삽입할 key값을 가진 새로운 노드 연결
			q -> left = y;
		else
			q -> right = y;

		if(nkey > a -> key) {// 삽입된 값이 조상 노드보다 클 경우
			p = a -> right;
			b = p;
			d = -1;	// 균형 인수 1 감소
		}
		else {				// 삽입된 값이 조상 노드보다 작을 경우
			p = a -> left;
			b = p;
			d = 1;	// 균형 인수 1 증가
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

		unbalanced = true;	// 트리의 균형 or 불균형 여부
		
		if((a -> bf == 0) || ((a -> bf) + d == 0)) { // 균형인수가 -1~1이면
			(a -> bf) += d;
			unbalanced = false;	// 트리의 균형이 깨지지 않음
		}
		if(unbalanced == true) {	// 트리의 균형을 다시 맞춰야 함
			if(d == 1) {	// a의 균형 인수 : 2
				if(b -> bf == 1) {	
					cout << "회전 유형 : LL" << endl;
					a -> left = b -> right;
					b -> right = a;
					a -> bf = 0;
					b -> bf = 0;
				}
				else {				
					cout << "회전 유형 : LR" << endl;
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
			else {	// a의 균형 인수 : -2
				if(b -> bf == -1) {	
					cout << "회전 유형 : RR" << endl;
					a -> right = b -> left;
					b -> left = a;
					a -> bf = 0;
					b -> bf = 0;
				}
				else {
					cout << "회전 유형 : RL" << endl;
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
			if(f == NULL) // 재균형을 이룬 새 루트노드를 가리키도록 포인터에 저장
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