
/*

File receive.c


Purpose: simulate the receiveing end of a message over the network.  

The program converts a message encodded as an array of short integers into characters.
The input message uses 1-bit error correction code.
As part of the simulation, the program also corrects any 1-bit errors in the receiving message.


Revision:
a. Initial code - Doron Nussbaum


*/


/************************************************************************/

// INCLUDE FILES

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "bit_manipulation.h"
#include "bit_manipulation.c"


/************************************************************************/
//MACROS  / DEFINES



#define XSTR(A) STR(A)
#define STR(A) #A
#define MAX_INPUT_LENGTH 8192
#define MAX_MSG_LENGTH 2048
#define P1_MASK 0xaa8   // 0b0101010101000
#define P2_MASK 0xcc8	// 0b0110011001000
#define P4_MASK 0x10e0	// 0b1000011100000
#define P8_MASK 0x1e00  // 0b1111000000000


/************************************************************************/
// FUNCTION PROTOTYPES


void short2Char(short encodedChar, char *c);
void correctCode(short *num);
void readEncodedMessage(short *buf, int len, int *numRead);
//int correctCodeHelper(int mask, int sum, short *num ,int storedParity, int countingBits, int bitNumber, int parity, int parityPos);




/**************************************************************************/

int main(int argc, char *argv[])

{
	int rc = 0;		// return code

	char s[MAX_MSG_LENGTH] = { '\0' };  // message
	short encodedMsg[MAX_MSG_LENGTH];
	int numRead = 0;  // number of characters in the message
	int i;

	// read the message
	printf("Enter the transmitted message: ");
	readEncodedMessage(encodedMsg, MAX_MSG_LENGTH, &numRead);



	// print the corrected message
	printf("\n\n Transmitted Message:\n");
	for (i = 0; i < numRead; i++) 
	{
		char c;
		short2Char(encodedMsg[i], &c);
		printf("%c", c);
    }
    printf("\n");

    // correct the message
	for (i = 0; i < numRead; i++) {
		correctCode(&encodedMsg[i]);
	}



	// print the corrected message
	printf("\n\n Corrected Transmitted Message:\n");
	for (i = 0; i < numRead; i++) {
		char c;
		short2Char(encodedMsg[i], &c);
		printf("%c", c);
	}
	printf("\n");

	return(0);
}


/***********************************************************************************/
/* reads a message from the user

input
len - maximum length of mesage that should be read

output
receivedMsg - contains the message
numRead - the number of characters in the message

Asumption: 
function does not do any error checking of the input.  It expects to receive 
a sequence of positive short integers.

*/


void readEncodedMessage(short *receivedMsg, int len, int *numRead)
{
	int i;
	int rc;
	char s[MAX_INPUT_LENGTH+1];
	char *token = NULL;
	*numRead = 0;

	s[MAX_INPUT_LENGTH] = '\0';
	scanf("%"XSTR(MAX_INPUT_LENGTH)"[^\n]s", s);
	token = strtok(s, " ");

	for (i = 0; token != NULL  &&  i < len;token = strtok(NULL, " "), i++) {
		rc = sscanf(token, "%hd", &receivedMsg[i]);
	}

	*numRead = i; // set the number of read integers

    // empty the input buffer
    for( ; getchar() != '\n'; );


}




/*************************************************************************/
/* assign bits 3,5,6,7,9,10,11,12 of a integer to bits 0-7 of a char

input
encodedNum - a short integer 

output
*c - the modified char that is embedded in encodedNum

return:
none

comment:
this is the "inverse" of the function char2Short in the transmit program

*/


void short2Char(short encodedNum, char *c)

{
	short mask = 0x0001;
	int i;
	int bitSet;

	
	*c = 0;		// initialize *c
 
 	//traverse byte
	for (i = 0; i < 8; i++) 
	{
		// switch case for each bit 
		switch(i) 
		{
			case 0:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 3);
			if (bitSet) 
			{
				//set the bit at char c
				setCharBit(i, c);
			}
			break;
			case 1:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 5);
			if (bitSet) 
			{
				//set the bit at char c
				setCharBit(i, c);
			}
			break;
			case 2:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 6);
			if (bitSet) 
			{
				//set the bit at char c
				setCharBit(i, c);
			}
			break;
			case 3:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 7);
			if (bitSet) 
			{
				//set the bit at char c
				setCharBit(i, c);
			}
					
			break;
			case 4:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 9);
			if (bitSet) 
			{
				//set the bit at char c
				setCharBit(i, c);
			}
			break;
			case 5:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 10);
			if (bitSet) 
			{
				// set the bit at char c
				setCharBit(i, c);
			}
			break;
			case 6:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 11);
			if (bitSet) 
			{
				// set the bit at char c
				setCharBit(i, c);
			}
			break;
			case 7:
			//if the bit at i is set, set the bit at char c
			bitSet = isShortBitSet(encodedNum, 12);
			if (bitSet) 
			{
				// set the bit at char c
				setCharBit(i, c);
			}
			break;
			default:
			printf("This should not happen !!!!\n");
			assert(0);
		}
		
		
		
	}
}


