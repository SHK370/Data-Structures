void moveOddItemsToBack(LinkedList *ll)
{
    // 리스트가 비어 있으면 아무 작업도 하지 않음
    if (ll == NULL || ll->head == NULL) {
        return;
    }

    ListNode *cur = ll->head;
    ListNode *prev = NULL;
    ListNode *tail = ll->head;

    // tail 포인터를 현재 리스트의 마지막 노드로 이동
    while (tail->next != NULL) {
        tail = tail->next;
    }

    // 기존의 마지막 노드를 저장 (반복을 제한하기 위해)
    ListNode *last = tail;
    ListNode *newTail = last; // 새로 끝에 추가되는 노드를 가리킬 tail 포인터

    // 리스트의 각 노드를 순회하며 홀수를 뒤로 이동
    cur = ll->head; // 다시 head부터 시작
    while (cur != NULL && cur != last->next) {
        if (cur->item % 2 != 0) { // 홀수인 경우
            ListNode *nextNode = cur->next; // 다음 노드 미리 저장

            // 첫 번째 노드가 홀수인 경우 처리
            if (cur == ll->head) {
                ll->head = cur->next; // head를 갱신하여 현재 노드를 제거
            } else {
                prev->next = cur->next; // 현재 노드를 리스트에서 제거
            }

            // 현재 노드를 리스트의 끝으로 이동
            newTail->next = cur;
            cur->next = NULL; // 끝으로 옮긴 노드는 다음이 없도록 함
            newTail = cur; // 새로운 끝 노드를 갱신

            // 다음 노드로 이동
            cur = nextNode;
        } else { // 짝수인 경우
            prev = cur; // 이전 노드를 갱신
            cur = cur->next; // 다음 노드로 이동
        }
    }
}
