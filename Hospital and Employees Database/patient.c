

#include "string.h"
#include "stdio.h"
#include "patient.h"

/********************************************************************/
//method to print the data of a patient.
void printPatient(PersonRec person)

{
	
    // add code 
    //store the name of the patient.
    char nameString[NAME_SIZE*2];
    // add code
    //prints the name of the patient.
    sprintf(nameString,"%s %s",person.firstName, person.familyName);
    
    //prints the data of the patient
    printf("%-33s dept: %d  daily cost: %d  days in hospital: %d  severity: %d \n",nameString,person.patient.department, person.patient.dailyCost, person.patient.numDaysInHospital, person.patient.severity);

}

/********************************************************************/
//prints every patient in the person array.
void printPatients(PersonRec *person, int numRecords)
{

    // add code 
    //print header.
    printf("\nHospital Paitents\n");
    
    //for loop to print every patient in the array.
    for(int i = 0; i < numRecords;i++)
    {
    	//if the person is a patient print their data.
    	if(person[i].emplyeeOrPatient == PATIENT_TYPE)
    	{
    		printPatient(person[i]);
    	}
    }

}

//prints the summary of all patient data.
/********************************************************************/
void printPatientSummary(PersonRec *person, int numRecords)
{
	//initialize all the patient data summary to 0.
	int count = 0;
	float total = 0;
	float average = 0;
	float totalDaily =0;
	
	printf("\nPatient Summary");
	
	//for each patient in the array add their data to the overall data of all patients.
	for(int i = 0; i < numRecords;i++)
	{
		//if person is a patient their data will be added to the summary of patient data.
		if(person[i].emplyeeOrPatient == PATIENT_TYPE)
    		{
    			//increment the number of patients.
    			count++;
    			
    			//increment the total daily cost of patients.
    			total+= (person[i].patient.dailyCost *person[i].patient.numDaysInHospital);
    		}
	
	
	}
	
	//if the count > 0 then the average will be calculated.
	if(count != 0)
	{
		average = total / count;
	}
	
	//print the summary of patient data.
	printf("\nTotal number of patients: %d  total cost-to-date: %.2f  average cost per patient to-date: %.2f\n", count, total, average);
	
	//print the overall patient data of each department.
	for(int j = 1; j <= MAX_DEPARTMENTS;j++)
	{
		//reset values to 0 for each new department.
		count = 0;
		total = 0;
		average = 0;
		totalDaily = 0;
		
		//for each person in a specific department add their data to the overall department data.
		for(int k = 0; k < numRecords;k++)
		{
			//if the person is a patien and their in the current department add their data to the summary.
			if(person[k].emplyeeOrPatient == PATIENT_TYPE && person[k].patient.department== j)
    			{
    				//increment count
    				count+=1;
    				//daily cost to date.
    				total+= (person[k].patient.dailyCost *person[k].patient.numDaysInHospital);
    				//daily totasl cost
    				totalDaily += person[k].patient.dailyCost;
    				
    			}
		}
		
		//if the count > 0 average will be calculated.
		if(count != 0)
		{
			average = total / count;
		}
		
		//print the patient for specific department.
		printf("\ndepartment[%d]-patients: %d  cost to-date: %.2f  daily cost: %.2f  average daily cost per patient: %.2f\n", j,count, total, totalDaily, average);
	}

}


/********************************************************************/
//search for a patient with a specific family name
void searchPatients(PersonRec *person, int numRecords)
{
    //store the family name to be searched for
    char familyName1[NAME_SIZE];
    printf("Enter a family name to search for:");
    scanf("%s",familyName1);
    // add code 
    
    //traverse the array to find each patient with the same family name being searched for.
    for(int i = 0; i < numRecords;i++)
    {
    	//if the person's family name is the same as the one being looked for
	if(strcmp(person[i].familyName,familyName1) == 0)
	{
		//if the person is patient print their data.
		if(person[i].emplyeeOrPatient == PATIENT_TYPE)
		{
			printPatient(person[i]);
		
		}

	}
	
    }
    getchar();
    
	
}


