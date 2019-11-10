run : grep.o get_token.o mystrstr.o mystrstrcase.o dir.o usage.o 
	gcc -Wall -o mygrep *.o
	
grep : grep.c header.h
	gcc -c grep.c
	
tok : get_token.c header.h
	gcc -c get_token.c 
	
str : mystrstr.c mystrstrcase.c header.h
	gcc -c mystrstr.c mystrstrcase.c
	
dir : dir.c header.h
	gcc -c dir.c
	
usage : usage.c header.h
	gcc -c usage.c
		
clean :
	rm *.o
