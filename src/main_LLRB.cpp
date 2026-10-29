#include "LLRB.hpp"
#include <iostream>
#include <vector>

using namespace std;

void executarBateriaDeTestes(LLRBTree& rbt) {
    cout << "\n========================================================\n"
         << "   EXECUCAO DA BATERIA DE TESTES AUTOMATIZADOS (LLRB)   \n"
         << "========================================================\n";

    // 1. Árvore Vazia e Nó Único
    cout << "\n[TESTE 1] Operacoes em Arvore Vazia e No Unico:\n";
    rbt.clear();
    int steps = 0;
    cout << " - Busca em arvore vazia (ID 99): " << (rbt.search(99, steps) ? "Encontrado" : "Nao Encontrado") << " (passos: " << steps << ")\n";
    cout << " - Remocao em arvore vazia (ID 99): " << (rbt.remove(99) ? "Removido" : "Falha tratada") << "\n";
    rbt.insert(100);
    cout << " - Inserido no unico (100). Altura: " << rbt.getHeight() << "\n";
    rbt.remove(100);
    cout << " - Removido no unico. Altura final: " << rbt.getHeight() << "\n";

    // 2. Inserção em Ordem Crescente (Pior Caso de BST)
    cout << "\n[TESTE 2] Insercao em Ordem Crescente [10, 20, 30, 40, 50, 60, 70]:\n";
    rbt.clear();
    vector<int> crescente = {10, 20, 30, 40, 50, 60, 70};
    for (int v : crescente) rbt.insert(v);
    cout << " - Elementos em ordem: "; rbt.inOrder();
    cout << " - Altura final: " << rbt.getHeight() << "\n";
    cout << " - Rotacoes fisicas: " << rbt.getTotalRotations() 
         << " | Trocas de cor (flips): " << rbt.getColorFlips() << "\n";

    // 3. Inserção em Ordem Decrescente
    cout << "\n[TESTE 3] Insercao em Ordem Decrescente [70, 60, 50, 40, 30, 20, 10]:\n";
    rbt.clear();
    vector<int> decrescente = {70, 60, 50, 40, 30, 20, 10};
    for (int v : decrescente) rbt.insert(v);
    cout << " - Elementos em ordem: "; rbt.inOrder();
    cout << " - Altura final: " << rbt.getHeight() << "\n";
    cout << " - Rotacoes fisicas: " << rbt.getTotalRotations() 
         << " | Trocas de cor: " << rbt.getColorFlips() << "\n";

    // 4. Inserção Não Ordenada (Cenário Black Friday)
    cout << "\n[TESTE 4] Insercao Nao Ordenada (Carga Black Friday, N=15):\n";
    rbt.clear();
    vector<int> blackFriday = {50, 25, 75, 12, 35, 60, 85, 5, 18, 30, 40, 55, 65, 80, 95};
    for (int v : blackFriday) rbt.insert(v);
    cout << " - Elementos em ordem: "; rbt.inOrder();
    cout << " - Altura apos insercoes: " << rbt.getHeight() << "\n";
    cout << " - Rotacoes acumuladas: " << rbt.getTotalRotations() 
         << " | Trocas de cor: " << rbt.getColorFlips() << "\n";
    cout << "Topologia atual:\n";
    rbt.print();

    // 5. Teste de Busca (Existentes e Inexistentes)
    cout << "\n[TESTE 5] Testes de Busca de Encomendas:\n";
    rbt.search(50, steps);
    cout << " - Busca pela raiz (50): " << steps << " comparacoes.\n";
    rbt.search(95, steps);
    cout << " - Busca por folha profunda (95): " << steps << " comparacoes.\n";
    rbt.search(999, steps);
    cout << " - Busca por chave inexistente (999): " << steps << " comparacoes.\n";

    // 6. Teste de Remoções com Diferentes Configurações de Filhos
    cout << "\n[TESTE 6] Remocoes com Diferentes Configuracoes:\n";
    cout << " - Tentativa de remover chave inexistente (404): " 
         << (rbt.remove(404) ? "Removido" : "Nao encontrado (tratado sem erro)") << "\n";
    cout << " - Remocao de no folha (5): " << (rbt.remove(5) ? "OK" : "Erro") << "\n";
    cout << " - Remocao de no com 1 filho (12): " << (rbt.remove(12) ? "OK" : "Erro") << "\n";
    cout << " - Remocao de no com 2 filhos (raiz 50): " << (rbt.remove(50) ? "OK" : "Erro") << "\n";
    cout << " - Altura final apos remocoes: " << rbt.getHeight() << "\n";
    cout << "Topologia apos todas as remocoes:\n";
    rbt.print();
    cout << "========================================================\n\n";
}

int main() {
    LLRBTree rbt;
    int option, key, steps;

    do {
        cout << "\n===============================================\n"
             << " AMAZON LOGISTICS: ARVORE RUBRO-NEGRA (LLRB)   \n"
             << "===============================================\n"
             << "1. Inserir Encomenda (ID)\n"
             << "2. Remover Encomenda (ID)\n"
             << "3. Buscar Encomenda\n"
             << "4. Listar Encomendas em Ordem Crescente\n"
             << "5. Visualizar Topologia com Cores [RUBRO] e [NEGRO]\n"
             << "6. Relatorio de Metricas (Rotacoes e Flips)\n"
             << "7. Executar Bateria de Testes Automatizados (Seccao 3)\n"
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
            case 7:
                executarBateriaDeTestes(rbt);
                break;
        }
    } while (option != 0);

    return 0;
}