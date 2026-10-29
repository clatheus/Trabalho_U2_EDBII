#include "AVL.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

AVLNode::AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}

AVLTree::AVLTree() : root(nullptr), simpleRotations(0), doubleRotations(0) {}

AVLTree::~AVLTree() {
    destroy(root);
}

void AVLTree::clear() {
    destroy(root);
    root = nullptr;
    simpleRotations = 0;
    doubleRotations = 0;
}

int AVLTree::getHeight(AVLNode* node) const {
    return node ? node->height : 0; // Nó nulo possui altura 0
}

int AVLTree::getBalanceFactor(AVLNode* node) const {
    return node ? (getHeight(node->left) - getHeight(node->right)) : 0;
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

AVLNode* AVLTree::rotateRight(AVLNode* y) { // Rotação simples à direita: corrige inclinação LL
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    simpleRotations++;
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) { // Rotação simples à esquerda: corrige inclinação RR
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    simpleRotations++;
    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, int key, bool& inserted) {
    if (!node) {
        inserted = true;
        return new AVLNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, inserted);
    } else if (key > node->key) {
        node->right = insert(node->right, key, inserted);
    } else {
        inserted = false;
        return node;
    }

    updateHeight(node);
    int balance = getBalanceFactor(node);

    // Caso LL
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Caso LR
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        doubleRotations++;
        simpleRotations--;
        return rotateRight(node);
    }

    // Caso RR
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Caso RL
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        doubleRotations++;
        simpleRotations--;
        return rotateLeft(node);
    }

    return node;
}

AVLNode* AVLTree::getMinValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLNode* AVLTree::remove(AVLNode* node, int key, bool& removed) {
    if (!node) {
        removed = false;
        return nullptr;
    }

    if (key < node->key) {
        node->left = remove(node->left, key, removed);
    } else if (key > node->key) {
        node->right = remove(node->right, key, removed);
    } else {
        removed = true;
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode* temp = getMinValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key, removed);
        }
    }

    if (!node) return nullptr;

    updateHeight(node);
    int balance = getBalanceFactor(node);

    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        doubleRotations++;
        simpleRotations--;
        return rotateRight(node);
    }

    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        doubleRotations++;
        simpleRotations--;
        return rotateLeft(node);
    }

    return node;
}

bool AVLTree::search(AVLNode* node, int key, int& steps) const {
    if (!node) return false;
    steps++;
    if (key == node->key) return true;
    if (key < node->key) return search(node->left, key, steps);
    return search(node->right, key, steps);
}

void AVLTree::inOrder(AVLNode* node) const {
    if (!node) return;
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}

void AVLTree::printTree(AVLNode* node, const string& prefix, bool isLeft) const {
    if (!node) return;
    cout << prefix << (isLeft ? "|-- " : "`-- ")
         << node->key << " (alt: " << node->height << ", fb: " << getBalanceFactor(node) << ")\n";

    printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
    printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
}

void AVLTree::destroy(AVLNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool AVLTree::insert(int key) {
    bool inserted = false;
    root = insert(root, key, inserted);
    return inserted;
}

bool AVLTree::remove(int key) {
    bool removed = false;
    root = remove(root, key, removed);
    return removed;
}

bool AVLTree::search(int key, int& steps) const {
    steps = 0;
    return search(root, key, steps);
}

void AVLTree::inOrder() const {
    if (!root) cout << "[Arvore Vazia]";
    else inOrder(root);
    cout << "\n";
}

void AVLTree::print() const {
    if (!root) {
        cout << "  (Arvore Vazia)\n";
        return;
    }
    printTree(root, "", false);
}

int AVLTree::getHeight() const { return getHeight(root); }
long long AVLTree::getSimpleRotations() const { return simpleRotations; }
long long AVLTree::getDoubleRotations() const { return doubleRotations; }
long long AVLTree::getTotalRotations() const { return simpleRotations + doubleRotations; }