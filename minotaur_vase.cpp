#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <random>
#include <ctime>
#include <map>

// Number of guests
const int N = 10;

// Counter to keep track of guests who have visited the room
int visitedCount = 0;

// dictionary to track whether a specific guest has already entered the room
std::map<int, bool> guestVisit;

// Mutex to protect critical sections
std::mutex mtx;

// Queue to manage guest access to the showroom
std::queue<int> guestQueue;

// Function to represent a guest's behavior
void guest(int id) {
    while (true) {
        // Simulate time spent viewing the vase
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Try to enter the showroom (if first in queue)
        bool entered = false;

        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!guestQueue.empty() && guestQueue.front() == id) {
                entered = true;
                guestQueue.pop();
            }
        }

        if (entered) {
            std::cout << "Guest " << id << " entered the showroom and viewed the vase." << std::endl;
            
            if (!guestVisit[id]) {
                guestVisit[id] = true;
                visitedCount++;
            }

            // Simulate time spent inside the showroom
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            // Notify the next guest in queue (if any)
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!guestQueue.empty()) {
                    int nextGuest = guestQueue.front();
                    std::cout << "Guest " << id << " notifies Guest " << nextGuest << " that the showroom is available." << std::endl;
                }
            }
        }
        

        // Check if all guests have visited the showroom
        if (visitedCount >= N) {
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

    // Create guest threads
    std::vector<std::thread> guestThreads;

    // Start guest threads
    while (visitedCount < N) {
        int randomInt = rand() % N + 1; // Generate random guest ID
        guestQueue.push(randomInt);
        guestThreads.push_back(std::thread(guest, randomInt));
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    // Join guest threads with main thread
    for (auto& t : guestThreads) {
        t.join();
    }

    return 0;
}
