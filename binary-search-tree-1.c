/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; // 정수형 변수 선언
	struct node *left; // 구조체 포인터 left 선언
	struct node *right; // 구조체 포인터 right 선언
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; // 문자형 변수 선언
	int key; // 정수형 변수 선언
	Node* head = NULL; // Node 포인터 변수 head 선언 후 초기화
	Node* ptr = NULL;	/* temp */ //Node 포인터 변수 ptr 선언 후 초기화
        printf("[----- [Taehyung Kim] [2020039024] -----]");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { 
		case 'z': case 'Z': // z를 입력 받을 경우
			initializeBST(&head); // head의 주소를 매개 변수로 갖는 initializeBST함수 호출
			break;
		case 'q': case 'Q': // q를 입력 받을 경우
			freeBST(head); // freeBST함수 호출
			break;
		case 'n': case 'N': // n을 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key); // key를 입력 받음
			insert(head, key); // insert함수 호출
			break;
		case 'd': case 'D': // d를 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key); // key를 입력 받음
			deleteLeafNode(head, key); // deleteLeafNode 함수 호출
			break;
		case 'f': case 'F': // f를 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key); // key를 입력 받음
			ptr = searchIterative(head, key); // ptr에 searchIterative 함수 호출 값을 저장
			if(ptr != NULL) // ptr이 NULL이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': // s를 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key); // key를 입력 받음
			ptr = searchRecursive(head->left, key); // ptr에 searchRecursive 함수 호출 값을 저장
			if(ptr != NULL) // ptr이 NULL이 아닐 경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': // i를 입력 받을 경우
			inorderTraversal(head->left); // 중위순회함수
			break;
		case 'p': case 'P': // p를 입력 받을 경우
			preorderTraversal(head->left); // 전위순회함수
			break;
		case 't': case 'T': // t를 입력 받을 경우
			postorderTraversal(head->left); // 후위순회함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q가 입력되지 않을 동안 반복

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // 포인터 h에 Node의 크기만큼 메모리 할당
	(*h)->left = NULL;	/* root */ // 포인터 h의 left에 NULL값 대입
	(*h)->right = *h;  // 포인터 h의 right에 포인터 h 저장
	(*h)->key = -9999; // 포인터 h의 key를 -9999로 초기화
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) { 
		inorderTraversal(ptr->left); // 왼쪽 노드로 재귀
		printf(" [%d] ", ptr->key); // ptr의 key 출력
		inorderTraversal(ptr->right); // 오른쪽 노드로 재귀
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key); // ptr의 key 출력
		preorderTraversal(ptr->left); // 왼쪽 노드로 재귀
		preorderTraversal(ptr->right); // 오른쪽 노드로 재귀
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left); // 왼쪽 노드로 재귀
		postorderTraversal(ptr->right); // 오른쪽 노드로 재귀
		printf(" [%d] ", ptr->key); // ptr의 key 출력
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // Node 포인터 Node 크기만큼 메모리 할당 
	newNode->key = key; // newNode의 key에 key 저장
	newNode->left = NULL; // newNode의 left에 NULL 저장
	newNode->right = NULL; // newNode의 right에 NULL 저장

	if (head->left == NULL) { // head의 left가 NULL이라면
		head->left = newNode; // head의 left에 newNode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // Node의 포인터 ptr에 head의 left 저장

	Node* parentNode = NULL; // 포인터 parentNode 선언 후 NULL 저장
	while(ptr != NULL) { // ptr이 NULL이 아닐 동안

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; // ptr의 key가 key와 같다면 1을 return

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; // parentNode에 ptr 저장

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr의 key가 입력받은 key보다 작을 때
			ptr = ptr->right; // ptr에 ptr의 right 저장
		else
			ptr = ptr->left; // ptr에 ptr의 left 저장
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // parentNode의 key가 key보다 크면
		parentNode->left = newNode; // parentNode의 left에 newNode 대입
	else
		parentNode->right = newNode; // parentNode의 right에 newNode 대입
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { // head가 NULL일 경우
		printf("\n Nothing to delete!!\n"); // 출력
		return -1;
	}

	if (head->left == NULL) { // head의 left가 NULL일 경우
		printf("\n Nothing to delete!!\n"); // 출력
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // Node 포인터 ptr에 head의 left 대입


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; // Node 포인터 parentNode에 head 대입

	while(ptr != NULL) { // ptr이 NULL이 아닐 동안 반복

		if(ptr->key == key) { // ptr의 key가 key이면
			if(ptr->left == NULL && ptr->right == NULL) {
				// ptr의 left가 NULL이면서 ptr의 right가 NULL이라면
				/* root node case */
				if(parentNode == head) // parentNode와 head 값이 같으면
					head->left = NULL; // head의 left에 NULL 대입

				/* left node case or right case*/
				if(parentNode->left == ptr) // parentNode의 left가 ptr과 같으면
					parentNode->left = NULL; // parentNode의 left에 NULL 대입
				else
					parentNode->right = NULL; // parentNode의 right에 NULL 대입

				free(ptr); // ptr의 메모리 해제
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key); // 출력
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; // parentNode에 ptr 저장

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr의 key가 입력받은 key보다 작으면
			ptr = ptr->right; // ptr에 ptr의 right 저장
		else
			ptr = ptr->left; // ptr에 ptr의 left 저장


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // ptr이 NULL이면
		return NULL; // NULL 반환

	if(ptr->key < key) // ptr의 key가 입력받은 key보다 작으면
		ptr = searchRecursive(ptr->right, key); // ptr에 오른쪽 트리를 탐색한 결과 저장
	else if(ptr->key > key) // ptr의 key가 입력받은 key보다 크면
		ptr = searchRecursive(ptr->left, key); // ptr에 왼쪽 트리를 탐색한 결과 저장

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left; // Node 포인터 ptr에 head의 left 대입

	while(ptr != NULL) // ptr이 NULL이 아닐 동안 반복
	{
		if(ptr->key == key) // ptr의 key가 입력받은 key와 같으면
			return ptr;

		if(ptr->key < key) ptr = ptr->right; // ptr의 key가 입력받은 key보다 작으면
		else
			ptr = ptr->left; // ptr에 ptr의 left 대입
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); // ptr의 left 메모리 해제
		freeNode(ptr->right); // ptr의 right 메모리 해제
		free(ptr); // ptr의 메모리 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head) // head의 left가 head와 같으면
	{
		free(head); // head 메모리 해제
		return 1;
	}

	Node* p = head->left; // Node의 포인터 p에 head의 left 저장

	freeNode(p); // p의 메모리 해제

	free(head); // head의 메모리 해제
	return 1;
}