# ATM-System-Management
### 1. Compile the Program:

To compile the program and generate the executable atm, simply run:

```bash

make
```
This command will trigger the Makefile to compile the object files listed under $(objects) (which are main.o, system.o, auth.o), and then link them into the final executable named atm.
### 2. Run the Program:

Once the compilation completes successfully, you should see the atm executable in your current directory. You can run the program with the following command:

```bash

./atm
```
This should start the ATM management system and display its command-line interface.
### 3. Clean Up (Optional):

If you want to remove the compiled object files (to start fresh or free up space), you can run:

```bash

make clean
```
This will delete the object files (main.o, system.o, auth.o, etc.) but leave the atm executable intact.