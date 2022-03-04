#include "employee.h"
#include "stdio.h"

//this function prints an employee and its data.
void printEmployee(PersonRec person)

{
    //char array to store the name of employee.
    char nameString[NAME_SIZE*2];
    // add code
    
    //print the employees name
    sprintf(nameString,"%s %s",person.firstName, person.familyName);
    
    //print the data that belongs to the employee.
    printf("%-33s dept: %d  salary: %.2f  position: %d  years of service: %d  salary to-date: %.2f\n",nameString,person.emp.department, person.emp.salary, person.emp.position, person.emp.yearsService, person.emp.salary);

}

//prints all the employees in the person array
void printEmployees(PersonRec *person, int numRecords)
{
    //prints header
    printf("\nHospital Employees\n");
    
    //for loop to print every employee in the array
    for(int i = 0; i < numRecords;i++)
    {
    	//if the ith index of the person array is an employee, the employees data will be printed.
    	if(person[i].emplyeeOrPatient == EMPLOYEE_TYPE)
    	{
    		printEmployee(person[i]);
    	}
    }

    // add code

}

//prints summary of employee data
void printEmployeesSummary(PersonRec *person, int numRecords)
{
	//intialized variables to 0 to keep track of data
	int count = 0;
	float total = 0;
	float average = 0;
	
	//print header
	printf("\nEmployee Summary");
	
	//for loop to get the data of each employee and add it to the overall data.
	for(int i = 0; i < numRecords;i++)
	{
		//if the person is an employee their data will be added to the overall summary of employee data.
		if(person[i].emplyeeOrPatient == EMPLOYEE_TYPE)
    		{
    			//increment the number of employes and the total salary.
    			count++;
    			total+= person[i].emp.salary;
    		}
	
	
	}
	
	//if theres > 0 employees the average will be calcualted.
	if(count != 0)
	{
		average = total / count;
	}
	
	//print the summary of employee data.
	printf("\nTotal number of employees: %d  total salary: %.2f  average salary: %.2f\n", count, total, average);
	
	//for loop to print the overall data for each position at the hospital
	for(int j = 0; j < MAX_POSITIONS;j++)
	{
		//reset variables to 0 each time a new position begins.
		count = 0;
		total = 0;
		average = 0;
		
		//for loop to to store position data.
		for(int k = 0; k < numRecords;k++)
		{
			//if the person is an employee and they work in the current position, their data will be added.
			if(person[k].emplyeeOrPatient == EMPLOYEE_TYPE && person[k].emp.position == j)
    			{
    				//increment the numbber of employees in this position and their salary.
    				count+=1;
    				total+= person[k].emp.salary;
    			}
		}
		
		//if count > 0 then the average salary will be calculated for that position.
		if(count != 0)
		{
			average = total / count;
		}
		
		//print the summary of the position and employee data.
		printf("\nposition[%d]-employees: %d  total salary: %.2f  average salary: %.2f\n", j,count, total, average);
	}
	

}
