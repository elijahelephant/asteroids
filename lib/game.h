#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>

extern int score;
extern int finalScore;

void drawScore();
void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void gameOverScreen(int score);
void updateLeaderboard(int score);
void loadLeaderboard();
void saveLeaderboard();
void displayLeaderboard();
void drawText(float x, float y, const std::string& text);


struct PlayerScore {
    std::string playerName;
    int score;

    PlayerScore(): playerName(""), score(-1) {}
    PlayerScore(std::string name, int s) : playerName(name), score(s) {}
};

#endif