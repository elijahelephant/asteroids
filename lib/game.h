#pragma once
#ifndef GAME_H
#define GAME_H

extern int score;

void drawScore();
void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);

#endif