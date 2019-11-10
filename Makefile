run : grep.o get_token.o mystrstr.o mystrstrcase.o dir.o usage.o 
	gcc -Wall -o mygrep *.o
	
clean :
	rm *.o	

usage : usage.c header.h
	gcc -c usage.c
		
grep : grep.c header.h
	gcc -c grep.c
	
token : get_token.c header.h
	gcc -c get_token.c 
	
strstr : mystrstr.c mystrstrcase.c header.h
	gcc -c mystrstr.c mystrstrcase.c
	
dir : dir.c header.h
	gcc -c dir.c
	