/*************************************************************************************/


/* purpose:
performs error corrrections, if needed on the short integer

The function checks the parity bits for error and see if thre is a discrepancy between 
the transmitted parity bits and the computed parity bits for the received number.  
If there is a decrepancy then it finds the bit number that was flipped.

If there is an error then it fixes it.

input
num - the address of the short number 

output:
*num - the modified number
*/


void correctCode(short *num)

{
	int mask;
	int sum;
	int bitNumber = 0; //  bit number with the error bit
	int parity;		// a parity bit either 0 or 1
	int storedParity; // the parity bit in the encoded char
	int countB; // number of bits 
	//int parityPos;
	
    	
	
	//set mask to P1_MASK
	mask = P1_MASK;
	
	//store the parity of the number with parity bit P1 
	storedParity = isShortBitSet((*num), 1);
	
	//expose only the bits that are related to parity bit using the mask
	sum = (*num) & mask;
	
	//count the number of set bits in the number.
	countB = countBits(sum);
	
	//if the number of set bits is odd set the parity to 1.
	if(countB % 2 == 1) 
	{
		parity = 1;
	}
	
	//if the number of set bits is even set the partiy to 0.
	else 
	{
		parity = 0;
	}

	//if the stored parity and newly computed parity are are different add 2^0 to bitNumber
	if(storedParity != parity) 
	{
		bitNumber += 1;
	}

	//set mask to P2_MASK
	mask = P2_MASK;
	
	//store the parity of the number with parity bit P2
	storedParity = isShortBitSet((*num), 2);
	
	//expose only the bits that are related to parity bit using the mask
	sum = (*num) & mask;
	
	//count the number of set bits in the number.
	countB = countBits(sum);
	
	//if the number of set bits is odd set the parity to 1.
	if(countB % 2 == 1) 
	{
		parity = 1;
	}
	
	//if the number of set bits is even set the partiy to 0.
	else 
	{
		parity = 0;
	}

	//if the stored parity and newly computed parity are are different add 2^1 to bitNumber
	if(storedParity != parity) 
	{
		bitNumber += 2;
	}
	
	//set mask to P4_MASK
	mask = P4_MASK;
	
	//store the parity of the number with parity bit P4 
	storedParity = isShortBitSet((*num), 4);
	
	//expose only the bits that are related to parity bit using the mask
	sum = (*num) & mask;
	
	//count the number of set bits in the number.
	countB = countBits(sum);
	
	//if the number of set bits is odd set the parity to 1.
	if(countB % 2 == 1) 
	{
		parity = 1;
	}
	
	//if the number of set bits is even set the partiy to 0.
	else 
	{
		parity = 0;
	}

	//if the stored parity and newly computed parity are are different add 2^2 to bitNumber
	if(storedParity != parity) 
	{
		bitNumber += 4;
	}
	
	//set mask to P8_MASK
	mask = P8_MASK;
	
	//store the parity of the number with parity bit P8 
	storedParity = isShortBitSet((*num), 8);
	
	//expose only the bits that are related to parity bit using the mask
	sum = (*num) & mask;
	
	//count the number of set bits in the number.
	countB = countBits(sum);
	
	//if the number of set bits is odd set the parity to 1.
	if(countB % 2 == 1) 
	{
		parity = 1;
	}
	
	//if the number of set bits is even set the partiy to 0.
	else 
	{
		parity = 0;
	}

	//if the stored parity and newly computed parity are are different add 2^3 to bitNumber
	if(storedParity != parity) 
	{
		bitNumber += 8;
	}
	
	// if bitNumber != 0 then flip the bit at position bitNumber (use xor operator)
	if(bitNumber != 0) 
	{
  		flipBitShort(bitNumber, num);
  	}

	
}
/*
int correctCodeHelper(int m, int sum, short *num ,int storedParity, int countingBits, int bitNumber, int parity, int parityPos)
{
	int mask = m;
	storedParity = isShortBitSet((*num), parityPos);
	sum = (*num) & mask;
	countingBits = countBits(sum);

	if(countingBits % 2 == 1) 
	{
		parity = 1;
	}
	
	else 
	{
		parity = 0;
	}

	if(storedParity != parity) 
	{
		bitNumber += parityPos;
	}

}
*/

