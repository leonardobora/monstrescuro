#include <iostream>
#include <limits>
#include <thread>   // Para utilizar std::this_thread::sleep_for
#include <chrono>   // Para utilizar std::chrono::milliseconds
#include <cstdlib>  // Para utilizar exit()
#include <vector>
#include "game.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

void Game::showMainMenu() {
    int choice;
    do {
        std::cout << " ___ ___   ___   ____    _____ ______  ____     ___   _____    __  __ __  ____    ___      \n";
        std::cout << "|   |   | /   \\ |    \\  / ___/|      ||    \\   /  _] / ___/   /  ]|  |  ||    \\  /   \\     \n";
        std::cout << "| _   _ ||     ||  _  |(   \\_ |      ||  D  ) /  [_ (   \\_   /  / |  |  ||  D  )|     |    \n";
        std::cout << "|  \\_/  ||  O  ||  |  | \\__  ||_|  |_||    / |    _] \\__  | /  /  |  |  ||    / |  O  |    \n";
        std::cout << "|   |   ||     ||  |  | /  \\ |  |  |  |    \\ |   [_  /  \\ |/   \\_ |  :  ||    \\ |     |    \n";
        std::cout << "|   |   ||     ||  |  | \\    |  |  |  |  .  \\|     | \\    |\\     ||     ||  .  \\|     |    \n";
        std::cout << "|___|___| \\___/ |__|__|  \\___|  |__|  |__|\\_||_____|  \\___| \\____| \\__,_||__|\\_| \\___/     \n";
        std::cout << "\n";
        std::cout << "1. Iniciar Jogo\n";
        std::cout << "2. Instru��es\n";  // Nova op��o "Instru��es"
        std::cout << "3. Exibir Cr�ditos\n";
        std::cout << "4. Sair\n";
        std::cout << "> ";
        while (!(std::cin >> choice) || choice < 1 || choice > 4) {  // Ajustado para incluir a nova op��o
            std::cin.clear(); // Limpa o erro de entrada
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora entrada inv�lida
            std::cout << "Entrada inv�lida! Por favor, escolha uma op��o entre 1 e 4:\n> ";
        }
        handleMenuChoice(choice);
    } while (choice != 4);
}

void Game::handleMenuChoice(int choice) {
    switch (choice) {
        case 1:
            std::cout << "\nIniciando o jogo...";
            std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // Simula um tempo de carregamento de 1.5 segundos
            std::cout << " Pronto!\n\n";
            startGame();
            break;
        case 2:
            showInstructions();  // Chama a nova fun��o para mostrar as instru��es
            break;
        case 3:
            showCredits();
            break;
        case 4:
            std::cout << "Saindo do jogo.\n";
            break;
        default:
            std::cout << "Op��o inv�lida! Tente novamente.\n";
            break;
    }
}

void Game::showInstructions() {
    std::cout << "\nINSTRU��ES DO JOGO:\n";
    std::cout << "1. O objetivo do jogo � se esconder dos monstros. Cada rodada tem um n�mero crescente de esconderijos e monstros.\n";
    std::cout << "2. Em cada rodada, escolha um esconderijo. Se um monstro estiver l�, voc� ter� uma segunda chance de escapar.\n";
    std::cout << "3. Voc� pode encontrar itens durante o jogo:\n";
    std::cout << "   - Detector de Monstros: Revela metade dos esconderijos dos monstros.\n";
    std::cout << "   - Escudo: Protege voc� de ser capturado uma vez.\n";
    std::cout << "4. Pontua��o:\n";
    std::cout << "   - +20 pontos por escapar na primeira tentativa.\n";
    std::cout << "   - +10 pontos por escapar na segunda tentativa.\n";
    std::cout << "DICAS:\n";
    std::cout << "- Use o Detector de Monstros com sabedoria para reduzir os poss�veis esconderijos dos monstros.\n";
    std::cout << "- Sempre escolha esconderijos diferentes na segunda tentativa.\n";
    std::cout << "Pressione qualquer tecla para voltar ao menu principal...\n";
    std::cin.ignore();
    std::cin.get();
}

void Game::pauseMenu() {
    int choice;
    do {
        std::cout << "\nJogo pausado. Escolha uma op��o:\n";
        std::cout << "1. Reiniciar Jogo\n";
        std::cout << "2. Sair\n";
        std::cout << "> ";
        while (!(std::cin >> choice) || choice < 1 || choice > 2) {
            std::cin.clear(); // Limpa o erro de entrada
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora entrada inv�lida
            std::cout << "Entrada inv�lida! Por favor, escolha uma op��o entre 1 e 2:\n> ";
        }
        handlePauseChoice(choice);
    } while (choice != 2);
}

void Game::handlePauseChoice(int choice) {
    switch (choice) {
        case 1:
            std::cout << "\nReiniciando o jogo...";
            std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // Simula um tempo de carregamento de 1.5 segundos
            std::cout << " Pronto!\n\n";
            resetGame();
            break;
        case 2:
            std::cout << "Saindo do jogo.\n";
            exit(0);
            break;
        default:
            std::cout << "Op��o inv�lida! Tente novamente.\n";
            break;
    }
}

void Game::pauseGame() {
    std::cout << "\nJogo pausado...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Simula um tempo de pausa de 2 segundos
    std::cout << "Continuando o jogo!\n";
}

void Game::resetGame() {
    std::cout << "Jogo reiniciado.\n";
    startGame(); // Chama startGame() novamente ap�s o reset
}

void Game::showCredits() {
    std::cout << "\n";
    std::cout << "MONSTRESCURO\n";
    std::cout << "Criado por: Bora, Luan, e Freitas\n";
    std::cout << "Programa��o Avan�ada - APS 2 - Prof. Fabio Bettio\n";
    std::cout << "Reposit�rio: https://github.com/teu-repositorio/peek-a-monster\n";
    std::cout << "\n";
    std::cout << "Pressione qualquer tecla para voltar ao menu principal...\n";
    std::cin.ignore();
    std::cin.get();
}
