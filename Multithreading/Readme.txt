Purpose: the purpose of this software is to be able to to determine wheter a patient should be hospitailzed or not.
Developer: Manuel Alam 
Date: Dec 5, 2021
Organisation: This software is organized into seperate files each building on the logic of a previous file.
For example, singleAssessment.c, singleSpawn.c, and multiSpawn.c contain the same logic with minor differences to add on to previous logic created.


issues/limitations: None that I am aware of.


Instructions:
To compile each .c file use their respective Makefile.

To compile & run singleAssessment.c:

	Type make -f Makefile1
	
	This will create the executable singleMorph
	
	Type ./singleMorph patient.bin to run and test whether the current file exist.
	
	The program will take several seconds to produce the output.
	
	A message should appear saying whether the file exist or not.

To compile & run singleSpawn.c:

	Type make -f Makefile2
	
	This will create the executable singleSpawn
	
	Type ./singleSpawn patient.bin to run and test whether the current file exist.
	
        A message should appear saying whether the file exist or not.
        
        The program will take several seconds to produce the output.
        
        Another message should appear saying if the patient should be hospitalized for x days.
	
To compile & run multiSpawn.c:

	Type make -f Makefile3
	
	This will create the executable multiSpawn
	
	Type ./multiSpawn patient.bin to run and test whether the current file exist.
	
	The program will take several seconds to produce the output.
	
	A message should appear saying if the patient should be hospitalized for x days.
	
