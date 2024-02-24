# COP4520_assignment2

Compile terminal commands:

Problem 1 commands
(1) g++ -std=c++11 -pthread minotaur_birthday.cpp -o minotaur_birthday
(2) ./minotaur_birthday

Problem 2 commands
(1) g++ -std=c++11 -pthread minotaur_vase.cpp -o minotaur_vase
(2) ./minotaur_vase


# [Problem 2] Advantages and Disadvantages

Strategy 1:
Advantages -- 
1. Don't have to manage a queue / sorting system
2. Large crowd; unordered

Disadvantges --
1. Inefficient, guests have to continually check if they're able to go into the room
2. Guest has no guarantee that they'll be able to see the vase
3. Slow

Strategy 2
Advantages --
1. Crowd outside the room will not be as large
2. Minotaur is able to keep track of whether or not the room is in use
3. Don't have to manage a queue / sorting system

Disadvantges --
1. Guests still have to continually check if the room is available
2. No managing system implemented
3. Slow


Strategy 3
Advantages -- 
1. Ordered
2. No crowd outside the room; ordered line instead

Disadvantges --
1. Have to manage a queue
2. Guests have to tell next person they're done instead of using a sign; guests have to self-maintain availability
