#pragma once 

#include <vector>  

// Enum to represent the direction of the snake
enum class Direction { STOP, UP, DOWN, LEFT, RIGHT }; 

// Snake class to represent the snake's behavior and data
class Snake {
private:
    std::vector<std::pair<int, int>> body; // Stores the positions of all parts of the snake's body
    Direction dir; // Stores the current movement direction of the snake
    bool grow; // Flag to indicate whether the snake should grow on the next move
public:
    Snake(); // Constructor to initialize the snake
    void ChangeDirection(Direction newDir); // Changes the snake's direction
    void Move(int width, int height); // Moves the snake and handles wrapping or screen edges
    void Grow(); // Enables the snake to grow in length
    bool CheckCollision(int width, int height) const; // Checks if the snake collided with itself or walls
    const std::vector<std::pair<int, int>>& GetBody() const; // Returns the full body of the snake
    std::pair<int, int> GetHead() const; // Returns the current head position of the snake
};