#pragma once
#ifndef PLAYER_H
#define PLAYER_H

extern float playerX;
extern float playerY;
extern float playerSpeed;

extern float playerDirectionX;
extern float playerDirectionY;

void drawPlayer();
void specialKeys(int key, int x, int y);

#endif