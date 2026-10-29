#ifndef LLRB_HPP
#define LLRB_HPP

#include <string>

using namespace std;

enum Color { RED = true, BLACK = false };

struct RBTNode {
    int key;
    Color color;
    RBTNode* left;
    RBTNode* right;

    RBTNode(int k, Color c);
};

class LLRBTree {
private:
    RBTNode* root;
    long long leftRotations;
    long long rightRotations;
    long long colorFlips;

    bool isRed(RBTNode* node) const;
    RBTNode* rotateLeft(RBTNode* h); // Inclina aresta vermelha para a esquerda
    RBTNode* rotateRight(RBTNode* h); // Desfaz dois vermelhos consecutivos
    void flipColors(RBTNode* h); // Divide nó 4 temporário em nós 2-3
    RBTNode* fixUp(RBTNode* h); // Pipeline de correção LLRB na volta da recursão
    RBTNode* insert(RBTNode* h, int key, bool& inserted);
    RBTNode* moveRedLeft(RBTNode* h); // Propaga nó vermelho para a esquerda na remoção
    RBTNode* moveRedRight(RBTNode* h); // Propaga nó vermelho para a direita na remoção
    RBTNode* deleteMin(RBTNode* h); // Remove o nó mínimo da subárvore
    RBTNode* getMin(RBTNode* h) const;
    RBTNode* remove(RBTNode* h, int key, bool& removed);
    bool search(RBTNode* node, int key, int& steps) const;
    void inOrder(RBTNode* node) const;
    int getHeight(RBTNode* node) const;
    void printTree(RBTNode* node, const string& prefix, bool isLeft) const;
    void destroy(RBTNode* node);

public:
    LLRBTree();
    ~LLRBTree();

    bool insert(int key);
    bool remove(int key);
    bool search(int key, int& steps) const;
    void inOrder() const;
    void print() const;
    int getHeight() const;
    long long getLeftRotations() const;
    long long getRightRotations() const;
    long long getTotalRotations() const;
    long long getColorFlips() const;
};

#endif