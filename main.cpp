#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include "lib/asteroid.h"
#include "lib/game.h"
#include "lib/player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Asteroids Game");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    // Initialize asteroids
    srand(time(nullptr));
    for (int i = 0; i < 10; ++i) {
        Asteroid asteroid;
        asteroid.x = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        asteroid.y = 1.0;
        asteroid.speed = static_cast<float>(rand()) / RAND_MAX * 0.02 + 0.01;
        asteroid.isActive = true;
        asteroids.push_back(asteroid);
    }

    glutTimerFunc(0, updateAsteroids, 0);

    glutMainLoop();
    return 0;
}