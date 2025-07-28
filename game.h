#pragma once  

#include "Snake.h" 
#include "Food.h"   

class Game {
private:
    const int width = 30;   // Width of the game board
    const int height = 15;  // Height of the game board
    Snake snake;            // Snake object that controls snake behavior
    Food food;              // Food object that controls food behavior
    int score;              // Current score of the player
    bool gameOver;          // Flag indicating if the game has ended
    bool ispaused;          // Flag indicating if the game is paused
    int speed;              // Game speed (controls delay/movement)
    int highScore;          // Stores the highest score achieved
    void LoadHighScore();   // Loads the high score from a file or storage
    void SaveHighScore();   // Saves the current high score to a file or storage

public:
    Game();                 // Constructor to initialize game state
    void Run();             // Starts and runs the main game loop
    void ShowMenu();        // Displays the main menu to the player
    void SetColor(int color); // Sets text color in the console (platform-dependent)
    void Draw();            // Draws the game board, snake, and food on the screen
    void Input();           // Handles user keyboard input
    void Logic();           // Updates game logic such as movement and collisions
    bool IsGameOver() const; // Returns true if the game has ended
    int GetScore() const;   // Returns the current score
};