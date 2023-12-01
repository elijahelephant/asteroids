#include "game.h"
#include "asteroid.h"
#include "player.h"
#include <GL/glut.h>
#include <iostream>
#include <string>

int score = 0;

void drawScore() {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-0.9, 0.9);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlayer();
    drawAsteroids();
    drawScore();

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 27: // Escape key
        std::cout << "Game Over! Your score: " << score << std::endl;
        exit(0);
        break;
    }
}