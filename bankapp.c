#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Program to implement a simple banking application **********************
* Author                Dept.           Date            Notes
************************************************************************
* Tahseen T.            Comp. Science.  Mar 07 2020     Initial version.
* Tahseen T.            Comp. Science.  Mar 13 2020     Final version with all functions implemented.
*/
float balance = 0.0; // a variable storing the balance amount the accountholder has

int isAcc(FILE *f, char *a) { // a function which returns if the account exists and also updates the balance

        int acc = 0; // it's a switch which becomes 1 if the data is of a new account

        int exists = 0; // it's a switch which becomes 1 if the account input into the function exists

        char line[100]; // it's an array of characters which stores the data of each line dynamically

	while (fgets(line, 99, f)) { // read one line at a time

                int count = 0; // keep a count of the number of variables read

                char *cur = strtok(line, ","); // stores the current variable

                while (cur != NULL) { // loops through all the variables

                        count ++; // update the counter

                        if ( count == 1 && strcmp(cur,"AC") == 0) acc = 1; // checks if the first variable in the line is AC and update the variable acc

                        else if (count == 1 && strcmp(cur,"AC") != 0) acc = 0; // resets the variable if it's not a new account

                        if (acc && count == 2 && strcmp(cur,a) == 0) { // checks the second variable and sees if it is the accnum input and updates the variable exists

                          exists = 1;

                          break;

                        }

                        else if (count == 2 && strcmp(cur,a) != 0) { // break out of the loop if the accnum doesn't match

                          break;

                        }

                        else if (count == 4) { // update the balance of the input acc

                          balance+=atof(cur);

                        }

                        cur = strtok(0, ","); // gets the next variable

                }

        }

        return exists; // returns if the acc exists

}

void a(FILE *f, int c, char **v) { // the function which adds new accounts to the csv file

  if (c < 4) { // checks if there are sufficient arguments provided or else prints an error message

                fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n");

                fclose(f); // close the file

                exit(1); // exits the code with error code 1

                }

                else if (f != NULL) { // if the file is there, check if the account exists

                        if (isAcc(f, v[2])) {

                                fprintf(stderr, "Error, account number %s already exists\n", v[2]); // return an error if the account already exists

                                fclose(f); // close the file

                        	exit(50); // exit with the error code 50
			}
                        else {

                                fseek(f, 0, SEEK_END); // go to the end of the file to write

                                fprintf(f, "AC,%s,%s\n", v[2], v[3]); // write to the file

                                fclose(f); // close the file

                                exit(0); // exit the program

                        }

                }

}

void d(FILE *f, int c, char **v) { // the function which deposits an amount to the account and updates the csv file

  if (c < 5) { // checks if sufficient information is provided

			fprintf(stderr, "Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n"); // prints an error if sufficient information is not provided

      fclose(f); // close the file

			exit(1); // exit with an error code 1

		}

		else if (f != NULL) { // if the file exists

			if (isAcc(f, v[2])) { // checks if the account exists

				fseek(f, 0, SEEK_END); // goes to the end of the file

				fprintf(f, "TX,%s,%s,%s\n", v[2], v[3], v[4]); // writes the transaction down to the file

        fclose(f); // closes the file

				exit(0); // exit the program

			}

			else { // if the account does not exist

				fprintf(stderr, "Error, account number %s does not exists\n", v[2]); // don't let the transaction to pass through

        fclose(f); // close the file

				exit(50); // exit with error code 50

			}

		}

}

void w(FILE *f, int c, char **v) { // the function which withdraws a specified amount from an account

  if (c < 5) { // checks if sufficient information is provided

                        fprintf(stderr, "Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n"); // prints an error if sufficient information is not provided

                        fclose(f); // close the file

                	exit(1); // exit with error code 1

		}

		else if (f != NULL) { // if the file exists

			if (isAcc(f, v[2])) { // checks if the account exists

				if (balance >= atof(v[4])) { // if there is sufficient balance in the account

					fseek(f, 0, SEEK_END); // goes to the end of the file

					fprintf(f, "TX,%s,%s,-%s\n", v[2], v[3], v[4]); // writes the transaction down to the file

          fclose(f); // close the file

					exit(0); // exit the program

				}

				else { // if there isn't sufficient balance

					fprintf(stderr, "Error, account number %s has only %.2f\n", v[2], balance); // prints an error saying sufficient balance isn't there

          fclose(f); // close the file

					exit(60); // exit with error code 60

				}

			}

			else { // if the account does not exist

				fprintf(stderr, "Error, account number %s does not exists\n", v[2]); // prints an error saying the account does not exist

        fclose(f); // close the file

				exit(50); // exit with error code 50

			}

		}

}

int main(int argc, char **argv) {

        FILE *file = fopen("bankdata.csv", "r+"); // open the file in read and write mode

        if (argc == 1) { // if there is no input provided, return an error

                fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");

                fclose(file); // close the file

                exit(1); // exit the program

        }
        else if (argv[1][1] == 'a') { // if the input specifies -a

                a(file, argc, argv); // call the function which adds accounts

        }
	      else if (argv[1][1] == 'd') { // if the input specifies -d

                d(file, argc, argv); // call the function which deposits to an account

        }
	      else if (argv[1][1] == 'w') { // if the input specifies -w

                w(file, argc, argv); // call the function which withdraws from an account

		    }

	fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");  // if the file does not exist in the current directory, print an error saying that

	exit(100); // exit with error code 100

}
