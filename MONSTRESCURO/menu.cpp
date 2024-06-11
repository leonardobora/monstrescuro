#include <iostream>
#include "game.h"

void Game::showMainMenu() {
    int choice;
    do {
        std::cout << "1. Iniciar Jogo\n";
        std::cout << "2. Pausar Jogo\n";
        std::cout << "3. Reiniciar Jogo\n";
        std::cout << "4. Sair\n";
        std::cin >> choice;
        handleMenuChoice(choice);
    } while (choice != 4);
}

void Game::handleMenuChoice(int choice) {
    switch (choice) {
        case 1:
            startGame();
            break;
        case 2:
            pauseGame();
            break;
        case 3:
            resetGame();
            break;
        case 4:
            std::cout << "Saindo do jogo.\n";
            break;
        default:
            std::cout << "Opção inválida! Tente novamente.\n";
            break;
    }
}

