//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
    if (ll == NULL || ll->head == NULL) {
        return; // 리스트가 비어있으면 아무 작업도 하지 않음
    }

	// 현재 ll의 노드를 가리키는 포인터 cur 준비
    ListNode *cur = ll->head;
    ListNode *evenHead = NULL; // 짝수 노드의 첫 번째 노드
    ListNode *evenTail = NULL; // 짝수 노드의 마지막 노드
    ListNode *oddHead = NULL;  // 홀수 노드의 첫 번째 노드
    ListNode *oddTail = NULL;  // 홀수 노드의 마지막 노드

    // 리스트 순회 시작
    while (cur != NULL) {
        if (cur->item % 2 == 0) { // 짝수인 경우, 짝수 리스트에 원소 추가
            if (evenHead == NULL) { // 짝수 list가 비어 있는 경우, list head에 원소 넣고, 아니면 tail에 넣고
                evenHead = cur; // 짝수 리스트의 첫 번째 노드 설정
                evenTail = cur;
            } else {
                evenTail->next = cur; // 기존 짝수 리스트의 끝에 노드를 추가
                evenTail = cur; // 짝수 리스트의 끝 갱신
				// 짝수 리스트 마지막에 cur(현재 원소) 연결해주고, 현재 원소 자체가 짝수 리스트 마지막 원소로 재설정 됨
            }
        } else { // 홀수인 경우
            if (oddHead == NULL) {
                oddHead = cur; // 홀수 리스트의 첫 번째 노드 설정
                oddTail = cur;
            } else {
                oddTail->next = cur; // 기존 홀수 리스트의 끝에 노드를 추가
                oddTail = cur; // 홀수 리스트의 끝 갱신
            }
        }

        cur = cur->next; // 다음 노드로 이동, 원소 list 순회하며 even과 odd로 나눔
    }

	// 리스트의 끝 처리
    if (oddTail != NULL) {
        oddTail->next = NULL; // 홀수 리스트의 마지막 노드 처리
    }
    
	// 짝수 리스트와 홀수 리스트 연결
    if (evenTail != NULL) {
        evenTail->next = oddHead; // 짝수 리스트 뒤에 홀수 리스트 연결
    }

    // 짝수 리스트가 존재하면 head를 짝수 리스트의 head로 갱신
	// 여기서 아래 if문 없애고, 위 if (evenTail != NULL) 아래에 ll->head = evenHead; 넣어도 가능
	// evenTail이 NULL이 아니란 뜻은, evenList가 비어 있지 않다는 뜻이기도 하니
    if (evenHead != NULL) {
        ll->head = evenHead;
    } else {
        ll->head = oddHead; // 짝수 리스트가 없으면 홀수 리스트를 head로 설정
    }
}



///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
