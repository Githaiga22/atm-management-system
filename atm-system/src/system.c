#include "header.h"

const char *RECORDS = "./data/records.txt";

// Function to read an account from the file
int getAccountFromFile(FILE *pf, char *userName, struct Record *r) {
    int result = fscanf(pf, "%d %s %d/%d/%d %s %d %lf %s",
                        &r->accountNbr, userName,
                        &r->deposit.month, &r->deposit.day, &r->deposit.year,
                        r->country, &r->phone, &r->amount, r->accountType);
    
    if (result == EOF) {
        return 0; // End of file reached
    } else if (result != 9) {
        printf("Error reading account from file.\n");
        return 0; // Failed to read properly
    }

    printf("Read account: %d (user: %s)\n", r->accountNbr, userName); // DEBUGGING PRINT
    return 1;
}

// Function to save an account to the file
void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

// Function for invalid input handling
void stayOrReturn(int notGood, void f(struct User u), struct User u) {
  int option;
  do {
    if (notGood == 0) {
      printf("\n\t\tEnter 0 to try again, 1 to return to main menu and 2 to "
             "exit! \n\n");
    } else {
      printf("\n\t\tEnter 1 to go to the main menu and 0 to exit! \n\n");
    }

    scanf("%d", &option);

    if (option == 0) {
      f(u);
      break;
    } else if (option == 1) {
      mainMenu(u);
      break;
    } else if (option == 2) {
      exit(0);
    } else {
      printf("Insert a valid operation!\n");
    }
  } while (option < 0 || option > 2);
}
// Function to display success message
void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

// Function to create a new account
void createNewAcc(struct User u)
{
    struct Record r;
    char userName[50];
    struct Record cr;
    FILE *pf = fopen(RECORDS, "a+");
    if (!pf) {
        printf("Error opening records file.\n");
        return;
    }

    while (1) {
        system("clear");
        printf("\t\t\t===== New record =====\n");
        printf("\nEnter today's date(mm/dd/yyyy):");
        if (scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year) != 3) {
            printf("Invalid date format. Please try again.\n");
            continue;
        }

        printf("\nEnter the account number:");
        if (scanf("%d", &r.accountNbr) != 1) {
            printf("Invalid account number. Please try again.\n");
            continue;
        }

        printf("Account number entered: %d\n", r.accountNbr);

        // Reset the file pointer to the beginning of the file
        rewind(pf);

        // Check for duplicate accounts
        int duplicateFound = 0;
        printf("Checking for duplicates...\n");

        while (getAccountFromFile(pf, userName, &cr)) {
            printf("Comparing entered account number: %d with read account number: %d\n", r.accountNbr, cr.accountNbr);
            if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr) {
                printf("✖ This Account already exists for this user\n\n");
                duplicateFound = 1;
                break;
            }
        }

        if (duplicateFound) {
            printf("Duplicate found, try again...\n");
            fclose(pf);
            continue;
        }

        printf("No duplicates found, proceeding...\n");

        // Prompt for other account details
        printf("\nEnter the country:");
        scanf("%s", r.country);
        printf("\nEnter the phone number:");
        scanf("%d", &r.phone);
        printf("\nEnter amount to deposit: $");
        scanf("%lf", &r.amount);
        printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
        scanf("%s", r.accountType);

        saveAccountToFile(pf, u, r);
        fclose(pf);
        success(u);
        break;
    }
}


// Function to check all accounts
void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");
    if (!pf) {
        printf("Error opening records file.\n");
        return; // Handle error appropriately
    }

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}
