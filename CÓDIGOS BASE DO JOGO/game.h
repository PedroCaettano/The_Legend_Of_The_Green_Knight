#ifndef GAME_H
#define GAME_H

struct Item {
    std::string nome;
    int peso;
};

struct Arma : public Item {
    int ataque;
};

struct Pocao : public Item {
    int cura;
};

struct Inimigo {
    std::string nome;
    int vida;
    int ataque;
};

struct Jogador {
    std::string nome;
    int vida;
    Arma espada;
    Arma machado;
    Arma escudo;
    Item cinto[3];
    Item mochila[10];  // Exemplo: tamanho da mochila
    int pesoMaxCinto;
    int pesoMaxMochila;
    int pesoAtualCinto;
    int pesoAtualMochila;

    void atacar(Inimigo &inimigo, Arma &arma);
    void curar(Pocao &pocao);
    bool pegarItem(Item item);
    bool usarItem(int posicaoCinto);
    void removerItemMochila(int posicao);
};

class Jogo {
public:
    Jogo();
    void iniciar();
    void nivel1();
    void nivel2();
    void nivel3();
    void nivel4();
    void nivelFinal();
    bool checarFimDoJogo();
private:
    Jogador galdwin;
    Inimigo inimigos[5];
    Pocao poções[2];
    void mostrarStatus();
};

#endif
