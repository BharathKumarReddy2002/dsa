#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int key;
    struct Node* next;
};

// Define the size of the hash table
#define TABLE_SIZE 11

// Create the hash table as an array of pointers to linked lists (chains)
struct Node* hashTable[TABLE_SIZE];

// Hash function to calculate the index for a given key
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to insert a key into the hash table
void insert(int key) {
    int index = hashFunction(key);
    
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;
    
    // If no collision, insert at the start of the list
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        // Collision handling by adding the node at the beginning of the linked list (separate chaining)
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

// Function to search for a key in the hash table
int search(int key) {
    int index = hashFunction(key);
    struct Node* temp = hashTable[index];
    
    // Traverse the linked list at that index to find the key
    while (temp != NULL) {
        if (temp->key == key) {
            return 1;  // Key found
        }
        temp = temp->next;
    }
    return 0;  // Key not found
}

// Function to display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        struct Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    // Initialize the hash table to NULL
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    // Insert keys into the hash table
    insert(22);
    insert(1);
    insert(13);
    insert(11);
    insert(24);
    insert(33);

    // Display the hash table
    display();

    // Search for a key
    int keyToFind = 13;
    if (search(keyToFind)) {
        printf("Key %d found in the hash table.\n", keyToFind);
    } else {
        printf("Key %d not found in the hash table.\n", keyToFind);
    }

    return 0;
}
