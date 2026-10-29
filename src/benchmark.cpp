#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <algorithm>
#include <cassert>

#include "AVL.hpp"
#include "LLRB.hpp"

// Aliases para mapear as classes do seu projeto
using AVL = AVLTree;
using LLRB = LLRBTree;

using namespace std;
using namespace std::chrono;

// Gerador de permutação aleatória de 1 até n
vector<int> gerarAleatorios(int n, unsigned seed = 42) {
    vector<int> dados(n);
    iota(dados.begin(), dados.end(), 1);
    mt19937 g(seed);
    shuffle(dados.begin(), dados.end(), g);
    return dados;
}

int main() {
    const int N = 100000;
    int stepsDummy = 0;

    cout << "========================================================\n";
    cout << " INICIANDO TESTES COMPARATIVOS AVL vs LLRB (N = " << N << ")\n";
    cout << "========================================================\n\n";

    // 1. Casos de borda: arvore vazia e no unico
    cout << "[1/4] Executando casos de borda...\n";
    {
        AVL avlBorda;
        LLRB llrbBorda;

        // Busca e remocao em arvore vazia
        assert(!avlBorda.search(10, stepsDummy));
        assert(!llrbBorda.search(10, stepsDummy));
        avlBorda.remove(10);
        llrbBorda.remove(10);

        // Insercao e remocao de um unico elemento
        avlBorda.insert(99);
        llrbBorda.insert(99);
        assert(avlBorda.search(99, stepsDummy));
        assert(llrbBorda.search(99, stepsDummy));

        avlBorda.remove(99);
        llrbBorda.remove(99);
        assert(!avlBorda.search(99, stepsDummy));
        assert(!llrbBorda.search(99, stepsDummy));

        cout << "  -> Arvore vazia e no unico validados com sucesso.\n\n";
    }

    // 2. Cenários de Inserção: Crescente, Decrescente e Nao Ordenada
    cout << "[2/4] Executando cenarios de insercao...\n";

    vector<int> crescente(N);
    iota(crescente.begin(), crescente.end(), 1);

    vector<int> decrescente(N);
    iota(decrescente.rbegin(), decrescente.rend(), 1);

    vector<int> aleatoria = gerarAleatorios(N);

    auto testarInsercao = [](const string& rotulo, const vector<int>& dados) {
        AVL avl;
        LLRB llrb;

        auto inicio = high_resolution_clock::now();
        for (int v : dados) avl.insert(v);
        auto fim = high_resolution_clock::now();
        auto duracaoAVL = duration_cast<milliseconds>(fim - inicio).count();

        inicio = high_resolution_clock::now();
        for (int v : dados) llrb.insert(v);
        fim = high_resolution_clock::now();
        auto duracaoLLRB = duration_cast<milliseconds>(fim - inicio).count();

        cout << "  Cenario: " << rotulo << "\n";
        cout << "    AVL  -> Tempo: " << duracaoAVL << " ms | Altura: " << avl.getHeight() << "\n";
        cout << "    LLRB -> Tempo: " << duracaoLLRB << " ms | Altura: " << llrb.getHeight() << "\n\n";
    };

    testarInsercao("Ordem Crescente", crescente);
    testarInsercao("Ordem Decrescente", decrescente);
    testarInsercao("Nao Ordenada (Aleatoria)", aleatoria);

    // 3. Busca de elementos existentes e inexistentes
    cout << "[3/4] Executando testes de busca...\n";
    AVL avlPrincipal;
    LLRB llrbPrincipal;

    for (int v : aleatoria) {
        avlPrincipal.insert(v);
        llrbPrincipal.insert(v);
    }

    // Busca de 100k elementos existentes
    long long passosAVL_existentes = 0;
    auto inicio = high_resolution_clock::now();
    for (int v : aleatoria) {
        int s = 0;
        avlPrincipal.search(v, s);
        passosAVL_existentes += s;
    }
    auto fim = high_resolution_clock::now();
    auto tempoBuscaAVL_existentes = duration_cast<milliseconds>(fim - inicio).count();

    long long passosLLRB_existentes = 0;
    inicio = high_resolution_clock::now();
    for (int v : aleatoria) {
        int s = 0;
        llrbPrincipal.search(v, s);
        passosLLRB_existentes += s;
    }
    fim = high_resolution_clock::now();
    auto tempoBuscaLLRB_existentes = duration_cast<milliseconds>(fim - inicio).count();

    cout << "  Busca 100k existentes:\n";
    cout << "    AVL  -> Tempo: " << tempoBuscaAVL_existentes 
         << " ms | Media de passos/chave: " << (double)passosAVL_existentes / N << "\n";
    cout << "    LLRB -> Tempo: " << tempoBuscaLLRB_existentes 
         << " ms | Media de passos/chave: " << (double)passosLLRB_existentes / N << "\n\n";

    // Busca de 100k elementos inexistentes
    long long passosAVL_inexistentes = 0;
    inicio = high_resolution_clock::now();
    for (int v = N + 1; v <= 2 * N; ++v) {
        int s = 0;
        avlPrincipal.search(v, s);
        passosAVL_inexistentes += s;
    }
    fim = high_resolution_clock::now();
    auto tempoBuscaAVL_inexistentes = duration_cast<milliseconds>(fim - inicio).count();

    long long passosLLRB_inexistentes = 0;
    inicio = high_resolution_clock::now();
    for (int v = N + 1; v <= 2 * N; ++v) {
        int s = 0;
        llrbPrincipal.search(v, s);
        passosLLRB_inexistentes += s;
    }
    fim = high_resolution_clock::now();
    auto tempoBuscaLLRB_inexistentes = duration_cast<milliseconds>(fim - inicio).count();

    cout << "  Busca 100k inexistentes:\n";
    cout << "    AVL  -> Tempo: " << tempoBuscaAVL_inexistentes 
         << " ms | Media de passos/chave: " << (double)passosAVL_inexistentes / N << "\n";
    cout << "    LLRB -> Tempo: " << tempoBuscaLLRB_inexistentes 
         << " ms | Media de passos/chave: " << (double)passosLLRB_inexistentes / N << "\n\n";

    // 4. Remocao: elementos existentes e inexistentes
    cout << "[4/4] Executando testes de remocao...\n";

    // Remocao de 50.000 chaves (abrangendo folhas, nós com 1 filho e 2 filhos)
    inicio = high_resolution_clock::now();
    for (int i = 0; i < N / 2; ++i) avlPrincipal.remove(aleatoria[i]);
    fim = high_resolution_clock::now();
    cout << "  Remocao 50k nos (AVL):  " 
         << duration_cast<milliseconds>(fim - inicio).count() 
         << " ms | Altura final: " << avlPrincipal.getHeight() << "\n";

    inicio = high_resolution_clock::now();
    for (int i = 0; i < N / 2; ++i) llrbPrincipal.remove(aleatoria[i]);
    fim = high_resolution_clock::now();
    cout << "  Remocao 50k nos (LLRB): " 
         << duration_cast<milliseconds>(fim - inicio).count() 
         << " ms | Altura final: " << llrbPrincipal.getHeight() << "\n";

    // Tentativa de remocao de inexistentes
    for (int v = N + 1; v <= N + 5000; ++v) {
        avlPrincipal.remove(v);
        llrbPrincipal.remove(v);
    }
    cout << "  Tentativas de remocao de elementos inexistentes executadas com sucesso.\n\n";

    cout << "========================================================\n";
    cout << " TESTES FINALIZADOS COM SUCESSO!\n";
    cout << "========================================================\n";

    return 0;
}