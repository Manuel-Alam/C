

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "patient.h"

//Function prototypes
int morph(char *id, char *priorityLevel, char *medicalProblem);

int main(int argc, char *argv[])

{
    //initialize file name
    char* fileName = NULL;
   
   //initialize patient struct and 3 attributes from it.
    struct patientInfo p;
    char id[5];
    char priorityLevel[2];
    char medicalProblem[PROBLEM_LENGTH];
 
   //file name is equal to second arguement entered.
    fileName = argv[1];
    
    //if file name doesnt exist print error message.
    if(fileName == NULL)
    {
    	printf("usage singleAssessment fileName.\n");
    	
    	return -2;
    }
    
    //initialize file 
    FILE *file = NULL;
    
    //if the file isnt null when opened start morphing
    if((file = fopen(fileName,"rb"))!=NULL)
    {
    	    //variable to track morph return value.
	    int m;
	    
	    //read the patient from the binary file.
    	    fread(&p, sizeof(PatientInfo), 1, file);
    	    
    	    //close the file
            fclose(file);
            
            //print if the file name exists.
            printf("%s exists\n",fileName);
            
            //convert the data from the binary file to strings.
	    sprintf(id, "%d", p.id);
	    sprintf(priorityLevel, "%d", p.priorityLevel);
	    
	    //morph the patient.
	    m= morph(id, priorityLevel, p.medicalProblem);
	    
	    //print if morph failed
	    printf("%s %s %s\n", id, priorityLevel, p.medicalProblem);
	    
	    //return morphed value
	    return m;
	    

    }
    
    //if file name doesnt exist print error.
    else
    {
            printf("%s does not exist\n",fileName);
            
            return -3;
    }
 

    
    return 0;
	
}

//morph function
int morph(char *id, char *priorityLevel, char *medicalProblem)
{
	//store arugments.
        char *args[]={"./drAssessment", id, priorityLevel, medicalProblem, NULL};
	
	return 	execvp(args[0], args);
}

