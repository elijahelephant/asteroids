#include "player.h"
#include <GL/glut.h>

//initial positions
float playerX = 0.0;
float playerY = -0.4;
float playerSpeed = 0.05;

float playerDirectionX = 0.0;
float playerDirectionY = 1.0;

void drawPlayer() {
    //function to color pixels for the ship
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);
    glVertex2f(playerX, playerY + 0.04);
    glVertex2f(playerX - 0.02, playerY - 0.04);
    glVertex2f(playerX + 0.02, playerY - 0.04);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(playerX - 0.01, playerY - 0.02);
    glVertex2f(playerX - 0.05, playerY - 0.06);
    glVertex2f(playerX - 0.01, playerY - 0.06);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(playerX + 0.01, playerY - 0.02);
    glVertex2f(playerX + 0.05, playerY - 0.06);
    glVertex2f(playerX + 0.01, playerY - 0.06);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.02, playerY - 0.04);
    glVertex2f(playerX + 0.02, playerY - 0.04);
    glVertex2f(playerX + 0.02, playerY - 0.08);
    glVertex2f(playerX - 0.02, playerY - 0.08);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.005, playerY - 0.08);
    glVertex2f(playerX + 0.005, playerY - 0.08);
    glVertex2f(playerX + 0.005, playerY - 0.11);
    glVertex2f(playerX - 0.005, playerY - 0.11);
    glEnd();

    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.015, playerY - 0.08);
    glVertex2f(playerX - 0.005, playerY - 0.08);
    glVertex2f(playerX - 0.005, playerY - 0.1);
    glVertex2f(playerX - 0.015, playerY - 0.1);
    glEnd();

    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(playerX + 0.015, playerY - 0.08);
    glVertex2f(playerX + 0.005, playerY - 0.08);
    glVertex2f(playerX + 0.005, playerY - 0.1);
    glVertex2f(playerX + 0.015, playerY - 0.1);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(playerX + 0.0065, playerY - 0.08);
    glVertex2f(playerX + 0.0035, playerY - 0.08);
    glVertex2f(playerX + 0.0035, playerY - 0.1);
    glVertex2f(playerX + 0.0065, playerY - 0.1);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.0065, playerY - 0.08);
    glVertex2f(playerX - 0.0035, playerY - 0.08);
    glVertex2f(playerX - 0.0035, playerY - 0.1);
    glVertex2f(playerX - 0.0065, playerY - 0.1);
    glEnd();

    glColor3f(0.4, 0.8, .98);
    glBegin(GL_POLYGON);
    glVertex2f(playerX, playerY + 0.02);
    glVertex2f(playerX - 0.01, playerY - 0.03);
    glVertex2f(playerX + 0.01, playerY - 0.03);
    glEnd();
}

void specialKeys(int key, int x, int y) {
    //function to move the ship
    switch (key) {
    case GLUT_KEY_LEFT:
        playerX -= playerSpeed;
        if (playerX < -1.0) playerX = -1.0;
        break;
    case GLUT_KEY_RIGHT:
        playerX += playerSpeed;
        if (playerX > 1.0) playerX = 1.0;
        break;
    case GLUT_KEY_DOWN:
        playerY -= playerSpeed;
        if (playerY < -1.0) playerY = -1.0;
        break;
    case GLUT_KEY_UP:
        playerY += playerSpeed;
        if (playerY > 1.0) playerY = 1.0;
        break;
    }

    glutPostRedisplay();
}