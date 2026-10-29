#include "AVL.hpp"
#include <iostream>
#include <vector>

using namespace std;

void executarBateriaDeTestes(AVLTree& avl) {
    cout << "\n========================================================\n"
         << "   EXECUCAO DA BATERIA DE TESTES AUTOMATIZADOS (AVL)    \n"
         << "========================================================\n";

    // 1. Árvore Vazia e Nó Único
    cout << "\n[TESTE 1] Operacoes em Arvore Vazia e No Unico:\n";
    avl.clear();
    int steps = 0;
    cout << " - Busca em arvore vazia (ID 99): " << (avl.search(99, steps) ? "Encontrado" : "Nao Encontrado") << " (passos: " << steps << ")\n";
    cout << " - Remocao em arvore vazia (ID 99): " << (avl.remove(99) ? "Removido" : "Falha tratada") << "\n";
    avl.insert(100);
    cout << " - Inserido no unico (100). Altura: " << avl.getHeight() << "\n";
    avl.remove(100);
    cout << " - Removido no unico. Altura final: " << avl.getHeight() << "\n";

    // 2. Inserção em Ordem Crescente (Pior Caso de BST)
    cout << "\n[TESTE 2] Insercao em Ordem Crescente [10, 20, 30, 40, 50, 60, 70]:\n";
    avl.clear();
    vector<int> crescente = {10, 20, 30, 40, 50, 60, 70};
    for (int v : crescente) avl.insert(v);
    cout << " - Elementos em ordem: "; avl.inOrder();
    cout << " - Altura final: " << avl.getHeight() << " (esperado log2: 3)\n";
    cout << " - Rotacoes simples: " << avl.getSimpleRotations() 
         << " | Rotacoes duplas: " << avl.getDoubleRotations() << "\n";

    // 3. Inserção em Ordem Decrescente
    cout << "\n[TESTE 3] Insercao em Ordem Decrescente [70, 60, 50, 40, 30, 20, 10]:\n";
    avl.clear();
    vector<int> decrescente = {70, 60, 50, 40, 30, 20, 10};
    for (int v : decrescente) avl.insert(v);
    cout << " - Elementos em ordem: "; avl.inOrder();
    cout << " - Altura final: " << avl.getHeight() << "\n";
    cout << " - Total de rotacoes: " << avl.getTotalRotations() << "\n";

    // 4. Inserção Não Ordenada (Cenário Black Friday)
    cout << "\n[TESTE 4] Insercao Nao Ordenada (Carga Black Friday, N=15):\n";
    avl.clear();
    vector<int> blackFriday = {50, 25, 75, 12, 35, 60, 85, 5, 18, 30, 40, 55, 65, 80, 95};
    for (int v : blackFriday) avl.insert(v);
    cout << " - Elementos em ordem: "; avl.inOrder();
    cout << " - Altura apos insercoes: " << avl.getHeight() << "\n";
    cout << " - Rotacoes acumuladas: " << avl.getTotalRotations() << "\n";
    cout << "Topologia atual:\n";
    avl.print();

    // 5. Teste de Busca (Existentes e Inexistentes)
    cout << "\n[TESTE 5] Testes de Busca de Encomendas:\n";
    avl.search(50, steps);
    cout << " - Busca pela raiz (50): " << steps << " comparacoes.\n";
    avl.search(95, steps);
    cout << " - Busca por folha profunda (95): " << steps << " comparacoes.\n";
    avl.search(999, steps);
    cout << " - Busca por chave inexistente (999): " << steps << " comparacoes.\n";

    // 6. Teste de Remoções com Diferentes Configurações de Filhos
    cout << "\n[TESTE 6] Remocoes com Diferentes Configuracoes:\n";
    cout << " - Tentativa de remover chave inexistente (404): " 
         << (avl.remove(404) ? "Removido" : "Nao encontrado (tratado sem erro)") << "\n";
    cout << " - Remocao de no folha (5): " << (avl.remove(5) ? "OK" : "Erro") << "\n";
    cout << " - Remocao de no com 1 filho (12): " << (avl.remove(12) ? "OK" : "Erro") << "\n";
    cout << " - Remocao de no com 2 filhos (raiz 50): " << (avl.remove(50) ? "OK" : "Erro") << "\n";
    cout << " - Altura final apos remocoes: " << avl.getHeight() << "\n";
    cout << "Topologia apos todas as remocoes:\n";
    avl.print();
    cout << "========================================================\n\n";
}

int main() {
    AVLTree avl;
    int option, key, steps;

    do {
        cout << "\n========================================\n"
             << " AMAZON LOGISTICS: ARVORE AVL           \n"
             << "========================================\n"
             << "1. Inserir Encomenda (ID)\n"
             << "2. Remover Encomenda (ID)\n"
             << "3. Buscar Encomenda\n"
             << "4. Listar Encomendas em Ordem Crescente\n"
             << "5. Visualizar Estrutura da Arvore\n"
             << "6. Relatorio de Metricas (Altura e Rotacoes)\n"
             << "7. Executar Bateria de Testes Automatizados (Seccao 3)\n"
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
            case 7:
                executarBateriaDeTestes(avl);
                break;
        }
    } while (option != 0);

    return 0;
}