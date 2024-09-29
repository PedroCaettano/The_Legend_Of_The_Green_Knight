#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>

void printDramatic(const std::string& text) {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << text << "\n";
    std::cout << std::string(50, '=') << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void printLogo() {
    std::cout << R"(
   ________            __                              __   ____  ____   ________            ______                        __ __       _       __    __ 
 /_  __/ /_  ___     / /   ___  ____ ____  ____  ____/ /  / __ \/ __/  /_  __/ /_  ___     / ____/_______  ___  ____     / //_/____  (_)___ _/ /_  / /_
  / / / __ \/ _ \   / /   / _ \/ __ `/ _ \/ __ \/ __  /  / / / / /_     / / / __ \/ _ \   / / __/ ___/ _ \/ _ \/ __ \   / ,<  / __ \/ / __ `/ __ \/ __/
 / / / / / /  __/  / /___/  __/ /_/ /  __/ / / / /_/ /  / /_/ / __/    / / / / / /  __/  / /_/ / /  /  __/  __/ / / /  / /| |/ / / / / /_/ / / / / /_  
/_/ /_/ /_/\___/  /_____/\___/\__, /\___/_/ /_/\__,_/   \____/_/      /_/ /_/ /_/\___/   \____/_/   \___/\___/_/ /_/  /_/ |_/_/ /_/_/\__, /_/ /_/\__/  
                             /____/                                                                                                 /____/        
                             //                                                                                                 //             
    )" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void showCredits() {
    std::cout << "A Game by Pedro Caetano, Lorenzo Matheo & Gustavo Pereira" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}


class Item {
public:
    std::string name;
    int weight;
    int attackPower;
    int healingPower;

    Item(std::string n, int w, int ap = 0, int hp = 0)
        : name(n), weight(w), attackPower(ap), healingPower(hp) {}
};

class Enemy {
public:
    std::string name;
    int healthPoints;
    int attackPower;

    Enemy(std::string n, int hp, int ap)
        : name(n), healthPoints(hp), attackPower(ap) {}

    void takeDamage(int dmg) {
        healthPoints -= dmg;
        if (healthPoints < 0) healthPoints = 0;
    }

    bool isDefeated() {
        return healthPoints == 0;
    }

    void showHealth() {
        std::cout << name << " HP: [" << std::string(healthPoints / 10, '=') << std::string((100 - healthPoints) / 10, ' ') << "] (" << healthPoints << "/100)\n";
    }
};

class SirGaldwin {
public:
    int healthPoints;
    Item* belt[5];  
    Item* backpack[10];  
    int backpackSize;     
    int beltWeightLimit;
    const int backpackLimit = 10;  

    SirGaldwin() {
        healthPoints = 100;
        beltWeightLimit = 20;
        backpackSize = 0;
        for (int i = 0; i < 5; ++i) belt[i] = nullptr;
        for (int i = 0; i < 10; ++i) backpack[i] = nullptr;
    }

    bool addItemToBelt(Item* item) {
        int currentWeight = 0;
        for (int i = 0; i < 5; ++i) {
            if (belt[i] != nullptr) {
                currentWeight += belt[i]->weight;
            }
        }
        if (currentWeight + item->weight <= beltWeightLimit) {
            for (int i = 0; i < 5; ++i) {
                if (belt[i] == nullptr) {
                    belt[i] = item;
                    std::cout << "Item " << item->name << " adicionado ao cinto.\n";
                    return true;
                }
            }
        }
        std::cout << "Cinto cheio ou peso excessivo!\n";
        return false;
    }

    Item* getItemFromBelt(int position) {
        if (position >= 0 && position < 5 && belt[position] != nullptr) {
            Item* item = belt[position];
            belt[position] = nullptr;
            return item;
        }
        std::cout << "Cinto vazio nessa posição.\n";
        return nullptr;
    }

