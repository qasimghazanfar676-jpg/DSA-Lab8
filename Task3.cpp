#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* balanceNode(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* insert(Node* node, int key) {
    if (!node)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    return balanceNode(node);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (!root)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root)
        return root;

    return balanceNode(root);
}

void printTree(Node* root, string indent = "", bool last = true) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key << "\n";
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

void collectMax(Node* root, vector<int>& res, int k) {
    if (!root || (int)res.size() >= k)
        return;
    collectMax(root->right, res, k);
    if ((int)res.size() < k)
        res.push_back(root->key);
    collectMax(root->left, res, k);
}

void collectMin(Node* root, vector<int>& res, int k) {
    if (!root || (int)res.size() >= k)
        return;
    collectMin(root->left, res, k);
    if ((int)res.size() < k)
        res.push_back(root->key);
    collectMin(root->right, res, k);
}

vector<int> getTopK(Node* root, int k, string criteria) {
    vector<int> res;
    if (criteria == "max") {
        collectMax(root, res, k);
    } else if (criteria == "min") {
        collectMin(root, res, k);
    }
    return res;
}

int main() {
    Node* root = nullptr;
    vector<int> values = { 10, 20, 30, 40, 50, 25 };

    for (int val : values) {
        root = insert(root, val);
        cout << "Inserted " << val << ". Tree structure:\n";
        printTree(root);
        cout << "------------------------------------\n";
    }

    int k = 3;
    string criteria = "max";
    vector<int> topK = getTopK(root, k, criteria);

    cout << "Top " << k << " elements (" << criteria << "): ";
    for (int x : topK)
        cout << x << " ";
    cout << "\n------------------------------------\n";

    cout << "Deleting Top " << k << " elements:\n";
    for (int x : topK) {
        root = deleteNode(root, x);
        cout << "Deleted " << x << ". Tree structure:\n";
        printTree(root);
        cout << "------------------------------------\n";
    }

    return 0;
}