#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

const int TABLE_SIZE = 10;

// Hashing Functions
int divisionMethod(int key) {
    return key % TABLE_SIZE;
}

int multiplicationMethod(int key) {
    float A = 0.618033; // constant (0 < A < 1)
    return int(TABLE_SIZE * fmod(key * A, 1));
}

int midSquareMethod(int key) {
    int squared = key * key;
    int mid = (squared / 100) % 100;
    return mid % TABLE_SIZE;
}

int foldingMethod(int key) {
    string keyStr = to_string(key);
    int sum = 0;
    for (size_t i = 0; i < keyStr.length(); i += 2) {
        sum += stoi(keyStr.substr(i, 2));
    }
    return sum % TABLE_SIZE;
}

// Collision Resolution: Chaining Method
class ChainingHashTable {
    vector<list<int>> table;

public:
    ChainingHashTable() : table(TABLE_SIZE) {}

    void insert(int key) {
        int hashIndex = divisionMethod(key);
        table[hashIndex].push_back(key);
    }

    int search(int key) {
        int hashIndex = divisionMethod(key);
        int index = 0;
        for (int x : table[hashIndex]) {
            if (x == key) return hashIndex;
            index++;
        }
        return -1;
    }


    void remove(int key) {
        int hashIndex = divisionMethod(key);
        table[hashIndex].remove(key);
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << i << ": ";
            for (int x : table[i])
                cout << x << " -> ";
            cout << "NULL\n";
        }
    }

    void menu() {
        int choice, key;
        do {
            cout << "\nChaining Hash Table Menu:\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter key to insert: ";
                    cin >> key;
                    insert(key);
                    break;
                case 2:
                    {cout << "Enter key to search: ";
                    cin >> key;
                    int result = search(key);
                    if (result==-1){
                        cout<<"Not found"<<endl;
                    } else{
                        cout<<"Element found at index: "<<result<<endl;
                    }
                    break;}
                case 3:
                    cout << "Enter key to delete: ";
                    cin >> key;
                    remove(key);
                    break;
                case 4:
                    display();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};

// Open Addressing Method
class OpenAddressingHashTable {
    vector<int> table;
    vector<bool> occupied;

public:
    OpenAddressingHashTable() : table(TABLE_SIZE, -1), occupied(TABLE_SIZE, false) {}

    void insert(int key) {
        int hashIndex = divisionMethod(key);
        int i = 0;
        while (occupied[(hashIndex + i) % TABLE_SIZE]) {
            i++;
        }
        table[(hashIndex + i) % TABLE_SIZE] = key;
        occupied[(hashIndex + i) % TABLE_SIZE] = true;
    }

    int search(int key) {
        int hashIndex = divisionMethod(key);
        int i = 0;
        while (occupied[(hashIndex + i) % TABLE_SIZE]) {
            if (table[(hashIndex + i) % TABLE_SIZE] == key) return (hashIndex + i) % TABLE_SIZE;
            i++;
        }
        return -1;
    }


    void remove(int key) {
        int hashIndex = divisionMethod(key);
        int i = 0;
        while (occupied[(hashIndex + i) % TABLE_SIZE]) {
            if (table[(hashIndex + i) % TABLE_SIZE] == key) {
                table[(hashIndex + i) % TABLE_SIZE] = -1;
                occupied[(hashIndex + i) % TABLE_SIZE] = false;
                return;
            }
            i++;
        }
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << i << ": " << (occupied[i] ? to_string(table[i]) : "NULL") << endl;
        }
    }

    void menu() {
        int choice, key;
        do {
            cout << "\nOpen Addressing Menu:\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter key to insert: ";
                    cin >> key;
                    insert(key);
                    break;
                case 2:
                   {cout << "Enter key to search: ";
                    cin >> key;
                    int result = search(key);
                    if (result==-1){
                        cout<<"Not found"<<endl;
                    } else{
                        cout<<"Element found at index: "<<result<<endl;
                    }
                    break;}
                case 3:
                    cout << "Enter key to delete: ";
                    cin >> key;
                    remove(key);
                    break;
                case 4:
                    display();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};

// Double Hashing Method
class DoubleHashingHashTable {
    vector<int> table;
    vector<bool> occupied;

    int hash2(int key) {
        return 7 - (key % 7);
    }

public:
    DoubleHashingHashTable() : table(TABLE_SIZE, -1), occupied(TABLE_SIZE, false) {}

    void insert(int key) {
        int hashIndex = divisionMethod(key);
        int step = hash2(key);
        int i = 0;
        while (occupied[(hashIndex + i * step) % TABLE_SIZE]) {
            i++;
        }
        table[(hashIndex + i * step) % TABLE_SIZE] = key;
        occupied[(hashIndex + i * step) % TABLE_SIZE] = true;
    }

    int search(int key) {
        int hashIndex = divisionMethod(key);
        int step = hash2(key);
        int i = 0;
        while (occupied[(hashIndex + i * step) % TABLE_SIZE]) {
            if (table[(hashIndex + i * step) % TABLE_SIZE] == key) return (hashIndex + i * step) % TABLE_SIZE;
            i++;
        }
        return -1;
    }

    void remove(int key) {
        int hashIndex = divisionMethod(key);
        int step = hash2(key);
        int i = 0;
        while (occupied[(hashIndex + i * step) % TABLE_SIZE]) {
            if (table[(hashIndex + i * step) % TABLE_SIZE] == key) {
                table[(hashIndex + i * step) % TABLE_SIZE] = -1;
                occupied[(hashIndex + i * step) % TABLE_SIZE] = false;
                return;
            }
            i++;
        }
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << i << ": " << (occupied[i] ? to_string(table[i]) : "NULL") << endl;
        }
    }

    void menu() {
        int choice, key;
        do {
            cout << "\nDouble Hashing Menu:\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter key to insert: ";
                    cin >> key;
                    insert(key);
                    break;
                case 2:
                    {cout << "Enter key to search: ";
                    cin >> key;
                        int result = search(key);
                        if (result==-1){
                            cout<<"Not found"<<endl;
                        } else{
                            cout<<"Element found at index: "<<result<<endl;
                        }
                    break;}
                case 3:
                    cout << "Enter key to delete: ";
                    cin >> key;
                    remove(key);
                    break;
                case 4:
                    display();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }};

void showMenu() {
    cout << "Select a hashing technique or collision resolution method:\n";
    cout << "1. Division Method\n";
    cout << "2. Multiplication Method\n";
    cout << "3. Mid-Square Method\n";
    cout << "4. Folding Method\n";
    cout << "5. Chaining Method\n";
    cout << "6. Open Addressing Method\n";
    cout << "7. Double Hashing\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int tableSize = 10;
    int choice, key;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter key: ";
                cin >> key;
                cout << "Hash index (Division Method): " << divisionMethod(key) << "\n";
                break;
            }
            case 2: {
                cout << "Enter key: ";
                cin >> key;
                cout << "Hash index (Multiplication Method): " << multiplicationMethod(key) << "\n";
                break;
            }
            case 3: {
                cout << "Enter key: ";
                cin >> key;
                cout << "Hash index (Mid-Square Method): " << midSquareMethod(key) << "\n";
                break;
            }
            case 4: {
                cout << "Enter key: ";
                cin >> key;
                cout << "Hash index (Folding Method): " << foldingMethod(key) << "\n";
                break;
            }
            case 5: {
                ChainingHashTable hashTable;

                hashTable.menu();
                break;
            }
            case 6: {
                OpenAddressingHashTable hashTable;

                hashTable.menu();
                break;
            }
            case 7: {
                DoubleHashingHashTable hashTable;

                hashTable.menu();
                break;
            }
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << "\n";
    }

    return 0;

}
