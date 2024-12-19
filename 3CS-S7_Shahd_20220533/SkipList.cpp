#include <bits/stdc++.h>
using namespace std;

const int maxL = 4;

class node{
public:
    int data;
    vector <node*> next;
    node (int data, int level):data (data),next(level+1, nullptr){};
};
class skipList {
private:
    node* head;
    int level;
public:
    skipList();

    void insert(int data);  // To insert the value
    void remove(int data);  // To delete the value
    bool search(int data);  // To search for a value
    void display();         // Function to display a skip List

};
skipList:: skipList()
{
    head = new node(0, maxL);    // Initializing the skip list with the max number of levels

    level = 0;                               // At start the level is 0

}


void skipList::insert(int data)
{
    int newLevel = 0;

    // Deciding the level of inserting node on the basis of coin toss

    while (newLevel < maxL and (rand() % 2) == 1) // here rand()%2 is doing the coin toss
    {
        newLevel++;
    }
    // Resizing the size of the levels to make place for the inserting value

    if (level < newLevel)
    {
        head->next.resize(newLevel + 1, nullptr);

        level = newLevel;
    }

    node* current = head; // pointer to the head to traverse through the skip list

    vector<node*> Update(level + 1, nullptr); // To store the update node at eah level

    // Loop over the levels upto which we want the value to be inserted

    for (int i = level; i >= 0; i--)
    {
        // Finding the place for the inserting value

        while (current->next[i] and current->next[i]->data < data)
        {
            current = current->next[i];
        }
        // Updating the level accordingly

        Update[i] = current;

    }

    current = current->next[0];   // Moves the current to the next node at level 0

    if (current == nullptr or current->data != data) // if the current is null then it does not exit we need to insert the value
    {
        node* newNode = new node(data, level);

        for (int i = 0; i <= newLevel; i++)
        {
            newNode->next[i] = Update[i]->next[i];

            Update[i]->next[i] = newNode;  // To insert the value at each level

        }

        cout << "Element " << data << " inserted successfully.\n";
    }
    else
    {
        cout << "Element " << data << " already exists.\n";  // Incase if value already exists
    }
}

void skipList::remove(int data)
{
    // Function to remove value
    node* current = head; // start by setting a current pointer to the head node

    vector<node*> Update(level + 1, nullptr); // Create an update vector to store the updated node at each level, Remember only those nodes will be updated where the value to be deleted is present.

    for (int i = level; i >= 0; i--)
    {
        while (current->next[i] and current->next[i]->data < data)
        {
            current = current->next[i];
        }

        Update[i] = current;         // Update array is keeping the track, where the changes should be made, after deleting the node.
    }

    current = current->next[0];     // Set the current pointer to the next node at level 0.

    if (current != nullptr and current->data == data) // If the value is present then delete the value
    {
        for (int i = 0; i <= level; i++)      // Deleting the value from each level
        {
            // Setting the pointers
            if (Update[i]->next[i] != current)
            {
                break;
            }
            else
            {
                Update[i]->next[i] = current->next[i];
            }
        }

        delete current; // deleting the node

        while (level > 0 and head->next[level] == nullptr)  // decrement the level variable incase there is not any value at that level
        {
            level--;
        }

        cout << "Element " << data << " deleted successfully."<<endl;
    }
    else // Incase the value does not exist
    {
        cout << "Element " << data << " not found."<<endl;
    }
}

bool skipList::search(int data)
{
    node* current = head;           // start by setting a current pointer to the head node to traverse through the skip list


    for (int i = level; i >= 0; i--) // Begin traversing from the top level and iteratively approaching the bottom of the skip list
    {
        while (current->next[i] and current->next[i]->data < data) // keep on moving forward if the value of the next node is less than the searching node otherwise  move downward (handled by outer for loop)
        {
            current = current->next[i]; // moving forward

        }
    }

    current = current->next[0]; // Move to the next of the node at level 0

    if (current != nullptr && current->data == data) // if value is found
    {
        cout << "Element " << data << " found.\n";
        return true;
    }
    else  // Incase value does not exist
    {
        cout << "Element " << data << " not found.\n";
        return false;
    }
}
void skipList::display() {
    for (int i = level; i >= 0; i--) { // Loop from the highest level to level 0
        cout << "Level " << i << ":   "; // Print the current level

        node* current = head->next[i]; // Start from the head's next pointer at this level

        while (current != nullptr) { // Traverse all nodes at this level
            cout << "[" << current->data << "] --> ";
            current = current->next[i]; // Move to the next node at this level
        }

        cout << "nullptr" << endl; // End of the level
    }
}

////// game //////////////
 // Include your skip list implementation

class GameScores {
private:
    skipList skipList; // Skip list to manage scores
    unordered_map<string, int> playerMap; // Maps player names to scores
    multiset<int> scores; // To handle duplicate scores efficiently

public:
    GameScores() : skipList() {}

    void updateScore(string playerName, int newScore);
    vector<pair<string, int>> getTopPlayers(int N);
    void addPlayer(string playerName, int initialScore);
    void removePlayer(string playerName);
    int getPlayerScore(string playerName);
};

