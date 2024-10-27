#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

// Define the User struct (you may already have this in header.h)
// struct User {
//     int id;
//     char name[50];      // Use a fixed size for simplicity
//     char password[50];  // Use a fixed size for simplicity
// };

// Function to check if a username already exists in users.txt
int checkUniqueName(const char* name) {
    FILE *file = fopen(USERS, "r");
    if (!file) {
        printf("Error opening users.txt\n");
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
    scanf("%s", name);

    // Check if the username already exists
    if (checkUniqueName(name) == 0) {
        printf("Error: Username already exists. Registration failed.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);

    // Open the users.txt file for appending the new user
    FILE *file = fopen(USERS, "a+");
    if (!file) {
        printf("Error opening users.txt\n");
        return;
    }

    // Find the next available user ID
    int newId = 0;
    struct User u;
    while (fscanf(file, "%d %s %s", &u.id, u.name, u.password) != EOF) {
        newId = u.id + 1;  // Increment ID for new user
    }

    // Write the new user to the file
    fprintf(file, "%d %s %s\n", newId, name, password);

    printf("User %s registered successfully with ID %d.\n", name, newId);
    
    fclose(file);  // Close the file
}

// Existing loginMenu function
void loginMenu(char a[50], char pass[50]) {
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }

    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }
}

const char *getPassword(struct User u) {
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s", userChecker.name, userChecker.password) != EOF) {
        if (strcmp(userChecker.name, u.name) == 0) {
            fclose(fp);
            // Return a dynamically allocated copy of the password
            char *buff = malloc(strlen(userChecker.password) + 1);
            if (buff != NULL) {
                strcpy(buff, userChecker.password);
            }
            return buff;
        }
    }

    fclose(fp);
    return NULL;  // return NULL if no user found
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
//         case 2: {
//             char username[50];
//             char password[50];
//             loginMenu(username, password);  // Call login function
//             break;
//         }
//         default:
//             printf("Invalid option selected.\n");
//             break;
//     }

//     return 0;
// }
