class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* prevGroup = &dummy;

        while (true) {
            ListNode* kth = prevGroup;

            for (int i = 0; i < k; i++) {
                kth = kth->next;
                if (kth == nullptr)
                    return dummy.next;
            }

            ListNode* groupNext = kth->next;

            ListNode* prev = groupNext;
            ListNode* curr = prevGroup->next;

            while (curr != groupNext) {
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            ListNode* oldStart = prevGroup->next;
            prevGroup->next = kth;

            prevGroup = oldStart;
        }

        return dummy.next;
    }
};