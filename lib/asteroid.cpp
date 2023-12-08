#include "asteroid.h"
#include "player.h"
#include "game.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

std::vector<Asteroid> asteroids;
bool gameOver = false;
bool gameStart = false;


void drawAsteroidCircle(float centerX, float centerY, float radius, int numPoints, float bumpiness) {
    //simple function to draw circle
    glBegin(GL_POLYGON);
    for (int i = 0; i < numPoints; ++i) {
        float angle = 2.0 * 3.141592 * i / numPoints;
        float x = centerX + (radius + bumpiness * sin(5.0 * angle)) * cos(angle);
        float y = centerY + (radius + bumpiness * sin(5.0 * angle)) * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawAsteroids() {
    //create asteroids here
    glColor3f(0.4, 0.4, 0.4);
    for (const auto& asteroid : asteroids) {
        if (asteroid.isActive == true) {
            glPushMatrix();
            glTranslatef(asteroid.x, asteroid.y, 0.0);
            drawAsteroidCircle(0.0, 0.0, 0.08, 60, 0.005);

            glPointSize(2.0);
            glBegin(GL_POINTS);
            glColor3f(1.0, 1.0, 1.0);
            for (int i = 0; i < 20; ++i) {
                float angle = static_cast<float>(i) / 20.0 * 2.0 * 3.141592;
                float radius = static_cast<float>(rand()) / RAND_MAX * 0.05;
                float dotX = 1.1 * radius * std::cos(angle);
                float dotY = 1.1 * radius * std::sin(angle);
                glVertex2f(dotX, dotY);
            }
            glColor3f(0.4, 0.4, 0.4);
            glEnd();

            glPopMatrix();
        }
    }
}

void updateAsteroids(int value) {
    //keep track of game state, collision and asteroid destruction
    if (gameStart && !gameOver) {
        //game is active
        score += 1;
        if(score % 250 == 0){
            Asteroid asteroid;
            asteroid.x = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            asteroid.y = 1.0;
            asteroid.speed = static_cast<float>(rand()) / RAND_MAX * 0.02 + 0.01;
            asteroid.isActive = true;
            asteroids.push_back(asteroid);
        }
        for (auto& asteroid : asteroids) {
            asteroid.y -= asteroid.speed;
            if (asteroid.y < -1.0) {
                asteroid.y = 1.0;
                asteroid.x = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
                asteroid.isActive = true;
            }

            float asteroidRadius = 0.08;
            if (bulletActive && std::sqrt(std::pow(bulletX - asteroid.x, 2) + std::pow(bulletY - asteroid.y, 2)) < asteroidRadius) {
                asteroid.isActive = false;
                bulletActive = false;
            }
            if ((std::sqrt(std::pow(asteroid.x - playerX, 2) + std::pow(asteroid.y - playerY, 2)) < asteroidRadius + 0.03) && asteroid.isActive == true) {
                //collision, game over
                gameOver = true;
                finalScore = score;
            }
        }
        updateBullet();
        glutPostRedisplay();
        glutTimerFunc(16, updateAsteroids, 0);
    } else {
        glutPostRedisplay(); 
        glutTimerFunc(100, updateAsteroids, 0); // Call updateAsteroids after a delay
    }
}
