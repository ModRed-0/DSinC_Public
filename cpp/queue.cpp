#include <iostream> // For showing output
#include <queue>    // To use std::queue
#include <string>   // If you want to store text

int main() {
    // 1. Make a queue:
    std::queue<int> myCustomers; // A queue for customer IDs (whole numbers)

    // 2. Add something to the back (push):
    std::cout << "--- Adding customers to the back (push) ---" << std::endl;
    myCustomers.push(101); // Queue: [101]
    myCustomers.push(102); // Queue: [101, 102] (101 is at the front)
    myCustomers.push(103); // Queue: [101, 102, 103] (101 is at the front)
    std::cout << "Customers in line: " << myCustomers.size() << std::endl; // Shows 3

    // 3. Look at the item at the front (front):
    // Always check if the queue isn't empty first!
    std::cout << "\n--- Looking at the front customer (front) ---" << std::endl;
    if (!myCustomers.empty()) {
        std::cout << "Customer at the front is: " << myCustomers.front() << std::endl; // Shows 101
    }

    // 4. Look at the item at the back (back):
    std::cout << "\n--- Looking at the last customer (back) ---" << std::endl;
    if (!myCustomers.empty()) {
        std::cout << "Customer at the back is: " << myCustomers.back() << std::endl; // Shows 103
    }

    // 5. Serve (remove) the item from the front (pop):
    std::cout << "\n--- Serving the front customer (pop) ---" << std::endl;
    myCustomers.pop(); // Removes 101. Queue: [102, 103]
    std::cout << "Customers left: " << myCustomers.size() << std::endl; // Shows 2
    if (!myCustomers.empty()) {
        std::cout << "New front customer is: " << myCustomers.front() << std::endl; // Shows 102
    }

    // 6. Is it empty? (empty):
    std::cout << "\n--- Checking if empty (empty) ---" << std::endl;
    std::cout << "Is myCustomers queue empty? " << (myCustomers.empty() ? "Yes" : "No") << std::endl; // Shows No

    // 7. How many items? (size):
    std::cout << "\n--- Counting items (size) ---" << std::endl;
    std::cout << "Current count of customers: " << myCustomers.size() << std::endl; // Shows 2

    // 8. Clear out the whole queue:
    std::cout << "\n--- Serving all remaining customers ---" << std::endl;
    while (!myCustomers.empty()) { // As long as there are items...
        std::cout << "Serving: " << myCustomers.front() << std::endl; // Show who's at the front
        myCustomers.pop(); // Take them off the line
    }
    std::cout << "Is myCustomers queue empty now? " << (myCustomers.empty() ? "Yes" : "No") << std::endl; // Shows Yes

    // 9. emplace (similar to stack, for complex types)
    // Constructs an element directly in the queue, potentially more efficient.
    std::cout << "\n--- Emplace (for complex types) ---" << std::endl;
    struct Task {
        std::string description;
        int priority;
        Task(std::string d, int p) : description(d), priority(p) {
            std::cout << "Task '" << description << "' created!" << std::endl;
        }
    };

    std::queue<Task> taskQueue;
    taskQueue.emplace("Process email", 1);
    taskQueue.emplace("Print report", 2);

    if (!taskQueue.empty()) {
        std::cout << "Next task: '" << taskQueue.front().description << "' (Priority: " << taskQueue.front().priority << ")" << std::endl;
    }

    return 0;
}
