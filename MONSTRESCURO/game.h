#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

class Game {
public:
    void showMainMenu();
    void handleMenuChoice(int choice);
    void startGame();
    void pauseGame();
    void resetGame();
    void showCredits();
    void showInstructions();  // Nova função para mostrar as instruções
    void useMonsterDetector(std::vector<int>& monsterHidingSpots);
    bool useShield();

private:
    int playerScore;
    bool hasMonsterDetector;
    bool hasShield;

    void hide(int choice);
    void pauseMenu();
    void handlePauseChoice(int choice);
};

#endif
