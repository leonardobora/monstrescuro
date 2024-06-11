#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
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

void Game::startGame() {
    int rounds = 0;
    playerScore = 0;
    hasMonsterDetector = false;
    hasShield = false;
    bool gameOver = false;
    srand(time(0));

    while (!gameOver) {
        rounds++;
        int numHidingSpots = 3 + rounds;
        int numMonsters = 0 + rounds;
        int playerChoice;
        std::vector<int> monsterHidingSpots;

        // Determinar os esconderijos dos monstros
        for (int i = 0; i < numMonsters; ++i) {
            int monsterChoice = rand() % numHidingSpots + 1;
            monsterHidingSpots.push_back(monsterChoice);
        }

        // Chance de encontrar itens
        if (rand() % 5 == 0) {  // 20% de chance de encontrar um item
            if (!hasMonsterDetector && rand() % 2 == 0) {
                hasMonsterDetector = true;
                std::cout << YELLOW << "\nVocê encontrou um Detector de Monstros!\n" << RESET;
            } else if (!hasShield) {
                hasShield = true;
                std::cout << YELLOW << "\nVocê encontrou um Escudo!\n" << RESET;
            }
        }

        // Usar Detector de Monstros
        if (hasMonsterDetector) {
            char useDetector;
            std::cout << YELLOW << "\nVocê quer usar o Detector de Monstros? (s/n):\n> " << RESET;
            std::cin >> useDetector;
            if (useDetector == 's' || useDetector == 'S') {
                useMonsterDetector(monsterHidingSpots);
                hasMonsterDetector = false;
                numMonsters = monsterHidingSpots.size(); // Atualiza o número de monstros
            }
        }

        // Desenhar os esconderijos
        std::cout << "\nRodada " << rounds << "\n";
        std::cout << "Escolha um lugar para se esconder (1-" << numHidingSpots << ", ou 0 para pausar):\n";
        for (int i = 1; i <= numHidingSpots; ++i) {
            std::cout << "[" << i << "]";
            if (i % 10 == 0) {  // Quebra de linha para cada 10 esconderijos
                std::cout << "\n";
            }
        }
        std::cout << "\n> ";

        // Validação de entrada
        while (!(std::cin >> playerChoice) || playerChoice < 0 || playerChoice > numHidingSpots) {
            std::cin.clear(); // Limpa o erro de entrada
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora entrada inválida
            std::cout << "Entrada inválida! Por favor, escolha um lugar entre 0 e " << numHidingSpots << ":\n> ";
        }

        if (playerChoice == 0) {
            pauseGame();
            continue;
        }

        bool found = false;
        for (int i = 0; i < numMonsters; ++i) {
            if (playerChoice == monsterHidingSpots[i]) {
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << RED << "\n*** Você foi encontrado por um monstro! ***\n" << RESET;
            
            
            
            if (hasShield && useShield()) {
                std::cout << GREEN << "\nVocê usou o escudo e se salvou!\n" << RESET;
                hasShield = false;
            } else {
                std::cout << "Tente escapar novamente! Escolha outro lugar para se esconder (1-" << numHidingSpots << "):\n> ";

                // Segunda tentativa
                while (!(std::cin >> playerChoice) || playerChoice < 1 || playerChoice > numHidingSpots) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entrada inválida! Por favor, escolha um lugar entre 1 e " << numHidingSpots << ":\n> ";
                }

                // Menor chance de escapar na segunda tentativa
                found = false;
                for (int i = 0; i < numMonsters * 2; ++i) {  // Dobrar o número de monstros na segunda tentativa
                    int monsterChoice = rand() % numHidingSpots + 1;
                    if (playerChoice == monsterChoice) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    std::cout << RED << "\n*** Você foi capturado pelo monstro! ***\n" << RESET;

                    int choice;
                    std::cout << "Game Over! Sua pontuação final é: " << playerScore << "\n";
                    std::cout << "\nEscolha uma opção:\n";
                    std::cout << "1. Voltar ao menu principal\n";
                    std::cout << "2. Sair\n";
                    std::cout << "> ";
                    while (!(std::cin >> choice) || choice < 1 || choice > 2) {
                        std::cin.clear(); // Limpa o erro de entrada
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora entrada inválida
                        std::cout << "Entrada inválida! Por favor, escolha uma opção entre 1 e 2:\n> ";
                    }

                    if (choice == 1) {
                        showMainMenu();
                    } else {
                        std::cout << "Saindo do jogo.\n";
                        exit(0);
                    }
                    gameOver = true;
                } else {
                    std::cout << GREEN << "\nVocê conseguiu escapar na segunda tentativa!\n" << RESET;
                    playerScore += 10;  // Pontuação bônus por escapar na segunda tentativa
                }
            }
        } else {
            std::cout << GREEN << "\nVocê se escondeu com sucesso!\n" << RESET;
            playerScore += 20;  // Pontuação padrão por escapar na primeira tentativa
        }

        std::cout << "Os monstros estavam escondidos em: ";
        for (int i = 0; i < numMonsters; ++i) {
            std::cout << monsterHidingSpots[i] << " ";
        }
        std::cout << "\nSua pontuação: " << playerScore << "\n";
    }

    std::cout << "Game Over! Sua pontuação final é: " << playerScore << "\n";
}

void Game::useMonsterDetector(std::vector<int>& monsterHidingSpots) {
    int numMonsters = monsterHidingSpots.size();
    int numToRemove = numMonsters / 2;
    
    std::cout << CYAN << "\nUsando o Detector de Monstros...\n" << RESET;
    
    for (int i = 0; i < numToRemove; ++i) {
        int indexToRemove = rand() % monsterHidingSpots.size();
        monsterHidingSpots.erase(monsterHidingSpots.begin() + indexToRemove);
    }

    std::cout << "Os monstros restantes estão em: ";
    for (int spot : monsterHidingSpots) {
        std::cout << spot << " ";
    }
    std::cout << "\n";
}

bool Game::useShield() {
    std::cout << YELLOW << "\nUsando o Escudo...\n" << RESET;
    return true;
}
