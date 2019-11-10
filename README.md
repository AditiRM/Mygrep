# Mygrep  

DSA MINI PROJECT !
Aditi Medhane 
111803177

Implementation of Grep commands[Global Regulation Expression Print]

Aim: To search a file for a prticular string. 

**REFERENCE TO VARIOUS FUNCTIONS**
		
					
* The Program uses get_token and mystrstr functions to find the pattern and print the lines containing the pattern.

* get_token divides the file content into single lines and seearches for the pattern.

* mystrstr searches for the pattern and then prints the line if the pattern is found.

* Various options implemented are shown in ./mygrep -h. 

* -r option which traverses through directories.
  It is implemented in dir.c. dirent.h is used to do so.
  mystrstrcase function ignores case to search pattern.
	
  For more reference to command line options read GREP_DSAP.txt


