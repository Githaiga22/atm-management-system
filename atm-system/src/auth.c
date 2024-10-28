#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <bcrypt.h>
#include "header.h"

char *USERS = "./data/users.txt";

// Define the User struct
struct User {
    int id;
    char name[50];
    char password[60]; // Increased size for hashed passwords
};

// Function to check if a username already exists in users.txt
int checkUniqueName(const char* name) {
    FILE *file = fopen(USERS, "r");
    if (!file) {
        perror("Error opening users.txt");
        return -1;
    }

    struct User u;
    while (fscanf(file, "%d %s %s", &u.id, u.name, u.password) != EOF) {
        if (strcmp(u.name, name) == 0) {
            fclose(file);
            return 0;  // Name already exists
        }
    }
    fclose(file);
    return 1;  // Name is unique
}

// Function to register a new user
void registerUser() {
    char name[50];
    char password[50];
    
    printf("Enter username: ");
    scanf("%49s", name); // Limit input size for security

    // Check if the username already exists
    if (checkUniqueName(name) == 0) {
        printf("Error: Username already exists. Registration failed.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%49s", password); // Limit input size for security

    // Hash the password
    char hashedPassword[60];
    bcrypt_gensalt(12, hashedPassword); // Generate a salt for hashing
    bcrypt_hashpw(password, hashedPassword); // Hash the password

    // Open the users.txt file for appending the new user
    FILE *file = fopen(USERS, "a+");
    if (!file) {
        perror("Error opening users.txt");
        return;
    }

    // Find the next available user ID
    int newId = 0;
    struct User u;
    while (fscanf(file, "%d %s %s", &u.id, u.name, u.password) != EOF) {
        newId = u.id + 1;  // Increment ID for new user
    }

    // Write the new user to the file
    fprintf(file, "%d %s %s\n", newId, name, hashedPassword);

    printf("User %s registered successfully with ID %d.\n", name, newId);
    
    fclose(file);  // Close the file
}

// Function to handle user login
int loginUser(const char* username, const char* password) {
    FILE *file = fopen(USERS, "r");
    if (!file) {
        perror("Error opening users.txt");
        return -1;
    }

    struct User userChecker;
    while (fscanf(file, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
        if (strcmp(userChecker.name, username) == 0) {
            fclose(file);
            // Check the hashed password
            if (bcrypt_checkpw(password, userChecker.password) == 0) {
                printf("Login successful! Welcome, %s.\n", username);
                return 1; // Successful login
            } else {
                printf("Error: Incorrect password.\n");
                return 0; // Incorrect password
            }
        }
    }

    fclose(file);
    printf("Error: User not found.\n");
    return 0; // User not found
}

// Function to handle user input for login
void loginMenu() {
    char username[50];
    char password[50];

    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    printf("\n\nEnter username: ");
    scanf("%49s", username); // Limit input size for security

    // Disable echo for password input
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }

    printf("\nEnter password: ");
    scanf("%49s", password); // Limit input size for security

    // Restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }

    // Attempt to login
    loginUser(username, password);
}

// Main function to test registration and login
// int main() {
//     int choice;
//     printf("1. Register\n2. Login\nChoose an option: ");
//     scanf("%d", &choice);

//     switch (choice) {
//         case 1:
//             registerUser();  // Call register function
//             break;
//         case 2:
//             loginMenu();     // Call login function
//             break;
//         default:
//             printf("Invalid option selected.\n");
//             break;
//     }

//     return 0;
// }
