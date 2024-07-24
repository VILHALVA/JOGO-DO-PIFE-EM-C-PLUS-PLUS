#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void embaralharBaralho(vector<int>& baralho) {
    random_shuffle(baralho.begin(), baralho.end());
}

void distribuirCartas(vector<int>& baralho, vector<int>& mao, int& cartasDistribuidas) {
    for (int i = 0; i < cartasDistribuidas; ++i) {
        mao.push_back(baralho.back());
        baralho.pop_back();
    }
}

void exibirMao(const vector<int>& mao) {
    for (int carta : mao) {
        cout << carta << " ";
    }
    cout << endl;
}

bool verificarSequencia(const vector<int>& mao) {
    if (mao.size() < 3) return false;
    vector<int> maoOrdenada = mao;
    sort(maoOrdenada.begin(), maoOrdenada.end());

    for (size_t i = 0; i < maoOrdenada.size() - 2; ++i) {
        if (maoOrdenada[i] + 1 == maoOrdenada[i + 1] && maoOrdenada[i] + 2 == maoOrdenada[i + 2]) {
            return true;
        }
    }
    return false;
}

bool verificarTrinca(const vector<int>& mao) {
    if (mao.size() < 3) return false;
    vector<int> maoOrdenada = mao;
    sort(maoOrdenada.begin(), maoOrdenada.end());

    for (size_t i = 0; i < maoOrdenada.size() - 2; ++i) {
        if (maoOrdenada[i] == maoOrdenada[i + 1] && maoOrdenada[i] == maoOrdenada[i + 2]) {
            return true;
        }
    }
    return false;
}

bool verificarVitoria(const vector<int>& mao) {
    return verificarSequencia(mao) || verificarTrinca(mao);
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<int> baralho;
    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            baralho.push_back(i);  
        }
    }

    embaralharBaralho(baralho);

    vector<int> maoJogador, maoOponente;
    int cartasDistribuidas = 7;

    distribuirCartas(baralho, maoJogador, cartasDistribuidas);
    distribuirCartas(baralho, maoOponente, cartasDistribuidas);

    cout << "Mão do Jogador: ";
    exibirMao(maoJogador);

    cout << "Aguarde enquanto o oponente joga..." << endl;

    if (verificarVitoria(maoOponente)) {
        cout << "O oponente ganhou!" << endl;
        return 0;
    }

    char acao;
    cout << "Deseja trocar uma carta com o baralho? (s/n): ";
    cin >> acao;

    if (acao == 's' || acao == 'S') {
        int cartaTroca;
        cout << "Escolha uma carta para trocar (informe o valor): ";
        cin >> cartaTroca;

        auto it = find(maoJogador.begin(), maoJogador.end(), cartaTroca);
        if (it != maoJogador.end()) {
            maoJogador.erase(it);
            maoJogador.push_back(baralho.back());
            baralho.pop_back();
        } else {
            cout << "Carta não encontrada na sua mão!" << endl;
        }
    }

    cout << "Sua nova mão: ";
    exibirMao(maoJogador);

    if (verificarVitoria(maoJogador)) {
        cout << "Você ganhou!" << endl;
    } else {
        cout << "Você perdeu!" << endl;
    }

    return 0;
}
