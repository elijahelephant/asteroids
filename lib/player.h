#pragma once
#ifndef PLAYER_H
#define PLAYER_H

extern float playerX;
extern float playerY;
extern float playerSpeed;

extern float playerDirectionX;
extern float playerDirectionY;

extern float bulletX;
extern float bulletY;
extern float bulletActive;
extern float bulletSpeed;

void drawPlayer();
void specialKeys(int key, int x, int y);
void updateBullet();
void drawBullet();
void fireBullet();

#endif