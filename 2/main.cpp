//
// Created by 钟华松 on 16/9/24.
// leetcode
// 2. Add Two Numbers
//

#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* First = new ListNode(0);
        ListNode* Current = First;
        int carry = 0;
        int res = 0;
        int flag = 0;
        int num = 0;

        while (l1 != NULL || l2 != NULL) {
            if (flag == 0) {
                res = (l1->val + l2->val) % 10;
                carry = (l1->val + l2->val) /10;
                First->val = res;
                flag = 1;
                l1 = l1->next;
                l2 = l2->next;
                continue;
            }
            ListNode *NewNode = new ListNode(0);
            if (l1 != NULL && l2 != NULL) {
                num = (l1->val + l2->val);
                l1 = l1->next;
                l2 = l2->next;
            }else if (l1 != NULL) {
                num = (l1->val);
                l1 = l1->next;
            }else if (l2 != NULL) {
                num = (l2->val);
                l2 = l2->next;
            }
            res = (num + carry) % 10;
            carry = (num + carry) / 10;
            NewNode->val = res;
            Current->next = NewNode;
            Current = NewNode;
        }

        if (carry != 0) {
            ListNode* NewNode = new ListNode(carry);
            Current->next = NewNode;
        }

        return First;
    }
};

int main() {
    ListNode* node11 = new ListNode(1);
    ListNode* node12 = new ListNode(8);
    ListNode* node13 = new ListNode(3);
    node11->next = node12;
    node12->next = node13;

    ListNode* node21 = new ListNode(0);
    ListNode* node22 = new ListNode(6);
    ListNode* node23 = new ListNode(4);
    node21->next = node22;
    node22->next = node23;

    Solution* solu = new Solution();
    ListNode* res = solu->addTwoNumbers(node11, node21);
    while (res) {
        cout << res->val;
        res = res->next;
    }
    return 0;
}
