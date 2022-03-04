
/* 
File name is linked_list_hospital.c
 Purpose: file contains functions for manipulating singly linked list
 
 Revisions
 Doron Nussbaum 2021

 
 
 
 
 Copyright 2021 Doron Nussbaum
 
 */

/******************************************************************/
// INCLUDE 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list_hospital.h"
#include "patient.h"


/************************************************************************/
// Define 



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
patient - the patient record

input/output
head - head of linked list

return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/

//function to insert node into linkedlist
ListNode *insertToList(ListNode **head, PatientInfo *patient)
{
	//initialized p node to null
	ListNode *p = NULL;


	//allocate memoryy for the new node.
    	p = (ListNode *) malloc(sizeof(ListNode));
    	
    	//error message if allocation went wrong
    	if(p == NULL) 
    	{
		printf("error: could not allocate memory for the array \n");
		return NULL;

    	}

	//assignment the patient data to the new node.
	p->patient = *patient;

	// Step 3 update the next field of the new node to point to the first node in the list as a next node
	p->next = *head;
	
	// Step 4 update the list head to point to the new node.
	*head = p;
	
	//return the new node
	return p;




}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node  

Input
input
patient - the patient record


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/

//function to insert a node after another
ListNode *insertAfter(ListNode *node, PatientInfo *patient)
{
	//if the node is null return null
	if(node == NULL)
	{
		return NULL;
	}
	
	//if the node is not null.
	else
	{
		//initialize the new node to null.
		ListNode *p = NULL;
		
		//allocate memory for the new node.
    		p = (ListNode *) malloc(sizeof(ListNode));
    		
    		//if the memory allocation went wrong error message.
    		if(p == NULL) 
    		{
			printf("error: could not allocate memory for the array \n");
			return NULL;

    		}

		//assign the patient data to the new node.
		p->patient = *patient;

		// Step 3 update the next field of the new node to point to the first node in the list as a next node
		p->next = node->next;
		
		node->next = p;
	
		// Step 4 update the list head to point to the new node.
		return p;
		
	}
 

}




/************************************************************************/
/*
Purpose: search for the first patient with the matching priority
Input
head - the head of the list
priority - first priority of the patient

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


ListNode * searchFirstPatientByPriority(ListNode *head, unsigned char priority, PatientInfo *patient)

{
	// add code 
   
   //if the list is empty return null.
   if(head == NULL)
   {
   	return NULL;
   }
   
   //if the list is not empty.
   else
   {
	//intialize node p to null
   	ListNode *p = NULL;
	
	//set node p equal to the head node.
	p = head;
	
	//while loop to traverse linkedlist and search for patient with matching priority.
	while(p != NULL)
	{
		//if the current node in the linked list has the same priority as the patient being searched for return the patient.
		if(p->patient.priorityLevel == priority)
		{
			//set patient equal to the current node's patient.
			*patient = p->patient;
			
			//return patient.
			return p;
		}
		
		//set current node equal to next to continue traversing list.
		p = p->next;
	}
	
   }


}

/************************************************************************/
/*
Purpose: search for the first patient with the matching criteria.  The criteria is determined
by the comparison function 
Input
head - the head of the list
findPatient -  a function pointer that returns a 0 if the patient's record matches that criteria

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


ListNode * searchNextPatient(ListNode *head, int (*findPatient)(PatientInfo *), PatientInfo *patient)
{
  //if list is empty return null.
  if(head == NULL)
  {
     return NULL;
  }
   
   //if the list is not empty.
   else
   {
   	//initialize node p to null.
	ListNode *p = NULL;
	
	//set node p equal to head node.
   	p = head;
	
	//while loop to traverse linkedlist.
	while(p != NULL)
	{
		//if current node's patient meets the criteria return it.
		if(findPatient(&p->patient) == 0)
		{
			//save patient data.
			*patient = p->patient;
			
			//return patient
			return p;
		}
		
		//move on
		else
		{
			//keep traversing linked list.
			p = p->next;
		}
	}
	
	return NULL;
   }
 


}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(ListNode **head, PatientInfo *patient)

{
    //initialize temporary node to keep track of the head and previous nodes.
    ListNode *p = *head, *prev;
 
    //if the current node is the one being searched for delete it.
    if(p != NULL && &p->patient == patient)
    {
    	//change head pointer
        *head = p->next; 
        
        //free memory from deleted node.
        free(p); 
        return 0;
    }
 
    //while loop to search for node to be deleted.
    while(p != NULL && &p->patient != patient)
    {
    	//keep track of previous node.
        prev = p;
        
        //continute to traverse linkedlist.
        p = p->next;
    }
 
    //if the patient wasnt found return 1
    if(p == NULL)
        return 1;
 
    //else if the node was found delete and free it and change pointers.
    prev->next = p->next;
 	
    //free memory from node.
    free(p);

}


/***************************************************************/

