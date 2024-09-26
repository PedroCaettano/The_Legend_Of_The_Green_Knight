#include "game.h"
#include <iostream>

Jogo::Jogo() {
    galdwin.nome = "Sir Galdwin";
    galdwin.vida = 100;
    galdwin.espada = {"Espada de Galdwin", 5, 10};
    galdwin.machado = {"Machado do Cavaleiro Verde", 15, 20};
    galdwin.escudo = {"Escudo de Galdwin", 10, 5};
    galdwin.pesoMaxCinto = 20;
    galdwin.pesoMaxMochila = 50;
    galdwin.pesoAtualCinto = 0;
    galdwin.pesoAtualMochila = 0;
    
    // Definir inimigos
    inimigos[0] = {"Ladrão", 30, 5};
    inimigos[1] = {"Fantasma", 20, 10};
    inimigos[2] = {"Galdwin Maligno", 100, 15};
    inimigos[3] = {"Rei Purpura", 120, 0};  // Combate espiritual
    inimigos[4] = {"Cavaleiro Verde", 200, 30};

    poções[0] = {"Poção Menor", 1, 10};
    poções[1] = {"Poção Maior", 2, 25};
}

void Jogo::iniciar() {
    std::cout << "Bem-vindo à jornada de Sir Galdwin!" << std::endl;
    nivel1();
}

void Jogo::nivel1() {
    std::cout << "Nivel 1: Galdwin enfrenta os ladrões." << std::endl;
    galdwin.atacar(inimigos[0], galdwin.espada);
    mostrarStatus();
    nivel2();
}

void Jogo::nivel2() {
    std::cout << "Nivel 2: Galdwin ajuda Willow contra os fantasmas." << std::endl;
    galdwin.atacar(inimigos[1], galdwin.espada);
    mostrarStatus();
    nivel3();
}

void Jogo::nivel3() {
    std::cout << "Nivel 3: Galdwin enfrenta a si mesmo." << std::endl;
    galdwin.atacar(inimigos[2], galdwin.machado);
    mostrarStatus();
    nivel4();
}

void Jogo::nivel4() {
    std::cout << "Nivel 4: Galdwin encontra o Rei Purpura e a Rainha Ametista." << std::endl;
    std::cout << "Desafio espiritual iniciado..." << std::endl;
    mostrarStatus();
    nivelFinal();
}

void Jogo::nivelFinal() {
    std::cout << "Nivel Final: O desafio contra o Cavaleiro Verde começa." << std::endl;
    galdwin.atacar(inimigos[4], galdwin.machado);
    mostrarStatus();
}

void Jogo::mostrarStatus() {
    std::cout << "Status do jogador: Vida: " << galdwin.vida << std::endl;
}

void Jogador::atacar(Inimigo &inimigo, Arma &arma) {
    std::cout << "Atacando " << inimigo.nome << " com " << arma.nome << std::endl;
    inimigo.vida -= arma.ataque;
    if (inimigo.vida <= 0) {
        std::cout << inimigo.nome << " foi derrotado!" << std::endl;
    } else {
        vida -= inimigo.ataque;
        std::cout << "Você foi atacado! Vida restante: " << vida << std::endl;
    }
}

void Jogador::curar(Pocao &pocao) {
    std::cout << "Usando " << pocao.nome << " para curar " << pocao.cura << " de vida." << std::endl;
    vida += pocao.cura;
}

bool Jogador::pegarItem(Item item) {
    if (pesoAtualCinto + item.peso <= pesoMaxCinto) {
        cinto[pesoAtualCinto] = item;
        pesoAtualCinto += item.peso;
        std::cout << item.nome << " adicionado ao cinto." << std::endl;
        return true;
    } else {
        std::cout << "Cinto cheio. Adicionando à mochila." << std::endl;
        mochila[pesoAtualMochila] = item;
        pesoAtualMochila += item.peso;
        return false;
    }
}

bool Jogador::usarItem(int posicaoCinto) {
    if (posicaoCinto >= 0 && posicaoCinto < 3) {
        std::cout << "Usando " << cinto[posicaoCinto].nome << std::endl;
        // Lógica para usar o item
        return true;
    }
    return false;
}

void Jogador::removerItemMochila(int posicao) {
    std::cout << "Removendo " << mochila[posicao].nome << " da mochila." << std::endl;
    for (int i = posicao; i < 9; ++i) {
        mochila[i] = mochila[i + 1];
    }
}



