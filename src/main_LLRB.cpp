#include "LLRB.hpp"
#include <iostream>

using namespace std;

int main() {
    LLRBTree rbt;
    int option, key, steps;

    do {
        cout << "ARVORE RUBRO-NEGRA (LLRB)\n"
             << "1. Inserir Encomenda (ID)\n"
             << "2. Remover Encomenda (ID)\n"
             << "3. Buscar Encomenda\n"
             << "4. Listar Encomendas em Ordem Crescente\n"
             << "5. Visualizar Topologia com Cores [RUBRO] e [NEGRO]\n"
             << "6. Relatorio de Metricas (Rotacoes e Flips)\n"
             << "0. Encerrar\n"
             << "Escolha uma opcao: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Identificador para inserir: ";
                cin >> key;
                if (rbt.insert(key))
                    cout << "[OK] Pacote " << key << " inserido com sucesso.\n";
                else
                    cout << "[ALERTA] Duplicata: Pacote " << key << " ja cadastrado.\n";
                break;
            case 2:
                cout << "Identificador para remover: ";
                cin >> key;
                if (rbt.remove(key))
                    cout << "[OK] Pacote " << key << " removido com sucesso.\n";
                else
                    cout << "[ERRO] Pacote " << key << " inexistente no indice.\n";
                break;
            case 3:
                cout << "Identificador para buscar: ";
                cin >> key;
                if (rbt.search(key, steps))
                    cout << "[LOCALIZADO] Encontrado em " << steps << " comparacoes.\n";
                else
                    cout << "[NAO ENCONTRADO] Varredura encerrou apos " << steps << " comparacoes.\n";
                break;
            case 4:
                cout << "Pacotes em Ordem: ";
                rbt.inOrder();
                break;
            case 5:
                cout << "\nTopologia Hierarquica LLRB:\n";
                rbt.print();
                break;
            case 6:
                cout << "\n--- Metricas Rubro-Negra (LLRB) ---\n"
                     << "Altura: " << rbt.getHeight() << "\n"
                     << "Rotacoes a Esquerda: " << rbt.getLeftRotations() << "\n"
                     << "Rotacoes a Direita: " << rbt.getRightRotations() << "\n"
                     << "Total de Rotacoes: " << rbt.getTotalRotations() << "\n"
                     << "Trocas de Cor (Color Flips): " << rbt.getColorFlips() << "\n";
                break;
        }
    } while (option != 0);

    return 0;
}