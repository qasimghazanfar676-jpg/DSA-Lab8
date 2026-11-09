#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct CompareNode {
    bool operator()(ListNode* const& p1, ListNode* const& p2) {
        return p1->val > p2->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, CompareNode> minHeap;

    for (ListNode* root : lists) {
        if (root != nullptr)
            minHeap.push(root);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!minHeap.empty()) {
        ListNode* smallest = minHeap.top();
        minHeap.pop();

        tail->next = smallest;
        tail = tail->next;

        if (smallest->next != nullptr) {
            minHeap.push(smallest->next);
        }
    }

    return dummy.next;
}

void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

int main() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);

    vector<ListNode*> lists = { l1, l2, l3 };

    ListNode* merged = mergeKLists(lists);
    printList(merged);

    return 0;
}