void GameScores::updateScore(string playerName, int newScore) {
    if (playerMap.find(playerName) != playerMap.end()) {
        int oldScore = playerMap[playerName];
        scores.erase(scores.find(oldScore));
        skipList.remove(oldScore);
    }
    playerMap[playerName] = newScore;
    scores.insert(newScore);
    skipList.insert(newScore);
    cout << "Player " << playerName << "'s score updated to " << newScore << endl;
}

vector<pair<string, int>> GameScores::getTopPlayers(int N) {
    vector<pair<string, int>> leaderboard;
    auto it = scores.rbegin(); // Access the highest scores
    while (N > 0 && it != scores.rend()) {
        for (const auto& player : playerMap) {
            if (player.second == *it) {
                leaderboard.emplace_back(player.first, player.second);
                N--;
                break;
            }
        }
        ++it;
    }
    return leaderboard;
}

void GameScores::addPlayer(string playerName, int initialScore) {
    if (playerMap.find(playerName) != playerMap.end()) {
        cout << "Player " << playerName << " is already in the game." << endl;
        return;
    }
    playerMap[playerName] = initialScore;
    scores.insert(initialScore);
    skipList.insert(initialScore);
    cout << "Player " << playerName << " added with score " << initialScore << endl;
}

void GameScores::removePlayer(string playerName) {
    if (playerMap.find(playerName) == playerMap.end()) {
        cout << "Player " << playerName << " not found in the game." << endl;
        return;
    }
    int score = playerMap[playerName];
    scores.erase(scores.find(score));
    skipList.remove(score);
    playerMap.erase(playerName);
    cout << "Player " << playerName << " removed from the game." << endl;
}

int GameScores::getPlayerScore(string playerName) {
    if (playerMap.find(playerName) == playerMap.end()) {
        cout << "Player " << playerName << " not found in the game." << endl;
        return -1;
    }
    return playerMap[playerName];
}
void Menu(){
    cout << "\nMultiplayer Game Menu:\n "
            "1. Add Player\n "
            "2. Remove Player\n"
            "3. Update Player Score\n"
            "4. Get Player Score\n"
            "5. Display Leaderboard\n"
            "6. Exit\n";
}
int main() {
    cout<<"Testing Skip List:\n";

    skipList SkipList; // Creating the skip List

    // Inserting the Data in skip list

    SkipList.insert(10);
    SkipList.insert(20);
    SkipList.insert(30);
    SkipList.insert(40);
    SkipList.insert(50);

    // Display skip list after inserting the data

    SkipList.display();

    // Searching for the key

    SkipList.search(20);
    SkipList.search(40);


    // Deleting the key

    SkipList.remove(20);
    SkipList.remove(40);

    // Display the skip list after removing the data

    SkipList.display();
    cout<<"Testing Game:\n";
    char continueGame = 'y'; // Variable to control termination of the game

    GameScores game;
    while (continueGame == 'y' || continueGame == 'Y') {
        int choice;
        Menu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Add a player
            string playerName;
            int initialScore;
            cout << "Enter player name: ";
            cin >> playerName;
            cout << "Enter initial score: ";
            cin >> initialScore;
            game.addPlayer(playerName, initialScore);
        } else if (choice == 2) {
            // Remove a player
            string playerName;
            cout << "Enter player name: ";
            cin >> playerName;
            game.removePlayer(playerName);
        } else if (choice == 3) {
            // Update a player's score
            string playerName;
            int newScore;
            cout << "Enter player name: ";
            cin >> playerName;
            cout << "Enter new score: ";
            cin >> newScore;
            game.updateScore(playerName, newScore);
        } else if (choice == 4) {
            // Get a player's score
            string playerName;
            cout << "Enter player name: ";
            cin >> playerName;
            int score = game.getPlayerScore(playerName);
            if (score != -1) {
                cout << playerName << "'s score: " << score << endl;
            }
        } else if (choice == 5) {
            // Display leaderboard
            int N;
            cout << "Enter the number of top players to display: ";
            cin >> N;
            vector<pair<string, int>> leaderboard = game.getTopPlayers(N);
            cout << "Leaderboard:\n";
            for (auto& player : leaderboard) {
                cout << player.first << ": " << player.second << endl;
            }
        } else if (choice == 6) {
            // Ask the user to confirm exiting
            cout << "Are you sure you want to exit the game? (y/n): ";
            char confirmExit;
            cin >> confirmExit;
            if (confirmExit == 'y' || confirmExit == 'Y') {
                cout << "Exiting the game. Goodbye!\n";
                break;
            }
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

        // Ask the user if they want to continue
        cout << "Do you want to continue? (y/n): ";
        cin >> continueGame;
    }

    cout << "Game terminated by the user. Goodbye!\n";
    return 0;

    // Add players
    game.addPlayer("Alice", 1500);
    game.addPlayer("Bob", 1200);
    game.addPlayer("Charlie", 1800);

    // Update scores
    game.updateScore("Alice", 1600);
    game.updateScore("Bob", 1700);

    // Get top players
    vector<pair<string, int>> leaderboard = game.getTopPlayers(2);
    cout << "Leaderboard:\n";
    for (auto& player : leaderboard) {
        cout << player.first << ": " << player.second << endl;
    }

    // Player management
    cout << "Alice's score: " << game.getPlayerScore("Alice") << endl;
    game.removePlayer("Alice");

    return 0;
}
