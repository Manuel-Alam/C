

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "patient.h"
#include "sys/wait.h"
int morph(char *id, char *priorityLevel, char *medicalProblem);
int main(int argc, char *argv[])

{
        //initialize file name
    char* fileName = NULL;
    
   //initialize patient and attributes.
    struct patientInfo p[10];
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
    if((file = fopen(fileName,"rb"))!=NULL)
    {
	    //read the 10 patients from the binary file.
    	    fread(&p, sizeof(PatientInfo), 10, file);
    	    
    	    //close the file
            fclose(file);
            
            //initialize process array to store 10 patients.
            int process[10];
            int status = 0;
            
            //for loop to create child process for each patient
            for(int i = 0; i < 10; i++)
            {
            	//child process.
            	int child = fork();
            	int m;
            	
            	//if the ccurrent process is a child 
            	if(child == 0)
            	{
            	//print if the file name exists.
            	 //printf("%s exists\n",fileName);
            	 
            	 //convert the data from the binary file to strings.
	    	 sprintf(id, "%d", p[i].id);
	   	 sprintf(priorityLevel, "%d", p[i].priorityLevel);
	          
	          //morph the patient.
	    	  m = morph(id, priorityLevel, p[i].medicalProblem);
	    	
	    	//print if morph failed
	   	 printf("%s %s %s\n", id, priorityLevel, p[i].medicalProblem);
	     
	         //return morphed value
	    	 return m;
            	}
            	
            	//set the current process to the current child in the processIds array.
            	process[i] = child;
            	
            
            }
            
            //for loop to print whether each patient needs to be hospitalized (10)
            for(int i = 0; i < 10; i++)
            {
                //initialize child pid .
            	int cpid = waitpid(-1, &status, 0);
		
		//if not ready to exit
        	if (WEXITSTATUS(status) != 0)
        	{

            		int index = 0;
            		
            		//check if any child process has the same cchild pid.
            		for (int j = 0; j < 10; j++)
            		{
            			//exit if any process in array has the same child pid
                		if (process[j] == cpid)
                		{
                    			index = j;
                    			break;
                		}	
            		}
            //print the hospitalzation days.
            printf("Patient %s %s id (%d) requires %d hospitalization days\n", p[index].firstName, p[index].familyName, p[index].id, WEXITSTATUS(status));
                }
            }
            
          
            return status;
           

    }
    else
    {
            printf("%s does not exist\n",fileName);
            
            return -3;
    }
 

    
    return 0;
	
}

//morph funcction
int morph(char *id, char *priorityLevel, char *medicalProblem)
{
        char *args[]={"./drAssessment", id, priorityLevel, medicalProblem, NULL};
	
	return 	execvp(args[0], args);
}

