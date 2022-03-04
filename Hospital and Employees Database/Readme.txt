Purpose: the purpose of this software is to be able to observe and manage a patient/employee "database" for a hospital.
Developer: Manuel Alam 
Date: Nov 2, 2021
Organisation: This software is organised into seperate files with each file containing seperate logic for functions related to that file.
For example, all the functions related to hospital are contained in the hospital.c file and similarly for the employee.c and patient.c. Functions that are common between
both patients and employees are stored in the populateRecords.c file. Structures, functions and values that need to be shared across files are included in the header
file for each type of file. For example, the struct.h file which creates the structures for the program, shares them across the entire program. 
Functions related to the patient,employee,hospital, and populateRecords are listed in their respective header files.

Instructions:
to compile: "gcc -o hospital hospital.c"
To run: "./hospital" user will be prompted to enter number of records
             OR
        "./hospital [value]" [value] being the number of records ex: ./hospital 37

issues/limitations: Names can't be more than 15 chars.

This program has 6 options:

1. Print all employees.		
2. Search for all patients by Family Name
3. Summary of Employees Data
4. Summary of Patients Data
5. Size of structures(PersonRec, PatientRec and EmployeeRec)
0. Quit

For example, when selecting input 1, all the employees will be printed and to continue back the menu display just press the enter key.
This applies for all inputs except for input 2 and 0 because you actually want to enter valid input so the program performs the action correctly.



