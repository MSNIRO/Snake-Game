#include "Game.h"      
#include <iostream>    

int main() {
    Game g; // Creates a Game object to manage and run the game
    g.ShowMenu(); // Displays the main menu to the player
    char choice; // Variable to store player's menu choice
    std::cin >> choice; // Takes input from the user (e.g., 1 to start the game)
    if (choice == '1') g.Run(); // If user chooses '1', start the game loop
    return 0;     
}
