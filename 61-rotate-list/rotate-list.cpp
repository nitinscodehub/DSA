class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next || k == 0) return head;

        // find length
        int len = 1;
        ListNode* tail = head;
        while(tail->next) {
            tail = tail->next;
            len++;
        }

        // make circular
        tail->next = head;

        k = k % len;
        int stepsToNewHead = len - k;

        ListNode* newTail = tail;
        while(stepsToNewHead--) {
            newTail = newTail->next;
        }

        ListNode* newHead = newTail->next;
        newTail->next = NULL;

        return newHead;
    }
};