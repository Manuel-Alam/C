Purpose: the purpose of this software is to be able to observe and manage a patient "database" for a hospital.
Developer: Manuel Alam 
Date: Nov 20, 2021
Organisation: This software is organised into seperate files with each file containing seperate logic for functions related to that file.
For example, all the functions related to adjusting the position of patients in the hospital data base are stored in the linked_list_hospital.c file.
Similarily, all the functions related to adjusting the attributes of each patient are stored in the patient.c file. Both patients and hospital share
similarites between their .h files which create the attributes for each patient and hospital struct.

Instructions:
to compile: "gcc emergencyRoomMain.c"
To run: "./a.out" 
        
issues/limitations: Program does contain memory leaks.

All bonus functions that were coded:
1. Saving to an Ascii file 
int createAsciiBackup(char *fileName, ListNode *head)

2. Saving to a Binary file
int createBinaryBackup(char *fileName, ListNode *head)

3. Reversing a list 
ListNode *reverse(ListNode *head)

4. releasing patients with low priority
int releasePatients(ListNode **head, unsigned char priority)


5. print the list of patients in reverse order
void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient))


