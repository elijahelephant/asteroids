#include "game.h"
#include "asteroid.h"
#include "player.h"
#include <GLUT/glut.h>
#include <iostream>
#include <string>
#include <cmath>

int score = 0;
int finalScore = 0;

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

    if (!gameStart) {
        // Display "Press enter to start" message until the game starts
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-.4, 0.1); // Position for start message
        std::string title = "Cosmic Blasters: Asteroid Assault";
        for (char c : title) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-.25, -0.1); // Position for start message
        std::string startText = "Press Enter to Start";
        for (char c : startText) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
    } else if (gameOver) {
        // Game over message and quit instruction
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.5, 0.1); // Position for game over text
        std::string gameOverText = "Game Over! Your score was: " + std::to_string(finalScore);
        for (char c : gameOverText) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }

        glRasterPos2f(-0.5, 0.0); // Position for "Press esc to quit game" text
        std::string quitText = "Press esc to quit game";
        for (char c : quitText) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
    } else {
        // Your regular game drawing logic when not game over
        drawPlayer();
        drawAsteroids();
        drawScore();
        drawBullet();
    }

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
    case 27:
        exit(0);
        break;
    case ' ':
        fireBullet();
        break;
    case 13:
        gameStart = true;
        glutPostOverlayRedisplay();
    }

}

void gameOverScreen(int score) {
    return;
}