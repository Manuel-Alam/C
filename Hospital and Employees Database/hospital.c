

#include "stdio.h"
#include "stdlib.h"
#include "struct.h"
#include "string.h"
#include "populateRecords.h"
#include "populateRecords.c"
#include "patient.h"
#include "employee.h"
#include "employee.c"
#include "patient.c"

#define NUM_RECORDS 20

//initialize method prototypes.
int menu();
int quit();

//main to execute the code
int main(int argc, char *argv[])
{
  
    //intialize struct person arrayy to null
    struct person *personArr = NULL;
    int numRecords = 0;// number of records to be created
    char rc = 0;
    
    //gets the value from the command line
    if(argc == 2)
    {
    	    numRecords = atoi(argv[1]);
    }
    
    //if no value is assigned one is requested.
    else
    {
    	// add code to get the number of records to be created
    	printf("Enter the number of records to be created:  \n");
    	scanf("%d", &numRecords);
    }
    
    //allocated memory for the array oof persons based on the number of records to be created.
    personArr = (struct person *) malloc(sizeof(struct person) * numRecords);

    //if the person array is still null than the memory was not allocated properly.
    if(personArr == NULL) 
    {
	printf("error: could not allocate memory for the array \n");
	return(1);
    }

    //populate the array of persons with the number of records to be created for each person.
    populateRecords(personArr,numRecords);
    
    //menu option and quit value option.
    int menuOption;
    int quitValue = 0;
    
    //do while loop to keep displaying the menu after each input.
    do
    {
    	//menu option is equal to the return value from the menu() method which retrieves the input the user gave.
    	menuOption = menu();
    	//displays the output.
    	getchar();
    	
    	//switch case statement to determine what happens after each case is selected.
    	switch(menuOption)
    	{
    		//if 1 is inputted all the employees wil be printed.
    		case 1: printEmployees(personArr, numRecords);

    			getchar();
    			break;
    		
    		//if 2 is inputted the option to search for a family name will be given and each patient with the same family name will be printed.
    		case 2: searchPatients(personArr, numRecords);
			getchar();
    			break;
    		
    		//if 3 is inputted a summary of all employee data will be printed.
    		case 3: printEmployeesSummary(personArr, numRecords);

    			getchar();
    			break;
    		
    		//if 4 is inputted a summary of all patient data will be printed.
    		case 4:	printPatientSummary(personArr, numRecords);

    			getchar();
    		      	break;
    		
    		//if 5 is inputted the size of all structures will be printed.
    		case 5: printf("\nSize of PersonRec: %ld",sizeof(PersonRec));
    		       	printf("\nSize of PatientRec: %ld",sizeof(PatientRec));
    			printf("\nSize of EmployeeRec: %ld\n",sizeof(EmployeeRec));

    			getchar();
    			break;
    		
    		//if 0 is inputted an option to exit will be given
    		case 0:quitValue = quit();
			
			//if the user quits all the memory will be freed from the person array.
    			if(quitValue == 1)
    			{
    				free(personArr);
    			}

    			break;
    		
    	}
    }
    //while quit value is 0 menu display will keep looping
    while(quitValue == 0);
    

    
    return 0;
}

//menu method to display options for user to select.
int menu()
{	
	//option for user to input.
	int option;
	
	//clears the consoles previous commands
	system("clear");
	
	//char choice array.
	char choice[100];
	
	//do while loop to make sure user enters correct input.
	do
	{
	//prints the menu and options available.
	printf("\n\n MENU: \n\n 1. Print all employees \n\n 2. Search for all patients by Family Name \n\n 3. Summary of Employees Data \n\n 4. Summary of Patients data \n\n 5. Size of structures(PersonRec, PatientRec and EmployeeRec) \n\n 0. Quit \n\n");
	
	//prints message to enter input
	printf("\nEnter input: ") ;
	
	//stores the data of the input value.
	scanf("%s", choice);
	option = atoi(choice);
	
	//if the input is invalid user will be prompted to enter a valid value;
	if(option > 5 || option < 0 || strlen(choice) > 1)
	{
		printf("\n Option is not valid, press a key to restart.");
		getchar();
		getchar();
		system("clear");
	}
	}
	while(option > 5 || option < 0 || strlen(choice) > 1);
	
	//returns the input of the user.
	return option;
}

//quit function 
int quit()
{
	//store the value entered for quit.
	char quitVal[10];
	printf("Are you sure you want to exit the program? (y/n)");
	scanf("%s",quitVal);
	getchar();
	
	//if the quit value equals y the method will return 1 and exit the program in the menu method.
	if(strcmp(quitVal,"y") == 0 || strcmp(quitVal,"Y") == 0)
	{
		return 1;
	}
	
	//if the quit equals n the method will return 0 and stay in the program.
	if(strcmp(quitVal,"n") == 0 || strcmp(quitVal,"N") == 0)
	{
		return 0;
	}

}



