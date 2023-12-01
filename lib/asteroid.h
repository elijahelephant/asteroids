#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>

struct Asteroid {
    float x;
    float y;
    float speed;
};


extern std::vector<Asteroid> asteroids;

void drawAsteroids();
void updateAsteroids(int value);

#endif