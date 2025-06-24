#include <iostream> // For showing output
#include <stack>    // To use std::stack
#include <string>   // If you want to store text

int main() {
    // 1. Make a stack:
    std::stack<int> myNumbers; // A stack for whole numbers

    // 2. Put something on top (push):
    std::cout << "--- Adding numbers (push) ---" << std::endl;
    myNumbers.push(10); // Stack: [10]
    myNumbers.push(20); // Stack: [10, 20] (20 is on top)
    myNumbers.push(30); // Stack: [10, 20, 30] (30 is on top)
    std::cout << "Numbers in stack: " << myNumbers.size() << std::endl; // Shows 3

    // 3. Look at the top item (top):
    // Always check if the stack isn't empty first!
    std::cout << "\n--- Looking at the top (top) ---" << std::endl;
    if (!myNumbers.empty()) {
        std::cout << "Top number is: " << myNumbers.top() << std::endl; // Shows 30
    }

    // 4. Take the top item off (pop):
    std::cout << "\n--- Taking off the top (pop) ---" << std::endl;
    myNumbers.pop(); // Removes 30. Stack: [10, 20]
    std::cout << "Numbers left: " << myNumbers.size() << std::endl; // Shows 2
    if (!myNumbers.empty()) {
        std::cout << "New top number is: " << myNumbers.top() << std::endl; // Shows 20
    }

    // 5. Is it empty? (empty):
    std::cout << "\n--- Checking if empty (empty) ---" << std::endl;
    std::cout << "Is myNumbers stack empty? " << (myNumbers.empty() ? "Yes" : "No") << std::endl; // Shows No

    // 6. How many items? (size):
    std::cout << "\n--- Counting items (size) ---" << std::endl;
    std::cout << "Current count of numbers: " << myNumbers.size() << std::endl; // Shows 2

    // 7. Clear out the whole stack:
    std::cout << "\n--- Clearing the stack ---" << std::endl;
    while (!myNumbers.empty()) { // As long as there are items...
        std::cout << "Removing: " << myNumbers.top() << std::endl; // Show what's on top
        myNumbers.pop(); // Take it off
    }
    std::cout << "Is myNumbers stack empty now? " << (myNumbers.empty() ? "Yes" : "No") << std::endl; // Shows Yes

    // 8. push vs. emplace (a small optimization for complex items)
    // For simple types like int, push and emplace do pretty much the same thing.
    // But for more complex "objects", emplace can sometimes be faster because
    // it builds the object right inside the stack, instead of building it outside
    // and then copying it in.
    std::cout << "\n--- Emplace (for complex types) ---" << std::endl;
    struct Player {
        std::string name;
        int score;
        Player(std::string n, int s) : name(n), score(s) {
            std::cout << "Player " << name << " created!" << std::endl;
        }
    };

    std::stack<Player> gamePlayers;
    // With emplace, we directly give arguments to create the Player object
    gamePlayers.emplace("Alice", 100);
    gamePlayers.emplace("Bob", 150);

    if (!gamePlayers.empty()) {
        std::cout << "Top player: " << gamePlayers.top().name << " with score " << gamePlayers.top().score << std::endl;
    }

    return 0;
}
