#include "Game.h"  
#include <conio.h>  
#include <iostream>
#include <windows.h>  
#include <fstream> 
#include <iomanip>  
#include <string>  

// Constructor initializes game variables and loads the high score
Game::Game() : score(0), gameOver(false), ispaused(false), speed(100) {
    LoadHighScore();  // Load high score from file
}

// Loads the high score from a file, or sets it to 0 if file not found
void Game::LoadHighScore() {
    std::ifstream file("highscore.txt");  // Try to open the file
    if (file) {
        file >> highScore;  // Read high score value
    } else {
        highScore = 0;  // Default value if file doesn't exist
    }
}

// Saves the score to the file if it's higher than the previous high score
void Game::SaveHighScore() {
    if (score > highScore) {
        std::ofstream file("highscore.txt");  // Open file for writing
        if (file) {
            file << score;  // Save the new high score
            highScore = score;  // Update in memory
        }

    }
}

// Main game loop that runs the full game cycle
void Game::Run() {
    char playAgain;  // To store user choice to play again

    do {
        gameOver = false;  // Reset game over state
        score = 0;  // Reset score
        snake = Snake();  // Create new snake object
        food.foodrespawn(width, height, snake.GetBody());  // Spawn new food

        while (!gameOver) {  // Game loop continues until gameOver
            Draw();      // Draw the game
            Input();     // Handle user input
            if (gameOver) break; // Exit the loop immediately if the player press q 
            Logic();     // Update game logic
            Sleep(speed);  // Control game speed
        }

        // Save the high score when game ends
        SaveHighScore();

        // Display game over screen
        system("cls");
        SetColor(12);  // Red color
        std::cout << "|====================|\n"
                  << "|     GAME OVER!     |\n"
                  << "|====================|\n"
                  << "| Score:    " << score << std::setw(13 - std::to_string(score).length()) << "║\n"
                  << "|====================|\n"
                  << "| 1. Play Again      |\n"
                  << "| 2. Exit            |\n"
                  << "|====================|\n";

        SetColor(15);  // White color
        std::cout << "Choice: ";
        std::cin >> playAgain;  // Get user choice

    } while (playAgain == '1');  // Loop if user chooses to play again
}

// Displays the main menu before starting the game
void Game::ShowMenu() {
    system("cls");  // Clear the screen
    SetColor(11);   // Light blue color
    std::cout << "|====================|\n"
              << "|    SNAKE GAME      |\n"
              << "|====================|\n"
              << "| 1. Start Game      |\n"
              << "| 2. Exit            |\n"
              << "|====================|\n";
}

// Sets the console text color using Windows API
void Game::SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Draws the game board, snake, food, and score
void Game::Draw() {
    system("cls");  // Clear the screen
    SetColor(15);  // Set default color (white)

    // Draw top border
    std::cout << "|";
    for (int i = 0; i < width; i++) std::cout << "=";
    std::cout << "|" << std::endl;

    // Draw game area row by row
    for (int y = 0; y < height; y++) {
        std::cout << "|";  // Left wall
        for (int x = 0; x < width; x++) {
            // Draw food
            if (x == food.GetFoodPosition().first && y == food.GetFoodPosition().second) {
                SetColor(12);  // Red for food
                std::cout << "x";
                SetColor(15);  // Reset color
            }
            else {
                bool isBodyPart = false;
                const auto& body = snake.GetBody();

                // Check if current position is part of the snake
                for (size_t i = 0; i < body.size(); ++i) {
                    if (body[i].first == x && body[i].second == y) {
                        SetColor(i == 0 ? 10 : 2);  // Light green for head, dark green for body
                        std::cout << (i == 0 ? "O" : "o");
                        isBodyPart = true;
                        SetColor(15);  // Reset color
                        break;
                    }
                }

                if (!isBodyPart) std::cout << " ";  // Empty space
            }
        }
        std::cout << "|" << std::endl;  // Right wall
    }

    // Draw bottom border
    std::cout << "|";
    for (int i = 0; i < width; i++) std::cout << "=";
    std::cout << "|" << std::endl;

    // Show score and high score
    SetColor(11);  // Light blue color
    std::cout << "Score: " << score << std::endl;
    std::cout << "High Score: " << highScore << std::endl;

    // Show pause message if game is paused
    if (ispaused) {
        SetColor(14);  // Yellow
        std::cout << "The Game is Paused (Press p to Resume)" << std::endl;
    }
    SetColor(14);
    std::cout << "Press q to Quit" << std::endl;
    SetColor(15);  // Reset color
}

// Handles user keyboard input using WASD keys and pause
void Game::Input() {
    if (_kbhit()) {  // Check if a key was pressed
        char ch = _getch();  // Get the pressed key
        switch (tolower(ch)) {
            case 'w': snake.ChangeDirection(Direction::UP); break;
            case 's': snake.ChangeDirection(Direction::DOWN); break;
            case 'a': snake.ChangeDirection(Direction::LEFT); break;
            case 'd': snake.ChangeDirection(Direction::RIGHT); break;
            case 'p': ispaused = !ispaused; break; 
            case 'q': gameOver = true; break;
        }
    }
}

// Updates the game logic including movement, collisions, and scoring
void Game::Logic() {
    if (ispaused) return;  // Skip logic if paused

    snake.Move(width, height);  // Move the snake

    // Check if the snake eats the food
    if (snake.GetHead() == food.GetFoodPosition()) {
        snake.Grow();  // Increase snake length
        food.foodrespawn(width, height, snake.GetBody());  // Generate new food
        score += 10;  // Add points
    }

    // Increase speed every 30 points (up to a limit)
    if (score % 30 == 0 && speed > 50) {
        speed -= 10;  // Make game faster
    }

    // Check for collisions with self
    gameOver = snake.CheckCollision(width, height);
}

// Returns whether the game is over
bool Game::IsGameOver() const { return gameOver; }

// Returns the current score
int Game::GetScore() const { return score; }