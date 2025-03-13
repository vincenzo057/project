#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

int search(struct Node* root, int key) {
    if (root == NULL)
        return 0;
    if (root->data == key)
        return 1;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

void displayGuesses(struct Node* root) {
    if (root != NULL) {
        displayGuesses(root->left);
        printf("%d ", root->data);
        displayGuesses(root->right);
    }
}

void playGame() {
    srand(time(0));
    int number = rand() % 100 + 1; 
    int guess, attempts = 0;
    struct Node* root = NULL;

    printf("\n=== Welcome to the Number Guessing Game! ===\n");
    printf("Try to guess the number between 1 and 100.\n");

    while (1) {
        printf("\nEnter your guess: ");
        scanf("%d", &guess);

        if (search(root, guess)) {
            printf("You've already guessed %d! Try a different number.\n", guess);
            continue;
        }

        root = insert(root, guess);
        attempts++;

        if (guess == number) {
            printf("Congratulations! You guessed the correct number %d in %d attempts!\n", number, attempts);
            break;
        } else if (guess < number) {
            printf("Too low! Try a higher number.\n");
        } else {
            printf("Too high! Try a lower number.\n");
        }

        printf("Your previous guesses: ");
        displayGuesses(root);
        printf("\n");
    }
}

int main() {
    playGame();
    return 0;
}
