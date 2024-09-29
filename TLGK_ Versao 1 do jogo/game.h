#ifndef GAME_H
#define GAME_H

#include <string>

// Classe representando um item (arma ou poção)
class Item {
public:
    std::string name;
    int weight;
    int attackPower;
    int healingPower;

    Item(std::string n, int w, int ap = 0, int hp = 0);
};

// Classe representando um inimigo
class Enemy {
public:
    std::string name;
    int healthPoints;
    int attackPower;

    Enemy(std::string n, int hp, int ap);

    void takeDamage(int dmg);
    bool isDefeated();
};

// Classe representando o protagonista Sir Galdwin
class SirGaldwin {
public:
    int healthPoints;
    Item* belt[3]; // Cinto verde com 3 posições
    Item* backpack[10]; // Mochila com pilha (array simples)
    int beltWeightLimit;

    SirGaldwin();
    bool addItemToBelt(Item* item);
    bool addItemToBackpack(Item* item);
    Item* getItemFromBackpack();
    Item* getItemFromBelt(int position);
    void takeDamage(int dmg);
    bool isDefeated();
};

// Classe principal que controla o fluxo do jogo
class Game {
public:
    SirGaldwin player;
    void startGame();
    void battle(Enemy& enemy);
    void exploreLevel(int level);
    void pickItem(Item* item);
};
#endif