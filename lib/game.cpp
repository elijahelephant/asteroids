#include "game.h"
#include "asteroid.h"
#include "player.h"
#include <GLUT/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

int score = 0;
int finalScore = 0;

std::vector<PlayerScore> leaderboard;
const std::string leaderboardFilePath = "lib/highscore.txt";

std::string playerNameInput = "";
bool enteringName = false;

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
        glColor3f(1.0, 1.0, 1.0);
        drawText(-0.6, -0.15, "Press 'Enter' then enter your name using the keyboard.");
        drawText(-.10, -0.2775, playerNameInput);
        drawText(-0.4, -0.40, "Press 'Enter' to start the game");

    } else if (gameOver) {

        loadLeaderboard();
        updateLeaderboard(finalScore);
        saveLeaderboard();

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
        displayLeaderboard();

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
    case 13: // Enter key
        if (!enteringName) {
            // Switch to entering name mode
            enteringName = true;
        } else {
            // Submit the name and start the game
            enteringName = false;
            gameStart = true;
        }
        break;
    case 8: // Backspace key
        if (enteringName && !playerNameInput.empty()) {
            playerNameInput.pop_back();
            glutPostOverlayRedisplay();
        }
        break;
    default:
        if (enteringName && isalpha(key) && playerNameInput.length() < 20) {
            playerNameInput += key;
            glutPostOverlayRedisplay();
        }
    }
}

void gameOverScreen(int score) {
    return;
}

void updateLeaderboard(int score) {
    // Only update leaderboard if a name has been entered
    if (!playerNameInput.empty()) {
        // Check if the player's name is already in the leaderboard
        auto it = std::find_if(leaderboard.begin(), leaderboard.end(),
                               [&](const PlayerScore& entry) {
                                   return entry.playerName == playerNameInput;
                               });

        if (it != leaderboard.end()) {
            // Update the existing entry if the new score is higher
            if (score > it->score) {
                it->score = score;
                // Resort the leaderboard after updating the score
                std::sort(leaderboard.begin(), leaderboard.end(),
                          [](const PlayerScore& a, const PlayerScore& b) {
                              return a.score > b.score;
                          });
            }
        } else {
            // Add a new entry if the player's name is not in the leaderboard
            leaderboard.emplace_back(playerNameInput, score);

            // Resort the leaderboard after adding the new entry
            std::sort(leaderboard.begin(), leaderboard.end(),
                      [](const PlayerScore& a, const PlayerScore& b) {
                          return a.score > b.score;
                      });

            // Ensure the leaderboard has at most 5 entries
            if (leaderboard.size() > 5) {
                leaderboard.resize(5);
            }
        }
    }
}

void loadLeaderboard() {
    leaderboard.clear();

    std::ifstream leaderboardFile(leaderboardFilePath);

    if (leaderboardFile.is_open()) {
        std::string playerName;
        int score;

        while (leaderboardFile >> playerName >> score) {
            leaderboard.emplace_back(playerName, score);
        }

        leaderboardFile.close();
    }
}

void saveLeaderboard() {
    std::ofstream leaderboardFile(leaderboardFilePath);

    for (const auto& entry : leaderboard) {
        leaderboardFile << entry.playerName << " " << entry.score << std::endl;
    }

    leaderboardFile.close();
}

void displayLeaderboard() {
    loadLeaderboard();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-0.5, -0.15);

    std::string leaderboardText = "Leaderboard";
    for (char c : leaderboardText) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    float yPos = -0.25;
    for (const auto& entry : leaderboard) {
        glRasterPos2f(-0.5, yPos);
        std::string entryText = entry.playerName + ": " + std::to_string(entry.score);
        for (char c : entryText) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
        yPos -= 0.1;
    }

    saveLeaderboard();
}

void drawText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}