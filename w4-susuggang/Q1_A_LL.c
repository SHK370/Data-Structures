//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// 구조체의 이름(태그tag): _listnode, 구조체의 내부에서 사용하는 이름. 내부 이름을 구분하기 위해 _를 앞에 씀.
// 구조체의 별칭: ListNode, 프로그램에서 struct _listnode를 ListNode로 사용 가능. 외부에서 쉽게 참조할 수 있는 이름.
typedef struct _listnode{
	int item;				// 데이터 저장할 공간 (정수형)
	struct _listnode *next;	// 다음 노드를 가리키는 포인터, next는 그 포인터의 이름. 아직 다음 노드는 없더라도 메모리 주소를 할당해둔다?
} ListNode;					// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;				// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
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

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
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

int insertSortedLL(LinkedList *ll, int item)
{
    // 새로운 노드 생성
	// malloc 은 메모리 할당 함수. 주어진 크기만큼의 메모리를 힙 영역에 동적으로 할당.
	// ListNode 구조체 내 모든 멤버 변수의 크기(int item, ListNode *next)의 합. ex. int = 4byte, pointer = 8byte, 12byte.
	// malloc 은 메모리 할당하고, 메모리 시작 주소 반환.
	// 반환된 주소는 newNode라는 포인터 변수에 저장. newNode는 새로 할당된 메모리 공간을 가리키며, 그 공간을 ListNode처럼 사용할 수 있음.
    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        return -1; // 메모리 할당 실패
    newNode->item = item;
    newNode->next = NULL;

    // 리스트가 비어 있거나 가장 앞에 삽입해야 할 경우
    if (ll->head == NULL || item <= ll->head->item) { // head 위치의 item 보다 new item이 더 작다? 맨 앞으로 갈 것
        
		newNode->next = ll->head; // newNode의 next pointer에 기존 list의 head pointer를 저장해 기존 list를 newNode 뒤로 보내기
        ll->head = newNode; // newNode는 list의 head가 되어 list 맨 앞 원소가 됨
        
		ll->size++;
        return 0; // 첫 번째 위치에 삽입
    }

    // 중간이나 끝에 삽입해야 할 경우
    ListNode *cur = ll->head; // 새로운 Node가 우선 첫번째 순서는 아니란게 위에서 밝혀짐. cursor pointer 만들어서 순차적으로 비교하며 새 Node의 위치 찾음
    int index = 1; // 삽입될 인덱스 추적 (첫 번째 노드는 이미 확인했으므로 1로 시작), index = 0 보단 크다는 것 위에서 증명됨
    while (cur->next != NULL && cur->next->item < item) {  // 새 Node의 next가 Null이 아니고(=뒤에 원소가 존재하고), 새 Node 뒤의 Item이 새 Node Item 보다 작으면, 새 Node cur을 뒤로 계속 이동시켜야 함.
        cur = cur->next; // 계속 while문 돌면서, 다음 Node의 next 주소로 가면서 원소 비교
        index++; // 1 턴마다 index +1
    }
    
    newNode->next = cur->next; // 새로 삽입할 newNode의 next(다음 노드 주소)를 cur이 가리키고 있던 다음 원소 값 주소로 지정.
    cur->next = newNode; // 기존 cur이 가리키고 있던 node의 다음 원소 값으론 새로운 원소 newNode의 주소값 저장.
	// 위처럼 하면 기존 ll에서 next로 연결되어 있던 2개의 원소 값 사이에 newNode를 배치할 수 있음.
	// ex. 20,next1  -  30,next3 였을 때, newNode가 25,next2라고 한다면, cur는 while문 통해 20,next1 node를 가리키는 주소로 도출됨.
	// cur의 next는 25,next2에 저장되어 25,next2가 30,next3를 가리키도록 저장됨.
	// 기존 cur가 가리키던 20,next1은 newNode인 25,next2를 가리키도록 저장됨.
	// 결론적으로, 20 - 25 - 30 의 연결성으로 수정됨.
    ll->size++;

    return index; // 삽입된 위치 반환
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
