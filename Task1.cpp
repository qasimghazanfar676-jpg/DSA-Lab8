#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        this->left = this->right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

void printCodesPreorder(MinHeapNode* root, string str) {
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodesPreorder(root->left, str + "0");
    printCodesPreorder(root->right, str + "1");
}

void HuffmanCodes(string S, int f[], int N) {
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < N; ++i)
        minHeap.push(new MinHeapNode(S[i], f[i]));

    while (minHeap.size() != 1) {
        MinHeapNode* left = minHeap.top();
        minHeap.pop();

        MinHeapNode* right = minHeap.top();
        minHeap.pop();

        MinHeapNode* top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    printCodesPreorder(minHeap.top(), "");
}

int main() {
    string S = "abcdef";
    int f[] = { 5, 9, 12, 13, 16, 45 };
    int N = S.length();

    HuffmanCodes(S, f, N);

    return 0;
}