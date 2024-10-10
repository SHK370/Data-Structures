// 무한루프 버전


void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    // 두 리스트 모두 비어있는 경우 아무 작업도 하지 않음
    if (ll1 == NULL || ll2 == NULL) {
        return;
    }

    // 현재 ll1, ll2의 노드를 가리키는 포인터를 준비
    ListNode *cur1 = ll1->head;
    ListNode *cur2 = ll2->head;
    ListNode *next1, *next2;

    // 교대로 노드를 가져오기 위해 반복문 사용
    while (cur1 != NULL && cur2 != NULL) {
        // 다음 노드를 미리 저장 (나중에 사용할 예정)
        next1 = cur1->next;
        next2 = cur2->next;

        // ll2의 첫 번째 노드를 ll1의 다음에 삽입
        cur1->next = cur2;
        cur2->next = next1;

        // 포인터 이동: ll1의 다음 노드로 이동
        cur1 = next1;
        // ll2의 노드로 이동 (즉, ll2는 새로운 첫 번째 노드를 가리켜야 함)
        cur2 = next2;
    }

    // ll1 리스트의 사이즈 갱신
    ll1->size += ll2->size;
    // ll2 리스트를 비움
    ll2->head = NULL;
    ll2->size = 0;
}
