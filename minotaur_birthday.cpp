#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include <ctime>
#include <map>

// Number of guests
const int N = 10;

// dictionary to track of whether a specific guest has already entered the labryinth
std::map<int, bool> guestVisit;

// Mutex to protect critical sections
std::mutex mtx;

// Counter to keep track of guests who have visited the labyrinth
int visitedCount = 0;

// Function to represent a guest's behavior
void guest(int id) {
    while (true) {

        // Dummy value to simulate labyrinth navigation
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Random value deciding if the guest ate the cupcake or not
        bool eatCupcake = (rand() % 2) == 0;

        // [terminal] notification for if the guest ate the cupcake
        if (eatCupcake) {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Guest " << id << " ate the cupcake." << std::endl;
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!guestVisit[id]) {
                visitedCount++;
                guestVisit[id] = true; // setting guestVisit to true
                std::cout << "Guest " << id << " has visited the labyrinth." << std::endl;
            }
        }

        // Check if all guests have visited the labyrinth
        if (visitedCount >= N) {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "All guests have visited the labyrinth. No guest is uncounted for." << std::endl;
            break;
        }
    }
}

int main() {
    // Seed for random number generation
    srand(time(NULL));

    // Initialize guestVisit map
    for (int i = 1; i <= N; ++i) {
        guestVisit[i] = false; // No guest has visited the labyrinth yet
    }

    // guest threads vector
    std::vector<std::thread> guestThreads;

    // Create guest threads
    while (visitedCount < N) {
        int randomInt = rand() % N + 1; // Generate random guest ID
        guestThreads.push_back(std::thread(guest, randomInt));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }   

    // Join guest threads with main thread
    for (auto& t : guestThreads) {
        t.join();
    }

    return 0;
}
