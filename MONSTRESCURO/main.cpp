#include <iostream>
#include <locale>
#include "game.h"

int main() {
    // Configura o locale para suportar caracteres especiais
    std::setlocale(LC_ALL, "Portuguese");

    Game game;
    game.showMainMenu();
    return 0; 
}

