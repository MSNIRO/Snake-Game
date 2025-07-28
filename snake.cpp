#include "Snake.h"  
 
// Constructor initializes direction to STOP and places the snake at position (5,5)
Snake::Snake() : dir(Direction::STOP), grow(false) {
    body.emplace_back(5,5);  
}

// Changes the snake's direction if it's a valid move
void Snake::ChangeDirection(Direction newDir) {
    // Allow first move from STOP to any direction except STOP
    if (dir == Direction::STOP && newDir != Direction::STOP) {
        dir = newDir;
        return;
    }

    // Prevent snake from reversing directly into itself
    if ((dir == Direction::UP && newDir != Direction::DOWN) ||
        (dir == Direction::DOWN && newDir != Direction::UP) ||
        (dir == Direction::LEFT && newDir != Direction::RIGHT) ||
        (dir == Direction::RIGHT && newDir != Direction::LEFT)) {
        dir = newDir;
    }
}

// Moves the snake in the current direction and handles growth and screen wrapping
void Snake::Move(int width, int height) {
    if (dir == Direction::STOP) return;  // If direction is STOP, don't move

    auto head = body.front();  // Get current head position

    // Update head position based on direction
    switch (dir) {
        case Direction::UP:    head.second--; break;   // Move up
        case Direction::DOWN:  head.second++; break;   // Move down
        case Direction::LEFT:  head.first--; break;    // Move left
        case Direction::RIGHT: head.first++; break;    // Move right
        case Direction::STOP:  return;                 // Do nothing
    }

    // Wrap around if snake crosses horizontal boundary
    if (head.first < 0) head.first = width - 1;
    else if (head.first >= width)  head.first = 0;

    // Wrap around if snake crosses vertical boundary
    if (head.second < 0) head.second = height - 1;
    else if (head.second >= height)  head.second = 0;

    body.insert(body.begin(), head);  // Insert new head at the beginning of the body

    if (!grow) {
        body.pop_back();  // Remove last segment if not growing
    } else {
        grow = false;     // Reset grow flag after growing
    }
}

// Sets the grow flag so that the snake will grow on the next move
void Snake::Grow() {
    grow = true;
}

// Checks if the snake's head has collided with its body
bool Snake::CheckCollision(int width, int height) const {
    auto head = body.front();  // Get the head position

    // Wrap around logic (same as in Move)
    if (head.first < 0) head.first = width - 1;
    else if (head.first >= width)  head.first = 0;
    if (head.second < 0) head.second = height - 1;
    else if (head.second >= height)  head.second = 0;

    // Check if head collides with any other part of the body
    for (auto i = 1; i < body.size(); i++) {
        if (head == body[i])
            return true;  // Collision detected
    }

    return false;  // No collision
}

// Returns a constant reference to the entire snake body
const std::vector<std::pair<int, int>>& Snake::GetBody() const {
    return body;
}

// Returns the current head position of the snake
std::pair<int, int> Snake::GetHead() const {
    return body.front();
}