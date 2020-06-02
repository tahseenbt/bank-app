# A Banking System Application

A C program, bankapp.c to implement a simple banking application. The application provides three capabilities: (i) Add an account number, (ii) Make a deposit, (iii) Make a withdrawal. All of your banking data is stored in a CSV file bankdata.csv.

There are two kinds of records in this CSV file. (i) Account records, indicated by AC in the first field, followed by a 4 digit account number, followed by the name of the account holder (max 30 characters long). (ii) Then there are transaction records that are indicated by TX in the first field, followed by the account number, transaction date in YYYY-MM-DD format, followed by the amount of money deposited or withdrawn (negative values for the latter).
