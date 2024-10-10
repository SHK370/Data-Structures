void moveOddItemsToBack(LinkedList *ll)
{
    // 리스트가 비어 있으면 아무 작업도 하지 않음
    if (ll == NULL || ll->head == NULL) {
        return;
    }

    ListNode *cur = ll->head;
    ListNode *prev = NULL;
    ListNode *tail = ll->head;
    
    // tail 포인터를 마지막 노드로 이동
    while (tail->next != NULL) {
        tail = tail->next;
    }

    ListNode *last = tail; // 원래의 마지막 노드를 기억해 둠

    // 리스트를 처음부터 순회하면서 홀수 노드를 뒤로 보냄
    while (cur != NULL && cur != last->next) {
        if (cur->item % 2 != 0) { // 홀수인 경우
            if (cur == ll->head) { // 첫 번째 노드가 홀수인 경우
                ll->head = cur->next; // 헤드를 다음 노드로 이동
                tail->next = cur; // 홀수 노드를 끝으로 이동
                tail = cur; // 끝 노드를 갱신
                cur = ll->head; // 새로운 헤드를 기준으로 다시 순회 시작
                tail->next = NULL; // 끝 노드의 다음은 NULL로 설정
            } else { // 중간 노드가 홀수인 경우
                prev->next = cur->next; // 중간의 홀수 노드를 리스트에서 제외
                tail->next = cur; // 그 홀수 노드를 끝으로 이동
                tail = cur; // 끝 노드를 갱신
                cur = prev->next; // 이전 노드의 다음 노드로 이동
                tail->next = NULL; // 끝 노드의 다음은 NULL로 설정
            }
        } else { // 짝수인 경우
            prev = cur; // 이전 노드를 갱신
            cur = cur->next; // 다음 노드로 이동
        }
    }
}
