# ATM-System-Management

### Overview

The ATM System Management project is a simple console-based application that allows users to manage their bank accounts. This system enables users to create accounts, transfer ownership, check balances, and more. The project demonstrates fundamental concepts in C programming, including file handling, data structures, and user input validation.
#### Key Features

1. User Registration and Login
        Users can create accounts by registering their personal information.
        A login system allows registered users to access their accounts securely.

2. Account Management
        Users can create multiple accounts linked to their profiles.
        Each account maintains details such as account number, balance, and account holder information.

3. Transfer of Account Ownership
        Users can transfer ownership of their accounts to other registered users.
        The transfer process checks if the user has accounts and validates the new owner's existence.

4. Balance Inquiry
        Users can view their account balances to manage their finances effectively.

5. Transaction History
        Users can check their transaction history to track deposits, withdrawals, and transfers.

6.  File Storage
        All user and account data is stored in text files, ensuring persistence even after the program terminates.

 ## How to Run the Program

To run the ATM System Management application, follow these steps:
Prerequisites

   - C Compiler: Ensure you have a C compiler installed (e.g., GCC).
  -  Text Editor/IDE: Use a text editor (e.g., VSCode, Notepad++) or an Integrated Development Environment (IDE) to modify the source code.  
1. Open a terminal or command prompt.

2. Navigate to the project directory:    
```bash
 cd path/to/atm-system
```

###  Compile the Program:

To compile the program and generate the executable atm, simply run:

```bash

make
```
This command will trigger the Makefile to compile the object files listed under $(objects) (which are main.o, system.o, auth.o), and then link them into the final executable named atm.
###  Run the Program:

Once the compilation completes successfully, you should see the atm executable in your current directory. You can run the program with the following command:

```bash

./atm-sytsem
```
This should start the ATM management system and display its command-line interface.
### Clean Up (Optional):

If you want to remove the compiled object files (to start fresh or free up space), you can run:

```bash

make clean
```
This will delete the object files (main.o, system.o, auth.o, etc.) but leave the atm executable intact.

### User Interaction

- Follow the on-screen instructions to register, log in, create accounts, transfer ownership, and check balances.
- All user inputs will be taken through the console.

### Key Functionality
#### User Registration

The user registration process collects the following information:

    Name
    Username
    Password

Users are prompted to enter their details, and if successful, their information is saved in the records.txt file.

#### User Login

Registered users can log in using their username and password. The system checks the credentials against the stored data.

#### Creating an Account

Once logged in, users can create a new account, which is assigned a unique account number and initialized with a zero balance.

#### Transferring Account Ownership

Users can transfer ownership of their accounts by specifying the account number and the new owner's username. The system verifies that the account exists and that the new user is registered.

#### Checking Balances

Users can inquire about their account balances by entering their account number. The system retrieves and displays the current balance.

#### Viewing Transaction History

The system keeps a record of transactions. Users can view their transaction history to track changes to their accounts.

### Conclusion

This ATM System Management project provides a practical example of how to manage user accounts and transactions in a simple console application. It serves as an educational tool for beginners looking to learn about file handling, data structures, and basic programming concepts in C.

Feel free to explore and modify the code to fit your learning needs!

### Author

This project was developed by Your Name.

### Contributions

Contributions are welcome! If you would like to contribute to this project, please fork the repository and submit a pull request with your changes.

#### How to Contribute

1. Fork the project.
2. Create a new branch for your feature or bug fix.
3.  Commit your changes.
4.  Push your changes to your forked repository.
5.  Open a pull request explaining your changes.

### License

This project is licensed under the MIT License. See the LICENSE file for more details.
