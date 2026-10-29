#include "LLRB.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

RBTNode::RBTNode(int k, Color c) : key(k), color(c), left(nullptr), right(nullptr) {}

LLRBTree::LLRBTree() : root(nullptr), leftRotations(0), rightRotations(0), colorFlips(0) {}

LLRBTree::~LLRBTree() {
    destroy(root);
}

void LLRBTree::clear() {
    destroy(root);
    root = nullptr;
    leftRotations = 0;
    rightRotations = 0;
    colorFlips = 0;
}

bool LLRBTree::isRed(RBTNode* node) const { // Nós nulos sempre são pretos
    return (node && node->color == RED);
}

RBTNode* LLRBTree::rotateLeft(RBTNode* h) { // Puxa a aresta vermelha da direita para a esquerda
    RBTNode* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    leftRotations++;
    return x;
}

RBTNode* LLRBTree::rotateRight(RBTNode* h) { // Desfaz cadeia com dois vermelhos seguidos à esquerda
    RBTNode* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    rightRotations++;
    return x;
}

void LLRBTree::flipColors(RBTNode* h) { // Inverte as cores do pai e de ambos os filhos
    h->color = (h->color == RED) ? BLACK : RED;
    if (h->left)  h->left->color  = (h->left->color == RED) ? BLACK : RED;
    if (h->right) h->right->color = (h->right->color == RED) ? BLACK : RED;
    colorFlips++;
}

RBTNode* LLRBTree::fixUp(RBTNode* h) { // Pipeline de balanceamento da LLRB executado na volta de toda modificação
    if (isRed(h->right) && !isRed(h->left))
        h = rotateLeft(h);

    if (isRed(h->left) && isRed(h->left->left))
        h = rotateRight(h);

    if (isRed(h->left) && isRed(h->right))
        flipColors(h);

    return h;
}

RBTNode* LLRBTree::insert(RBTNode* h, int key, bool& inserted) {
    if (!h) {
        inserted = true;
        return new RBTNode(key, RED);
    }

    if (key < h->key) {
        h->left = insert(h->left, key, inserted);
    } else if (key > h->key) {
        h->right = insert(h->right, key, inserted);
    } else {
        inserted = false;
        return h;
    }

    return fixUp(h);
}

RBTNode* LLRBTree::moveRedLeft(RBTNode* h) { // Puxa o nó vermelho para a esquerda preparando remoção segura
    flipColors(h);
    if (h->right && isRed(h->right->left)) {
        h->right = rotateRight(h->right);
        h = rotateLeft(h);
        flipColors(h);
    }
    return h;
}

RBTNode* LLRBTree::moveRedRight(RBTNode* h) { // Puxa o nó vermelho para a direita preparando remoção segura
    flipColors(h);
    if (h->left && isRed(h->left->left)) {
        h = rotateRight(h);
        flipColors(h);
    }
    return h;
}

RBTNode* LLRBTree::deleteMin(RBTNode* h) {
    if (!h->left) {
        delete h;
        return nullptr;
    }

    if (!isRed(h->left) && !isRed(h->left->left)) {
        h = moveRedLeft(h);
    }

    h->left = deleteMin(h->left);
    return fixUp(h);
}

RBTNode* LLRBTree::getMin(RBTNode* h) const {
    while (h->left) h = h->left;
    return h;
}

RBTNode* LLRBTree::remove(RBTNode* h, int key, bool& removed) {
    if (!h) return nullptr;

    if (key < h->key) {
        if (h->left) {
            if (!isRed(h->left) && !isRed(h->left->left)) {
                h = moveRedLeft(h);
            }
            h->left = remove(h->left, key, removed);
        }
    } else {
        if (isRed(h->left)) {
            h = rotateRight(h);
        }

        if (key == h->key && !h->right) {
            removed = true;
            delete h;
            return nullptr;
        }

        if (h->right) {
            if (!isRed(h->right) && !isRed(h->right->left)) {
                h = moveRedRight(h);
            }

            if (key == h->key) {
                removed = true;
                RBTNode* minRight = getMin(h->right);
                h->key = minRight->key;
                h->right = deleteMin(h->right);
            } else {
                h->right = remove(h->right, key, removed);
            }
        }
    }

    return fixUp(h);
}

bool LLRBTree::search(RBTNode* node, int key, int& steps) const {
    if (!node) return false;
    steps++;
    if (key == node->key) return true;
    if (key < node->key) return search(node->left, key, steps);
    return search(node->right, key, steps);
}

void LLRBTree::inOrder(RBTNode* node) const {
    if (!node) return;
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}

int LLRBTree::getHeight(RBTNode* node) const {
    if (!node) return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

void LLRBTree::printTree(RBTNode* node, const string& prefix, bool isLeft) const {
    if (!node) return;
    cout << prefix << (isLeft ? "|-- " : "`-- ")
         << node->key << (node->color == RED ? " [RUBRO]" : " [NEGRO]") << "\n";

    printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
    printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
}

void LLRBTree::destroy(RBTNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool LLRBTree::insert(int key) {
    bool inserted = false;
    root = insert(root, key, inserted);
    if (root) root->color = BLACK;
    return inserted;
}

bool LLRBTree::remove(int key) {
    bool removed = false;
    if (!root) return false;

    if (!isRed(root->left) && !isRed(root->right)) {
        root->color = RED;
    }

    root = remove(root, key, removed);
    if (root) root->color = BLACK;
    return removed;
}

bool LLRBTree::search(int key, int& steps) const {
    steps = 0;
    return search(root, key, steps);
}

void LLRBTree::inOrder() const {
    if (!root) cout << "[Arvore Vazia]";
    else inOrder(root);
    cout << "\n";
}

void LLRBTree::print() const {
    if (!root) {
        cout << "  (Arvore Vazia)\n";
        return;
    }
    printTree(root, "", false);
}

int LLRBTree::getHeight() const { return getHeight(root); }
long long LLRBTree::getLeftRotations() const { return leftRotations; }
long long LLRBTree::getRightRotations() const { return rightRotations; }
long long LLRBTree::getTotalRotations() const { return leftRotations + rightRotations; }
long long LLRBTree::getColorFlips() const { return colorFlips; }