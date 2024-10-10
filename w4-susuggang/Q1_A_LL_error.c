// 2번 기능 오작동 ver.

int insertSortedLL(LinkedList *ll, int item)
{
    // 새로운 노드 생성
    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        return -1; // 메모리 할당 실패
    newNode->item = item;
    newNode->next = NULL;

    // 리스트가 비어 있거나 가장 앞에 삽입해야 할 경우
    if (ll->head == NULL || item <= ll->head->item) {
        newNode->next = ll->head;
        ll->head = newNode;
        ll->size++;
        return 0;
    }

    // 중간이나 끝에 삽입해야 할 경우
    ListNode *cur = ll->head;
    while (cur->next != NULL && cur->next->item < item) {
        cur = cur->next;
    }
    
    newNode->next = cur->next;
    cur->next = newNode;
    ll->size++;
    
    return 0;
}







case 2:
    if (ll.size > 0) {
        printf("The value %d was added at index %d\n", i, j);
    } else {
        printf("No values have been added yet.\n");
    }
    break;
