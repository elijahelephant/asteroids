#pragma once
#ifndef GAME_H
#define GAME_H

extern int score;
extern int finalScore;

void drawScore();
void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void gameOverScreen(int score);

#endif