    bool addItemToBackpack(Item* item) {
        if (backpackSize < backpackLimit) {
            backpack[backpackSize] = item;
            backpackSize++;
            std::cout << "Item " << item->name << " adicionado à mochila.\n";
            return true;
        } else {
            std::cout << "Mochila cheia! Deseja remover um item? (1. Sim / 2. Não): ";
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                removeItemFromBackpack();
                return addItemToBackpack(item);
            }
        }
        return false;
    }

    void removeItemFromBackpack() {
        if (backpackSize > 0) {
            Item* removedItem = backpack[backpackSize - 1];  
            backpack[backpackSize - 1] = nullptr;
            backpackSize--;
            std::cout << "Item " << removedItem->name << " foi removido da mochila.\n";
            delete removedItem;  
        } else {
            std::cout << "A mochila já está vazia.\n";
        }
    }

    void takeDamage(int dmg) {
        healthPoints -= dmg;
        if (healthPoints < 0) healthPoints = 0;
    }

    void heal(int healAmount) {
        healthPoints += healAmount;
        if (healthPoints > 100) healthPoints = 100;
        std::cout << "Sir Galdwin recuperou " << healAmount << " pontos de vida!\n";
    }

    bool isDefeated() {
        return healthPoints <= 0;
    }

    void showHealth() {
        std::cout << "Sir Galdwin HP: [" << std::string(healthPoints / 10, '=') << std::string((100 - healthPoints) / 10, ' ') << "] (" << healthPoints << "/100)\n";
    }
};

class Game {
public:
    SirGaldwin player;

    void startGame() {
        printLogo();  
        showCredits();  
        printDramatic("Bem-vindo à jornada de Sir Galdwin!");

printDramatic("No coracao de Camelot, um reino de florestas densas e castelos ancestrais, onde o inverno traz consigo a promessa de neve eterna, os ventos carregam sussurros de antigas lendas. Entre essas lendas, uma história temida por todos: a do Cavaleiro Verde – um ser imponente, envolto em misterios, cujo corpo resplandece com a luz esmeralda de um poder desconhecido. Ele e o guardiao de um segredo antigo, um desafio que testa a honra e a coragem de qualquer cavaleiro que cruze seu caminho.");
printDramatic("Voce assume o papel de Sir Galdwin, um jovem cavaleiro de linhagem nobre, mas atormentado por duvidas e pressoes do legado que carrega. Embora Galdwin tenha treinamento em armas e habilidades taticas, seu verdadeiro desafio e interno – a luta contra suas proprias insegurancas.");
printDramatic("A vida no castelo e cheia de expectativas, e o peso das tradicoes familiares recai sobre seus ombros. Galdwin é conhecido por seu coracao bondoso, mas tamem por sua tendencia a evitar confrontos, preferindo resolver disputas com diplomacia.");
printDramatic(" A história começa na Grande Sala do Castelo de Ardenfall, onde a corte do rei Arthur se reúne para celebrar o solstício de inverno. O salao está iluminado por chamas cintilantes, e o som das risadas ecoa pelas paredes de pedra. Mas, quando as portas se abrem com um estrondo, o clima festivo se transforma em silencio atordoado");
printDramatic("Um cavaleiro imponente, coberto da cabeça aos pes em uma armadura verde brilhante, entra no salao. Ele é o Cavaleiro Verde, sua presenca e ao mesmo tempo majestosa e aterrorizante.");
printDramatic("O Cavaleiro Verde anuncia um desafio: ele oferece sua propria cabeça como um prêmio para qualquer cavaleiro que tiver coragem de golpealo, com a condicão de que, um ano depois, o desafiador deve viajar até a Capela Verde e permitir que o Cavaleiro Verde retorne o golpe.");
printDramatic(" Verde retorne o golpe. E um teste de coragem, honra e compromisso – uma prova mortal....");
printDramatic("Enquanto os nobres recuam, temerosos de aceitar o desafio, Sir Galdwin, impulsionado por uma mistura de honra e a necessidade de provar seu valor, levanta-se para enfrentar o Cavaleiro Verde");
printDramatic("Com um golpe preciso, Galdwin decapita o cavaleiro, apenas para ver, com horror, a cabeça decapitada ser recolocada magicamente sobre os ombros. O Cavaleiro Verde, agora sorrindo enigmaticamente, lembra Galdwin de seu juramento e desaparece na noite, deixando Galdwin e todos os presentes atonitos");
printDramatic("Com o peso de seu juramento, Galdwin é forçado a embarcar em uma jornada solitaria até a mitica Capela Verde, onde enfrentara nao apenas o Cavaleiro Verde, mas tambem seus proprios medos.");
printDramatic("Sua jornada o levara por florestas sombrias, ruinas esquecidas e territorios desconhecidos, onde a linha entre o mundo real e o sobrenatural se desfaz. No caminho, Galdwin encontrara aliados inesperados, resolvera enigmas antigos, e enfrentara criaturas e desafios que testarao sua mente, corpo e alma.");
printDramatic("A escuridão que permeia as terras de Camelot esconde segredos que Galdwin deve desvendar para ter uma chance de sobreviver ao encontro final com o Cavaleiro Verde.");
printDramatic("Mas à medida que a jornada avança, Galdwin descobrira que a maior batalha que ele enfrentara sera contra seu pr0prio destino, e que o verdadeiro teste de coragem talvez nao seja empunhar a espada, mas, sim, manter-se fiel ao. que acredita até o fim.");
printDramatic("Para mais informacoes consulte o texto complementar da historia do jogo.");
        exploreLevels();
    }

