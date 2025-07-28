#pragma once  

#include <utility>  
#include <vector>   

class Food {
private:
    std::pair<int, int> position;  // Holds the current position of the food (x, y)

public:
    Food();  // Constructor to initialize the food

    // Respawns the food at a random position not occupied by the snake
    void foodrespawn(int width, int height, const std::vector<std::pair<int, int>>& snakeBody);

    // Returns the current position of the food
    std::pair<int, int> GetFoodPosition() const;

    // Checks if the food has been eaten by comparing with the snake's head
    bool IsEaten(const std::pair<int, int>& snakeHead) const;
};