/*
Purpose: Retrieve the first node that matches the priority.  When found the node is deleted and the patient
information is provided. 

Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted  
1 if node was not found or list is empty 

*/


int retrieveNextPatientByPriority(ListNode **head, unsigned char priority, PatientInfo *patient)

{

    //keep track of return value
    int rc = 0;
    
    //store the patient being searched for in new node p.
    ListNode *p = searchFirstPatientByPriority(*head,priority, patient);

    //if the patient was found delete it from the list.
    if(p!= NULL)
    {
        //return 0 from deleting the patient from the linked list.
        return deleteFromList(head,&p->patient);

    }
    //return 1 if the patient was not found.
    return 1;
 
}

/***************************************************************/

/*
Purpose: Retrieve the patient with the highest criteria to be treated.  The maximum criteria is determined by 
a comparePatients function.  Once the patient is found it is deleted from the list and its information is 
returned. 

Input
head - the head of the list
comparePatients - this function takes two paitent records and compares them.  
				It returns, -1, 0 or 1 if p1 < p2, p1 == p2, or p1 > p2, respectively. 

output
head - the head of the list
patient - the patient record


return
0 if  patient was found and the node was deleted  
1 if no paitent was found or the list is empty 


Algorithm:
The function first finds the patient with the hights criteria by comparing all the patients records and 
finding the first patient with the maximum criteria to be treated.  It then deletes the patient and returns
its information. 
*/


int retrieveNextPatientByCriteria(ListNode **head, int (*comparePatients)(PatientInfo *p1, PatientInfo *p2, int currentTime), int currentTime, PatientInfo *patient)
{
	//set the max node equal to the head node.
	ListNode* max = *head;
	
	//set current node equal to the head node.
	ListNode* current = *head;
	
	//while loop to traverse linkedlist and find max criteria.
	while(current !=NULL)
	{
		//if the current node's next element is nulll return the max node.
		if(current->next == NULL)
		{
			//set patient equal to the max node.
			*patient = max->patient;
			
			//return the status from deleting the max node.
			return deleteFromList(head,&max->patient);
		}
		
		//if the current node's criteria is greater than the max criteria, replace the max criteria with the new max.
		if(comparePatients(&current->patient, &max->patient,currentTime) == 1)
		{
			//set max node equal to current node, since current node is greater.
			max = current;
		}
		
		//continue traversing linkedlist.
		current = current->next;
	}
	
	
}



/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(ListNode **head)
{
	// add code 
	//initialize nodes to help traverse linkedlist.
	ListNode *current = NULL;
	current = *head;
	ListNode *next = NULL;
	//iterate through the list
	while(current != NULL)
	{
		//set next to the current nodes next node
		next = current->next;
		//free the current node memory
		free(current);
		//set current next
		current = next;
	}
	//set head to null
	*head = NULL;


}



/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
myPrint - a function pointer for print the patient information. 
*/


void printList(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	// add code 
	//initialize node p equal to head node.
   	ListNode *p = NULL;
   	p = head;

	//iterate through the list
	while(p != NULL)
	{
		//print the patient.
		printPatient(&p->patient);
		
		//continue traversing linkedlist.
		p = p->next;
	}
	
 
}


/************************************************************************/
/*
Purpose: counts the number of patients that are waiting to be treted
input
head - the head of the list

return 
the number of registered patients

*/


int numPatientsInEmergency(ListNode *head)
{
	// add code 
	//count to keep track of num of patietns.
	int count = 0;
	//initialize node p equal to head node.
	ListNode *p = NULL;
	p = head;
	
	//while loop to count num of patients in linked list.
	while(p != NULL)
	{
		//add to count.
		count+=1;
		
		//continue traversing linkedlist.
		p = p->next;
	}
	
	//return the num of patietns.
	return count;
 

}

/************************************************************************/
/*
Purpose: counts the number of patients with a matching priority
input
head - the head of the list


return 
the number of patients with a matching priority


*/


