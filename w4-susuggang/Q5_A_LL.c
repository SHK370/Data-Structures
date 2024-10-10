//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
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
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// list의 앞 절반 원소와 뒷 절반 원소를 각각 별개의 list에 나누어 저장 후 제시하는 함수
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
    // 리스트가 비어있는 경우 처리
    if (ll == NULL || ll->head == NULL) {
        return;
    }

    // 초기화
    removeAllItems(resultFrontList);
    removeAllItems(resultBackList);

	// slow : 뒷 list, fast : 앞 list
    ListNode *slow = ll->head;
    ListNode *fast = ll->head;
    ListNode *prev = NULL;
 
    // 리스트를 절반으로 나누기 위한 slow와 fast 포인터
	// fast가 끝에 도달하거나, 리스트 길이가 홀수인 경우 fast -> next가 NULL 일 때 루프 종료
    while (fast != NULL && fast->next != NULL) {
        prev = slow; 
        slow = slow->next; // 한번에 한칸씩 이동
        fast = fast->next->next; // 한번에 두칸씩 이동
		// fast 포인터가 끝에 도달할 때, slow 포인터는 중간에 도달
    }
	// 예시 :
	// 리스트: 1 -> 2 -> 3 -> 4 -> 5
	// 초기 상태: slow = 1, fast = 1
	// 1번째 반복: slow = 2, fast = 3
	// 2번째 반복: slow = 3, fast = 5 (fast가 마지막 노드에 도달함)

    // 리스트를 분리
	// prev는 slow 직전 node를 가리킴
	// prev의 next에 NULL을 저장하여, list 앞단과 뒷단을 물리적으로 분리
    if (prev != NULL) {
        prev->next = NULL; // 앞쪽 절반과 뒷쪽 절반을 분리
    }

    // resultFrontList는 ll의 앞부분
    resultFrontList->head = ll->head;
    resultFrontList->size = ll->size / 2;

	// prev로 끊은 바로 뒷단인 slow부터 뒷 list 시작
    // resultBackList는 ll의 뒷부분 (slow부터 시작)
    resultBackList->head = slow;
    resultBackList->size = (ll->size + 1) / 2;
	// 아래처럼 작성도 가능
	// resultBackList->size = ll->size - resultFrontList->size; // 남은 노드 수를 계산하여 설정


    // ll 리스트는 더 이상 유효하지 않으므로 head를 NULL로 설정
    ll->head = NULL;
    ll->size = 0;
}


// ---------------------------------------
// list 나누는 또 다른 방법 : Counting Nodes and Splitting

//     // Step 1: Count the total number of nodes
//     int count = 0;
//     ListNode *current = ll->head;
    
// 	while (current != NULL) {
//         count++;
//         current = current->next;
//     }

//     // Step 2: Calculate the midpoint
//     int mid = (count + 1) / 2; // Ensure frontList has one more node if count is odd

//     // Step 3: Traverse to the node before midpoint
//     current = ll->head;
//     ListNode *prev = NULL;
//     for (int i = 0; i < mid; i++) {
//         prev = current;
//         current = current->next;
//     }

//     // Split the list
//     if (prev != NULL) {
//         prev->next = NULL; // Terminate the front list
//     }

//     // Initialize frontList
//     frontList->head = ll->head;
//     frontList->size = mid;

//     // Initialize backList
//     backList->head = current;
//     backList->size = count - mid;


// // -------------

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


ListNode * findNode(LinkedList *ll, int index){

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
