#include <stdio.h>
#include <stdlib.h>

// Define the structure of a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Search for a value in inorder sequence and return its index
int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive function to build the binary tree from inorder and preorder traversals
struct Node* buildTree(int inorder[], int preorder[], int inorderStart, int inorderEnd, int* preorderIndex) {
    // Base case
    if (inorderStart > inorderEnd) {
        return NULL;
    }

    // The next element in preorder is the root of the current subtree
    int rootValue = preorder[*preorderIndex];
    (*preorderIndex)++;  // Move to the next element in preorder sequence

    // Create the root node
    struct Node* root = createNode(rootValue);

    // If this node has no children (leaf node)
    if (inorderStart == inorderEnd) {
        return root;
    }

    // Find the index of the root in inorder sequence
    int inorderIndex = search(inorder, inorderStart, inorderEnd, rootValue);

    // Recursively construct the left and right subtrees
    root->left = buildTree(inorder, preorder, inorderStart, inorderIndex - 1, preorderIndex);
    root->right = buildTree(inorder, preorder, inorderIndex + 1, inorderEnd, preorderIndex);

    return root;
}

// Function to print the inorder traversal of the tree
void inorderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Function to print the preorder traversal of the tree
void preorderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main() {
    // Sample inorder and preorder sequences
    int inorder[] = {9, 3, 15, 20, 7};
    int preorder[] = {3, 9, 20, 15, 7};
    int n = sizeof(inorder) / sizeof(inorder[0]);
    
    // Initialize preorder index to 0
    int preorderIndex = 0;

    // Build the tree
    struct Node* root = buildTree(inorder, preorder, 0, n - 1, &preorderIndex);

    // Print the inorder and preorder traversals of the constructed tree
    printf("Inorder traversal of the constructed tree: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal of the constructed tree: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