int countPatients(ListNode *head, unsigned char priority)
{
	// add code 
	//count num of patients with matching priority.
	int count = 0;
	
	//initialize node p equal to head node.
	ListNode *p = NULL;
	p = head;
	
	//while loop to traverse and compare nodes to see if any have matching priority levels.
	while(p != NULL)
	{
		//if node has a matching priority add to the count
		if(memcmp(&p->patient.priorityLevel, &priority,1) == 0)
		{
			count+=1;
		}
		
		//continue traversing linkedlist.
		p = p->next;
	}
	
	//return count
	return count;
  
}



/************************************************************************/
/*

Purpose: store all the patients records in the file by printing out the information i.e., in ASCII readable format. 


input
filename - the name of the file to be used for storing the data
head - the head of the  list

Algorithm:
use the '$' character as a delimeter between the fields
For example:
Miya                 $Bronson                 $ 9700    $ 20  $ 2 $ Broken Bone 
*/

// Backup Functions
int createAsciiBackup(char *fileName, ListNode *head)

{	//initialize current node equal to head node.
	ListNode* current = head;
	
	//open file in write mode.
	FILE* fp = fopen(fileName, "w");
	
	//while loop to traverse linkedlist and print every node and its values into a text file.
	while (current != NULL)
	{
    		fprintf(fp,"%-20s $%-20s $ %7d $ %5d $ %3d  $ %s \n",current->patient.firstName,current->patient.familyName,current->patient.id,current->patient.arrivalTime,current->patient.priorityLevel,current->patient.medicalProblem);
    		current = current->next;
    		
	}
	
	//close file
	fclose(fp);

    return(0);
}

/************************************************************************/
/*

Purpose: store all the patients records in the file in their binary format. 


input
filename - the name of the file to be used for storing the data
head - the head of the  list



*/

int createBinaryBackup(char *fileName, ListNode *head)
{
	//intiailze current node equal to head node.
	ListNode* current = head;
	
	//open file in binary write mode.
	FILE* fp = fopen(fileName, "wb");
	
	//while loop to traverse linked list and write every node in binary format to the file.
	while (current != NULL)
	{
		//write node to file.
    		fwrite(&current->patient, sizeof(struct patientInfo), 1, fp);
    		
    		//continue traversing linkedlist.
    		current = current->next;
	}
	
	//close file.
	fclose(fp);


    return(0);


}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// BONUS SECTION



/************************************************************************/
/*

Purpose: removes all Patients with priority less than or equal to the given priority 
(remove all patients with priorityLevel <= priority).   


input
head - the head of the  list

Ouput
head - the head of the list where all patients with priorityLevel < priority are removed 

*/

int releasePatients(ListNode **head, unsigned char priority)

/* code */
{
	//initialzie node p equal to head node.
	ListNode *p = NULL;
	p = *head;
	// remove all patients that head is pointing to and meet the criteria
	while(p != NULL)
	{
		//if the node has a priority less than or equal to the current priority rremove it.
		if(p->patient.priorityLevel <= priority)
		{
			//deleting node.
			deleteFromList(head,&p->patient);
		}
		
		//continue traversing linkedlist.
		p = p->next;
	}


	// remove all other patients that meet the crieria
	return(0);

}

/************************************************************************/
/*
Purpose: prints all the patients' records in the list in reverse order using recursion

input
head - the head of the list
*/


void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	//initialzie node p equal to head node.
	ListNode *p = NULL;
   	p = head;

	//base case to sotp recursion.
 	if(p == NULL)
	{
		return;
	}
	
	//recursive call to print patients.
	printListReverse(p->next,printPatient);
	
	//print patient
	printPatient(&p->patient);
    
 
}





/*****************************************************************************/

/************************************************************************/
/*
Purpose: Reverse the list such that the last node in the list becomes the first node and the first node in the list becomes the last node.  

Restrictions:
1.	This operation must be achieved using recursive calls
2.	No memory is to be allocated or released at any time during the execution of the function



input
head - the head of the list


Returns:
the head of the new list
*/

ListNode *reverse(ListNode *head)
{
    //base case to stop recursion.
     if(head == NULL || head->next == NULL)
     {
     	return head;
     }
     
            
     //keeps track of subsequent snodes.
     ListNode* rest = reverse(head->next);
     
     //change pointers to reverse order.
     head->next->next = head;
        
     head->next = NULL;
     
     //return rest.
     return rest;
	

}




