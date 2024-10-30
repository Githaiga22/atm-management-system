#include "header.h"
#include <termios.h>

#define MAX_USERNAME_SIZE 50
#define MAX_PASSWORD_SIZE 50
#define MAX_ID_SIZE 5

char *USERS = "./data/users.txt";
// The loginMenu function handles the login process for a user. It prompts the user for their username and password, using a technique to hide the password input.
void loginMenu(char a[MAX_USERNAME_SIZE], char pass[MAX_PASSWORD_SIZE]) {
  struct termios oflags, nflags;

  system("clear");
  printf("\n\n\t\tBank Management System\n\n\t\tUser Login: ");
  scanf("%s", a);

  // Password Input with Hidden Characters
  tcgetattr(fileno(stdin), &oflags);     // Get current terminal settings
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;   // Disable echo for hidden input
  nflags.c_lflag |= ECHONL;     // Enable newline after input

  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
  printf("\n\t\tEnter the password: ");
  scanf("%s", pass);

  // restore terminal
  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
};
// This function retrieves the password for a given user from the users.txt file to verify the login.
const char *getPassword(struct User u) {
  FILE *fp;
  struct User userChecker;
  char id[MAX_ID_SIZE];

  if ((fp = fopen("./data/users.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }

  while (fscanf(fp, "%s %s %s", id, userChecker.name, userChecker.password) !=
         EOF) {
    if (strcmp(userChecker.name, u.name) == 0) {
      fclose(fp);
      u.id = atoi(id);
      char *buff = userChecker.password;
      return buff;
    }
  }

  fclose(fp);
  return "no user found";
}
// This function checks if a username already exists in users.txt, which is useful during user registration.
int isUsernameUnique(char username[]) {
  FILE *fp;
  struct User userChecker;

  if ((fp = fopen("./data/users.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }

  while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name,
                userChecker.password) != EOF) {
    if (strcmp(userChecker.name, username) == 0) {
      fclose(fp);
      return 0;
    }
  }
  fclose(fp);
  return 1;
}

/*
registerMenu function handles the user registration process in this application, managing input collection,
 security for password entry, and file operations for storing user data
 */
void registerMenu(char a[MAX_USERNAME_SIZE], char pass[MAX_PASSWORD_SIZE]) {
  struct termios oflags, nflags;

  do {
    system("clear");
    printf("\n\n\t\tBank Management System\n\n\t\t  User Registration\n");
    printf("\n\n\t\tEnter Username: ");
    scanf("%s", a);

    if (!isUsernameUnique(a)) {
      system("clear");
      printf("\n\n\t\tBank Management System\n\n\t\t  User Registration\n");
      printf("\n\t\tUsername already exists. \n");
      handleFailedRegistration(a, pass);
    }
  } while (!isUsernameUnique(a));

  // Password Input with Hidden Characters
  tcgetattr(fileno(stdin), &oflags); // Get current terminal settings
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;     // Disable echo for hidden input
  nflags.c_lflag |= ECHONL;   // Enable newline after input

  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
    perror("tcsetattr");
    exit(1);
  }
  printf("\n\t\tEnter Password: ");
  scanf("%s", pass);

  // restore terminal
  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
    perror("tcsetattr");
    exit(1);
  }
//  File Operations to Store User Data
  FILE *fp;
  struct User userChecker;
  char id[MAX_ID_SIZE];
  int lastUserID = 0;

  if ((fp = fopen("./data/users.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }

  while (fscanf(fp, "%s %s %s", id, userChecker.name, userChecker.password) !=
         EOF) {
    lastUserID = atoi(id);
  }

  fclose(fp);

  if ((fp = fopen("./data/users.txt", "a")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }

  lastUserID++;

  fprintf(fp, "%d %s %s\n", lastUserID, a, pass);

  fclose(fp);
}
// This function provides options for retrying or exiting after a failed login attempt.
void handleFailedLogin(struct User *u) {
  int option;
  do {
    printf("\n\t\tEnter 0 to try again, 1 to exit! \n\n");
    scanf("%d", &option);

    if (option == 0) {
      initMenu(u);
      break;
    } else if (option == 1) {
      exit(1);
      break;
    } else {
      printf("Insert a valid operation!\n");
    }
  } while (option < 0 || option > 1);
}
// this function provides options for retrying or exiting if the username entered during registration already exists.
void handleFailedRegistration(char a[MAX_USERNAME_SIZE],
                              char pass[MAX_PASSWORD_SIZE]) {
  int option;
  do {
    printf("\n\t\tEnter 0 to try again, 1 to exit!\n\n");
    scanf("%d", &option);
    if (option == 0) {
      registerMenu(a, pass);
      break;
    } else if (option == 1) {
      exit(1);
      break;
    } else {
      printf("\t\tInsert a valid operation!\n");
    }
  } while (option < 0 || option > 1);
}