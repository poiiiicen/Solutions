/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int res = l1->val + l2->val;
        ListNode* p = new ListNode(res % 10);
        ListNode* l3 = p;
        res = (res - p->val) / 10;
        l1 = l1->next;
        l2 = l2->next;
        while (l1 != NULL && l2 != NULL) {
            res += l1->val + l2->val;
            p->next = new ListNode(res % 10);
            p = p->next;
            res = (res - p->val) / 10;
            l1 = l1->next;
            l2 = l2->next;
        }
        if (l1 == NULL) l1 = l2;
        while (l1 != NULL) {
            res += l1->val;
            p->next = new ListNode(res % 10);
            p = p->next;
            res = (res - p->val) / 10;
            l1 = l1->next;
        }
        if (res) p->next = new ListNode(res);
        return l3;
    }
};