#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for maximum name length and file type
#define MAX_NAME 50

// Define the structure for a file system node (directory or file)
struct Node {
    char name[MAX_NAME];     // Name of the directory or file
    int isFile;              // 1 for file, 0 for directory
    struct Node* child;      // Pointer to the first child (if directory)
    struct Node* sibling;    // Pointer to the next sibling node
};

// Function to create a new node (either a file or directory)
struct Node* createNode(char* name, int isFile) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->isFile = isFile;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to create a new directory under the current directory
void createDirectory(struct Node* currentDir, char* name) {
    struct Node* newDir = createNode(name, 0);  // 0 indicates it's a directory

    if (currentDir->child == NULL) {
        currentDir->child = newDir;  // First child
    } else {
        // Add new directory to the siblings of the first child
        struct Node* temp = currentDir->child;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = newDir;
    }

    printf("Directory '%s' created successfully.\n", name);
}

// Function to create a new file under the current directory
void createFile(struct Node* currentDir, char* name) {
    struct Node* newFile = createNode(name, 1);  // 1 indicates it's a file

    if (currentDir->child == NULL) {
        currentDir->child = newFile;  // First child
    } else {
        // Add new file to the siblings of the first child
        struct Node* temp = currentDir->child;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = newFile;
    }

    printf("File '%s' created successfully.\n", name);
}

// Function to display the contents of the current directory
void listDirectory(struct Node* currentDir) {
    if (currentDir->child == NULL) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Contents of directory '%s':\n", currentDir->name);
    struct Node* temp = currentDir->child;
    while (temp != NULL) {
        if (temp->isFile) {
            printf("File: %s\n", temp->name);
        } else {
            printf("Directory: %s\n", temp->name);
        }
        temp = temp->sibling;
    }
}

// Function to navigate into a subdirectory
struct Node* changeDirectory(struct Node* currentDir, char* name) {
    struct Node* temp = currentDir->child;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0 && temp->isFile == 0) {
            return temp;  // Found the subdirectory
        }
        temp = temp->sibling;
    }

    printf("Directory '%s' not found.\n", name);
    return currentDir;  // Return the current directory if subdirectory not found
}

// Recursive function to delete a node (directory or file) and all its children
void deleteNode(struct Node* node) {
    if (node == NULL) return;

    // Recursively delete all children of the node (if directory)
    deleteNode(node->child);

    // Recursively delete siblings
    deleteNode(node->sibling);

    // Free the node
    printf("Deleting '%s'.\n", node->name);
    free(node);
}

// Function to delete a file or directory from the current directory
void deleteItem(struct Node* currentDir, char* name) {
    struct Node* temp = currentDir->child;
    struct Node* prev = NULL;

    // Search for the file or directory in the current directory
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                // First child to be deleted
                currentDir->child = temp->sibling;
            } else {
                // Middle or last child to be deleted
                prev->sibling = temp->sibling;
            }

            // Delete the node and its children (if directory)
            deleteNode(temp);
            printf("'%s' deleted successfully.\n", name);
            return;
        }

        prev = temp;
        temp = temp->sibling;
    }

    printf("Item '%s' not found in the current directory.\n", name);
}

int main() {
    // Root of the file system
    struct Node* root = createNode("root", 0);
    struct Node* currentDir = root;

    // Example operations on the file system
    createDirectory(currentDir, "Documents");
    createDirectory(currentDir, "Downloads");
    createFile(currentDir, "file1.txt");
    createFile(currentDir, "file2.txt");

    // List the current directory contents
    listDirectory(currentDir);

    // Change to Documents directory
    currentDir = changeDirectory(currentDir, "Documents");
    createFile(currentDir, "doc1.txt");
    createDirectory(currentDir, "Images");

    // List contents of Documents
    listDirectory(currentDir);

    // Go back to root
    currentDir = root;

    // Delete a file
    deleteItem(currentDir, "file1.txt");

    // List contents of root after deletion
    listDirectory(currentDir);

    // Cleanup memory by deleting the entire tree starting from the root
    deleteNode(root);

    return 0;
}
