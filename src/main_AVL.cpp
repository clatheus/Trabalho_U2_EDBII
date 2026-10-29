#include "AVL.hpp"
#include <iostream>

using namespace std;

int main() {
    AVLTree avl;
    int option, key, steps;

    do {
        cout << "ARVORE AVL\n"
             << "1. Inserir Encomenda (ID)\n"
             << "2. Remover Encomenda (ID)\n"
             << "3. Buscar Encomenda\n"
             << "4. Listar Encomendas em Ordem Crescente\n"
             << "5. Visualizar Estrutura da Arvore\n"
             << "6. Relatorio de Metricas (Altura e Rotacoes)\n"
             << "0. Encerrar\n"
             << "Escolha uma opcao: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Identificador para inserir: ";
                cin >> key;
                if (avl.insert(key))
                    cout << "[OK] Pacote " << key << " inserido com sucesso.\n";
                else
                    cout << "[ALERTA] Duplicata: Pacote " << key << " ja cadastrado.\n";
                break;
            case 2:
                cout << "Identificador para remover: ";
                cin >> key;
                if (avl.remove(key))
                    cout << "[OK] Pacote " << key << " removido com sucesso.\n";
                else
                    cout << "[ERRO] Pacote " << key << " inexistente no indice.\n";
                break;
            case 3:
                cout << "Identificador para buscar: ";
                cin >> key;
                if (avl.search(key, steps))
                    cout << "[LOCALIZADO] Encontrado em " << steps << " comparacoes.\n";
                else
                    cout << "[NAO ENCONTRADO] Varredura encerrou apos " << steps << " comparacoes.\n";
                break;
            case 4:
                cout << "Pacotes em Ordem: ";
                avl.inOrder();
                break;
            case 5:
                cout << "\nTopologia Hierarquica AVL:\n";
                avl.print();
                break;
            case 6:
                cout << "\n--- Metricas AVL ---\n"
                     << "Altura: " << avl.getHeight() << "\n"
                     << "Rotacoes Simples: " << avl.getSimpleRotations() << "\n"
                     << "Rotacoes Duplas: " << avl.getDoubleRotations() << "\n"
                     << "Total de Rebalanceamentos: " << avl.getTotalRotations() << "\n";
                break;
        }
    } while (option != 0);

    return 0;
}