#include "asteroid.h"
#include "player.h"
#include "game.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

std::vector<Asteroid> asteroids;


void drawAsteroidCircle(float centerX, float centerY, float radius, int numPoints, float bumpiness) {
    //function to draw circle, harder than expected
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

void updateAsteroids(int value) {
    //updaye asteroids here
    score += 1;
    for (auto& asteroid : asteroids) {
        asteroid.y -= asteroid.speed;
        if (asteroid.y < -1.0) {
            asteroid.y = 1.0;
            asteroid.x = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        }

        float asteroidRadius = 0.08;
        if (std::sqrt(std::pow(asteroid.x - playerX, 2) + std::pow(asteroid.y - playerY, 2)) < asteroidRadius + 0.03) {
            std::cout << "Game Over! Your score: " << score << std::endl;
            exit(0);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateAsteroids, 0);
}