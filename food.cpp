#include "Food.h"  
#include <cstdlib>  // Includes rand() and srand() functions
#include <ctime>    

// Constructor initializes random seed and sets initial food position
Food::Food() {
    srand(time(nullptr));  // Seeds the random number generator with the current time
    position = {7,6};      // Sets the initial position of the food to (7,6)
}

// Generates a new food position that doesn't overlap with the snake's body
void Food::foodrespawn(int width, int height, const std::vector<std::pair<int, int>>& snakeBody) {
    while (true) {
        position.first = rand() % (width - 2) + 1;   // Random x within screen bounds (avoids walls)
        position.second = rand() % (height - 2) + 1; // Random y within screen bounds (avoids walls)

        bool onSnake = false;  // Flag to check if food is on the snake

        // Check if the new position overlaps with any part of the snake
        for (const auto& segment : snakeBody) {
            if (segment == position) {  // If food position matches any snake segment
                onSnake = true;         // Set flag and break
                break;
            }
        }
        if (!onSnake) break;  // Exit loop if food is not on the snake
    }
}

// Returns the current position of the food
std::pair<int, int> Food::GetFoodPosition() const { 
    return position; 
}

// Returns true if the snake's head is on the same position as the food
bool Food::IsEaten(const std::pair<int, int>& snakeHead) const {
    return snakeHead == position;
}