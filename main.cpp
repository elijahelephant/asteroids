#include <GL/glut.h>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Player ship properties
float playerX = 0.0;
float playerY = -0.4;
float playerSpeed = 0.05;

// Player ship direction
float playerDirectionX = 0.0;
float playerDirectionY = 1.0;

// Asteroid properties
struct Asteroid {
    float x;
    float y;
    float speed;
};

std::vector<Asteroid> asteroids;

// Score
int score = 0;

// Function declarations
void drawPlayer();
void drawAsteroids();
void drawAsteroidCircle(float centerX, float centerY, float radius, int numPoints, float bumpiness);
void updateAsteroids(int value);
void drawScore();
void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

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
    for (int i = 0; i < 5; ++i) {
        Asteroid asteroid;
        asteroid.x = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        asteroid.y = 1.0;
        asteroid.speed = static_cast<float>(rand()) / RAND_MAX * 0.02 + 0.01;
        asteroids.push_back(asteroid);
    }

    glutTimerFunc(0, updateAsteroids, 0);

    glutMainLoop();
    return 0;
}

void drawPlayer() {
    glColor3f(1.0, 1.0, 1.0);

    // Body
    glBegin(GL_POLYGON);
    glVertex2f(playerX, playerY + 0.04); // Top vertex
    glVertex2f(playerX - 0.02, playerY - 0.04); // Bottom left vertex
    glVertex2f(playerX + 0.02, playerY - 0.04); // Bottom right vertex
    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex2f(playerX - 0.01, playerY - 0.02); // Left wing vertex
    glVertex2f(playerX - 0.05, playerY - 0.06); // Left wing tip vertex
    glVertex2f(playerX - 0.01, playerY - 0.06); // Left wing bottom vertex
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(playerX + 0.01, playerY - 0.02); // Right wing vertex
    glVertex2f(playerX + 0.05, playerY - 0.06); // Right wing tip vertex
    glVertex2f(playerX + 0.01, playerY - 0.06); // Right wing bottom vertex
    glEnd();

    // Center bottom vertex for body
    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.02, playerY - 0.04); // top left vertex
    glVertex2f(playerX + 0.02, playerY - 0.04); // top right vertex
    glVertex2f(playerX + 0.02, playerY - 0.08); // bottom right vertex
    glVertex2f(playerX - 0.02, playerY - 0.08); // bottom left vertex
    glEnd();

    // Booster Rocket (Red)
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.005, playerY - 0.08); // Bottom left vertex
    glVertex2f(playerX + 0.005, playerY - 0.08); // Bottom right vertex
    glVertex2f(playerX + 0.005, playerY - 0.11); // Top right vertex
    glVertex2f(playerX - 0.005, playerY - 0.11); // Top left vertex
    glEnd();

    // Booster Rocket left(orange)
    glColor3f(1.0, 0.5, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.015, playerY - 0.08); // Bottom left vertex
    glVertex2f(playerX - 0.005, playerY - 0.08); // Bottom right vertex
    glVertex2f(playerX - 0.005, playerY - 0.1); // Top right vertex
    glVertex2f(playerX - 0.015, playerY - 0.1); // Top left vertex
    glEnd();
    // Booster Rocket right(orange)
    glColor3f(1.0, 0.5, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(playerX + 0.015, playerY - 0.08); // Bottom left vertex
    glVertex2f(playerX + 0.005, playerY - 0.08); // Bottom right vertex
    glVertex2f(playerX + 0.005, playerY - 0.1); // Top right vertex
    glVertex2f(playerX + 0.015, playerY - 0.1); // Top left vertex
    glEnd();

    // Booster Rocket detail(yellow)
    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(playerX + 0.0065, playerY - 0.08); // Bottom left vertex
    glVertex2f(playerX + 0.0035, playerY - 0.08); // Bottom right vertex
    glVertex2f(playerX + 0.0035, playerY - 0.1); // Top right vertex
    glVertex2f(playerX + 0.0065, playerY - 0.1); // Top left vertex
    glEnd();

    // Booster Rocket detail(yellow)
    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(playerX - 0.0065, playerY - 0.08); // Bottom left vertex
    glVertex2f(playerX - 0.0035, playerY - 0.08); // Bottom right vertex
    glVertex2f(playerX - 0.0035, playerY - 0.1); // Top right vertex
    glVertex2f(playerX - 0.0065, playerY - 0.1); // Top left vertex
    glEnd();

    // cockpit
    glColor3f(0.4, 0.8, .98);

    glBegin(GL_POLYGON);
    glVertex2f(playerX, playerY + 0.02); // Top vertex
    glVertex2f(playerX - 0.01, playerY - 0.03); // Bottom left vertex
    glVertex2f(playerX + 0.01, playerY - 0.03); // Bottom right vertex
    glEnd();

}



void drawAsteroids() {
    glColor3f(0.4, 0.4, 0.4);
    for (const auto& asteroid : asteroids) {
        glPushMatrix();
        glTranslatef(asteroid.x, asteroid.y, 0.0);
        drawAsteroidCircle(0.0, 0.0, 0.08, 60, 0.005);
        
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        for (int i = 0; i < 20; ++i) {
            float angle = static_cast<float>(i) / 20.0 * 2.0 * 3.141592; // Distribute dots evenly in a circle
            float radius = static_cast<float>(rand()) / RAND_MAX * 0.05; // Adjust the radius as needed
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
    score += 1;
    for (auto& asteroid : asteroids) {
        asteroid.y -= asteroid.speed;
        if (asteroid.y < -1.0) {
            asteroid.y = 1.0;
            asteroid.x = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        }

        // Check for collision with the player
        float asteroidRadius = 0.08; // Adjust the radius as needed
        if (std::sqrt(std::pow(asteroid.x - playerX, 2) + std::pow(asteroid.y - playerY, 2)) < asteroidRadius + 0.03) {
            std::cout << "Game Over! Your score: " << score << std::endl;
            exit(0);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateAsteroids, 0);
}


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
    gluOrtho2D(-1, 1, -1, 1);
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

void specialKeys(int key, int x, int y) {
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

void drawAsteroidCircle(float centerX, float centerY, float radius, int numPoints, float bumpiness) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numPoints; ++i) {
        float angle = 2.0 * 3.141592 * i / numPoints;
        float x = centerX + (radius + bumpiness * sin(5.0 * angle)) * cos(angle);
        float y = centerY + (radius + bumpiness * sin(5.0 * angle)) * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}