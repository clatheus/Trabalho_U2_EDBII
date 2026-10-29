#ifndef AVL_HPP
#define AVL_HPP

#include <string>

using namespace std;

struct AVLNode {
    int key;
    int height; // Altura da subárvore enraizada neste nó
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k);
};

class AVLTree {
private:
    AVLNode* root;
    long long simpleRotations;
    long long doubleRotations;

    int getHeight(AVLNode* node) const;
    int getBalanceFactor(AVLNode* node) const; // fb = h(esquerda) - h(direita)
    void updateHeight(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y); // Rotação simples à direita
    AVLNode* rotateLeft(AVLNode* x); // Rotação simples à esquerda
    AVLNode* insert(AVLNode* node, int key, bool& inserted);
    AVLNode* getMinValueNode(AVLNode* node); // Localiza o sucessor in-order
    AVLNode* remove(AVLNode* node, int key, bool& removed);
    bool search(AVLNode* node, int key, int& steps) const;
    void inOrder(AVLNode* node) const;
    void printTree(AVLNode* node, const string& prefix, bool isLeft) const;
    void destroy(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    bool insert(int key);
    bool remove(int key);
    bool search(int key, int& steps) const;
    void inOrder() const;
    void print() const;
    int getHeight() const;
    long long getSimpleRotations() const;
    long long getDoubleRotations() const;
    long long getTotalRotations() const;
};

#endif