#include <GLUT/glut.h>
#include <cmath>

// Triangle parameters
float xPos = 0.0f;
float yPos = 0.0f;
float angle = 0.0f;
float moveSpeed = 0.025f;

bool keys[256]; // Array to track key states

void drawTriangle() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);

    glTranslatef(xPos, yPos, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around z-axis

    // Define vertices centered around (0, 0) for the triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.08f);  // Top point
    glVertex2f(-0.08f, -0.08f);  // Bottom-left point
    glVertex2f(0.08f, -0.08f);  // Bottom-right point
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Update at approximately 60 FPS

    float dx = cos(angle * 3.14159 / 180.0f) * moveSpeed;
    float dy = sin(angle * 3.14159 / 180.0f) * moveSpeed;

    if (keys['w']) {
        xPos += dx;
        yPos += dy;
    }
    if (keys['s']) {
        xPos -= dx;
        yPos -= dy;
    }
    if (keys['a']) {
        angle += 3.0f; // Rotate left
    }
    if (keys['d']) {
        angle -= 3.0f; // Rotate right
    }
}

void keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Moving and Rotating Triangle");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(drawTriangle);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
