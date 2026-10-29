# Trabalho_U2_EDBII
# Amazon Engineering Challenge: Árvores Balanceadas (AVL e Rubro-Negra LLRB)

**Disciplina:** EDB II

**Instituição:** IMD/UFRN

**Aluno:** Matheus Lucheze Lopes 

## 1. Visão Geral do Projeto

### O Problema da Árvore de Busca Comum (BST)
Se os identificadores de encomendas chegarem em ordem sequencial (por exemplo: `101, 102, 103, 104...`), uma árvore binária comum perde sua forma ramificada e degenera em uma lista encadeada (formato linear/zigue-zague)[cite: 170, 419]. Nesses casos, o tempo de busca deixa de ser rápido ($O(\log n)$) e passa a ser lento ($O(n)$)[cite: 8, 419].

### A Solução
Este projeto implementa e analisa comparativamente dois dos principais algoritmos auto-balanceados da computação, garantindo tempo de resposta $O(\log n)$ mesmo nos piores cenários de entrada[cite: 336, 423, 634, 638]:
* **Árvore AVL:** Rigidez no balanceamento por controle direto das alturas das subárvores[cite: 338, 423].
* **Árvore Rubro-Negra (LLRB):** Balanceamento flexível por cores e codificação de Árvores 2-3, minimizando reestruturações pesadas na memória[cite: 337, 347, 350].

## 2. Instruções de Compilação e Execução

### Árvore AVL
* **Compilação:** g++ -std=c++17 -Iinclude src/AVL.cpp src/main_AVL.cpp -o avl_app
* **Execução op1:** ./avl_app
* **Execução op2:** avl_app.exe

### Árvore Rubro-Negra (LLRB)
* **Compilação:** g++ -std=c++17 -Iinclude src/LLRB.cpp src/main_LLRB.cpp -o llrb_app
* **Execução op1:** ./llrb_app
* **Execução op2:** llrb_app.exe
