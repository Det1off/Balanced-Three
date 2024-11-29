#include <iostream>
#include <vector>
#include <queue> // Для итеративного обхода
using namespace std;

class Tree {
public:
    struct Node {
        int value;
        Node* parent = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;

        void ShowNode() const {
            cout << value << " ";
        }
    };

private:
    Node* root = nullptr;

public:
    Tree() {}

    ~Tree() {
        Clear();
    }

    bool IsEmpty() const {
        return root == nullptr;
    }

    void Clear() {
        if (!IsEmpty()) {
            Clear(root);
            root = nullptr;
        }
    }

    void AddNode(int value) {
        Node* parent = nullptr;
        Node** current = &root;

        while (*current) {
            parent = *current;
            if (value < (*current)->value) {
                current = &(*current)->left;
            }
            else if (value > (*current)->value) {
                current = &(*current)->right;
            }
            else {
                return; // Элемент уже существует
            }
        }

        *current = new Node();
        (*current)->value = value;
        (*current)->parent = parent;

        // Балансировка дерева после добавления
        if (IsDegenerate(root)) {
            BalanceTree();
        }
    }

    void ShowTree() const {
        if (IsEmpty()) {
            cout << "Tree is empty\n";
            return;
        }

        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            current->ShowNode();

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << "\n";
    }

private:
    void Clear(Node* element) {
        if (!element) return;

        Clear(element->left);
        Clear(element->right);
        delete element;
    }

    bool IsDegenerate(Node* node) {
        if (!node) return false;
        // Если у узла только один потомок
        if ((node->left && !node->right) || (!node->left && node->right)) {
            return true;
        }
        return IsDegenerate(node->left) || IsDegenerate(node->right);
    }

    void CollectElements(Node* node, vector<int>& elements) {
        if (!node) return;

        CollectElements(node->left, elements);
        elements.push_back(node->value);
        CollectElements(node->right, elements);
    }

    void RebuildTreeFromArray(vector<int>& elements, int left, int right) {
        if (left > right) return;

        int mid = (left + right) / 2;
        AddNode(elements[mid]);

        RebuildTreeFromArray(elements, left, mid - 1);
        RebuildTreeFromArray(elements, mid + 1, right);
    }

    void BalanceTree() {
        vector<int> elements;
        CollectElements(root, elements);
        Clear();
        RebuildTreeFromArray(elements, 0, elements.size() - 1);
    }
};

int main() {
    Tree tree;

    // Добавление чисел от 1 до 5000
    for (int i = 1; i <= 5000; ++i) {
        tree.AddNode(i);
    }

    tree.ShowTree();
    return 0;
}
