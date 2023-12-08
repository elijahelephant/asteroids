#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>

extern bool gameOver;
extern bool gameStart;

struct Asteroid {
    float x;
    float y;
    float speed;
    bool isActive;
};


extern std::vector<Asteroid> asteroids;

void drawAsteroids();
void updateAsteroids(int value);

#endif