    void mostrarBioma(int level) {
        switch (level) {
            case 1: printDramatic("Nivel 1: Ao ser chamado para a jornada, Sir Galdwin, cavaleiro destemido do reino de Camelot, prepara-se para uma jornada que mudara seu destino para sempre. Com sua armadura reluzente e uma espada que brilha como o sol, ele se despede de seus entes queridos seus amigos leais, sua família, e especialmente de Fabrina Caspian, cujo sorriso e o farol em sua jornada. Com um coracao pesado, Galdwin adentra a floresta ancestral, onde as arvores sussurram segredos e as sombras dançam entre os troncos. Mas nao passa muito tempo ate que um grupo de ladroes, astutos como serpentes, emerge das sombras, determinados a roubar o que e seu. Prepare-se! A batalha comeca! LUTE CONTRA ESSES LADROES E CONTINUE SUA CAMINHO HEROICO."); break;
            case 2: printDramatic("Nivel 2: A escuridao se espalha como um manto pesado, engolindo a floresta enquanto Sir Galdwin avança em direcao ao seu destino. Mas, nas sombras, uma jovem assustada aparece, seu rosto marcado pelo medo e a inocencia perdida. Ela se chama Willow, uma garota cujo lar e atormentado por espectros e sombras malignas que a assombram. Com o coracao decidido, Galdwin promete protege-la. Juntos, eles se lançam nas profundezas do sobrenatural, onde ele enfrentara criaturas da noite, purificando o lar da jovem e banindo as trevas que ameacam devora-la."); break;
            case 3: printDramatic("Nivel 3: A medida que avanca em sua jornada, Galdwin encontra um espelho que reflete nao apenas sua imagem, mas a essencia de seus medos mais profundos. Uma versao sombria de si mesmo emerge, armada com as facetas mais traicoeiras de sua propria alma, determinada a acabar com sua vida. Este nao é apenas um inimigo; é um teste de sua propria coragem e carater. Galdwin deve confrontar este lado obscuro, lutando com todas as forças para dominar sua propria escuridao e continuar sua busca pela honra. "); break;
            case 4: printDramatic("Nivel 4: Em sua jornada, Galdwin chega a um vilarejo à beira da desolaçao, onde os habitantes vivem sob o medo de um dragao imponente que voa alto nos ceus, espoliando suas posses e espalhando terror. Uma pequena garota, com olhos de desespero, se aproxima, implorando por ajuda. Com o coracao fervendo de compaixao e bravura, Galdwin aceita o desafio de enfrentar a besta alada, decidindo que o brilho da justica deve prevalecer sobre o medo. Prepare-se para uma batalha epica, onde a coragem encontrara a ferocidade da fera."); break;
            case 5: printDramatic("Nivel 5: Apos derrotar o dragao, Galdwin ascende uma montanha ingreme, onde as brisas gélidas sussurram segredos de antigos poderes. La, ele encontra o Mago Merlin, mas este nao e o sabio conselheiro que conhecia. Possuido por forças sombrias, o mago agora busca sua morte. A batalha que se segue nao é apenas um teste de forca, mas um confronto entre luz e escuridao, magia e aco. Enfrente Merlin em uma luta que decidira o destino de sua jornada."); break;
            case 6: printDramatic("Nivel 6: Ao atravessar o vale onde moinhos de vento colossais giram sob o ceu tempestuoso, Sir Galdwin e desafiado por um ogro aterrador. Este gigante, de musculos como aço e olhos que ardem em furia, anseia pela destruicao. Lutando contra sua natureza animalesca, ele esta determinado a eliminar qualquer um que ouse cruzar seu caminho. Com bravura inabalavel, Galdwin deve derrotar esta criatura brutal para continuar sua jornada, provando que mesmo os maiores desafios podem ser superados pela forca de um coracao valente."); break;
            case 7: printDramatic("Nivel 7: Após a vitória sobre o ogro, Galdwin adentra o reino do Rei Purpura e da Rainha Ametista, onde a traiçao esta em cada esquina. Descobrindo que o casal real trama sua morte para garantir que ele nao se torne uma ameaça a seus planos, Galdwin se ve obrigado a lutar contra essas figuras de poder. Prepare-se para um embate que nao apenas testara suas habilidades de combate, mas tambem revelara os lacos de lealdade e traicao que ligam os destinos de todos no reino."); break;
            case 8: printDramatic("Nivel 8: Enquanto se aproxima da Capela Verde, um mensageiro misterioso aparece, carregando a aura do Cavaleiro Verde. Ele apresenta um desafio: um combate que determinara se Galdwin e digno de enfrentar o seu mestre. Com a espada em punho e a determinacao em seu coracao, Galdwin prepara-se para provar suas habilidades e mostrar que a luz da esperanca ainda brilha em meio a escuridao."); break;
            case 9: printDramatic("Nivel 9: A Capela do Cavaleiro Verde se ergue diante de Galdwin como um monumento ao destino e ao desafio final. Ele esta prestes a enfrentar o maior adversario de sua vida, um ser cuja lenda ecoa atraves das eras. Galdwin deve reunir toda a sua coragem e força, pois este confronto decidirá não apenas seu destino, mas o futuro do reino. O eco do aço e o rugido da batalha estão prestes a ser ouvidos! TOME CUIDADO! Este e o clímax de sua jornada, onde a bravura sera testada como nunca antes. Que sua coragem e determinação sejam suas melhores armas na batalha que se aproxima!"); break;
        }
    }

    void exploreLevels() {
        for (int level = 1; level <= 9; ++level) {
            mostrarBioma(level);

            bool venceuInimigo = false;
            while (!venceuInimigo) {  
                std::cout << "\nVoce chegou ao nivel " << level << ". O que deseja fazer?\n";
                std::cout << "1. Enfrente seu inimigo e decida sua sorte\n";
                std::cout << "2. Explorar a fase e encontrar itens raros\n";
                std::cout << "3. Veja os Status do Sir Galdwin\n";
                std::cout << "Escolha uma opção (1-3): ";
                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        venceuInimigo = fightEnemy(level);
                        if (player.isDefeated()) {
                            printDramatic("Sir Galdwin falhou em sua jornada e foi derrotado. Fim do jogo, voce morreu.");
                            endGame(false);
                            return;
                        }
                        break;
                    case 2:
                        exploreArea();
                        break;
                    case 3:
                        showStatus();
                        break;
                    default:
                        std::cout << "Opçao invalida. Tente novamente.\n";
                }
            }
        }
        endGame(true);  
    }

    bool fightEnemy(int level) {
        Enemy enemy("Adversario Desequilibrado Nivel " + std::to_string(level), 50 + (level * 10), 10);
        printDramatic("Um " + enemy.name + " assustador apareceu! QUE COMECE A LUTA!");

        while (!player.isDefeated() && !enemy.isDefeated()) {
            player.showHealth();
            enemy.showHealth();
            std::cout << "Escolha seu ataque: A (Espada Romani), B (Machado do Cavaleiro Verde), C (Ataque corpo a corpo), D (Itens), E (Bloquear com escudo): ";
            char playerAction;
            std::cin >> playerAction;

            char enemyAttack = "Ataque ferroz. "[std::rand() % 3];  
            std::cout << "Inimigo escolheu: Ataque ferroz. " << enemyAttack << "\n";

            if (playerAction == 'D') {
                usePotion();
                continue;  
            }

            if (playerAction == 'E') {
                blockAttack(enemy.attackPower);
            } else {
                int playerDamage = 0;
                if (playerAction == 'A') playerDamage = 15;  
                else if (playerAction == 'B') playerDamage = 20;  
                else if (playerAction == 'C') playerDamage = 5;  

                enemy.takeDamage(playerDamage);
                std::cout << "Voce causou " << playerDamage << " de dano ao inimigo!\n";
                if (enemy.isDefeated()) {
                    printDramatic("Inimigo derrotado!");
                    return true;
                }

                player.takeDamage(enemy.attackPower);
                std::cout << "Voce recebeu " << enemy.attackPower << " de dano!\n";
            }
        }
        return false;
    }

    void blockAttack(int& enemyAttackPower) {
        int damageBlocked = enemyAttackPower / 2;
        player.takeDamage(damageBlocked);
        std::cout << "Voce bloqueou parte do ataque e recebeu apenas " << damageBlocked << " de dano!\n";
    }

    void exploreArea() {
        std::cout << "Voce encontrou um item! Deseja pega lo? (S/N): ";
        char choice;
        std::cin >> choice;

        if (choice == 'S' || choice == 's') {
            Item* newItem = new Item("Espada Magica", 3, 15);  
            if (!player.addItemToBelt(newItem)) {
                if (!player.addItemToBackpack(newItem)) {
                    std::cout << "Voce nao tem espaço para pegar o item.\n";
                    delete newItem;  
                }
            }
        }

        if (std::rand() % 2 == 0) {  
            int potionType = std::rand() % 3;  
            Item* potion;
            if (potionType == 0) potion = new Item("Poçao de Vida Pequena", 1, 0, 20);
            else if (potionType == 1) potion = new Item("Poçao de Vida Media", 1, 0, 50);
            else potion = new Item("Poçao de Vida Completa", 1, 0, 100);

            if (!player.addItemToBackpack(potion)) {
                std::cout << "Voce nao tem espaço para pegar a poçao.\n";
                delete potion;
            } else {
                std::cout << "Voce encontrou uma " << potion->name << "!\n";
            }
        }
    }

    void usePotion() {
        if (player.backpackSize == 0) {
            std::cout << "Você nao tem poçoes!\n";
            return;
        }

        std::cout << "Escolha uma poçao para usar:\n";
        for (int i = 0; i < player.backpackSize; ++i) {
            if (player.backpack[i] != nullptr) {
                std::cout << i + 1 << ". " << player.backpack[i]->name << " (Cura: " << player.backpack[i]->healingPower << ")\n";
            }
        }

        int choice;
        std::cin >> choice;
        if (choice > 0 && choice <= player.backpackSize) {
            Item* potion = player.backpack[choice - 1];
            player.heal(potion->healingPower);
            delete potion;
            player.backpack[choice - 1] = nullptr;
        } else {
            std::cout << "Escolha invalida.\n";
        }
    }

    void showStatus() {
        player.showHealth();
        std::cout << "Itens no cinto:\n";
        for (int i = 0; i < 5; ++i) {
            if (player.belt[i] != nullptr) {
                std::cout << " - " << player.belt[i]->name << "\n";
            }
        }
        std::cout << "Itens na mochila: " << player.backpackSize << "\n";
    }

    void endGame(bool won) {
        if (won) {
            printDramatic("Parabens! Você completou a jornada.");
        } else {
            printDramatic("Voce falhou. Tente novamente.");
        }
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));  
    Game game;
    game.startGame();
    return 0;

};
