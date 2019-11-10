#include "header.h"
#include <stdio.h>

void usage () {
	printf("Usage:\n./mygrep [OPTION] PATTERN [FILE]...\n Search for PATTERN in each FILE\n\n");
	printf("  -r       traverse through directories and grep\n");
	printf("  -ri      traverse through directories and grep ignoring case distinctions\n");
	printf("  -rv      traverse through directories and select non matching lines\n\n");
	
	printf("  -i       ignore case distinctions\n");
	printf("  -in/-ni  ignore case distinctions & print line number with output lines\n\n");
	
	printf("  -v       select non-matching lines\n");
	printf("  -vn/-nv  select non-matching lines & print line number with output lines\n\n");
	
	printf("  -w       force PATTERN to match only whole words\n\n");	
	
	printf("  -c       print only a count of matching lines per FILE\n");
	printf("  -cv/-vc  print only a count of non-matching lines per FILE\n\n");
	
	printf("  -m[NUM]  stop after NUM matches\n");
	printf("  -b       print the byte offset with output lines\n");
	printf("  -h       suppress the file name prefix on output\n");
	printf("  -q       (Quiete) do  not  write  anything to standard output\n");
	printf("  -H       print the file name for each match\n");
	
	printf("  -n       print line number with output lines\n\n");
	
	printf("  -l       print only names of FILEs containing matches \n");
	printf("  -il/-li  ignore case distinctions & print name of files contaning matches\n\n");
	
	printf("  -L       print only names of FILEs containing no match \n");
	printf("  -iL/-Li  ignore case distinctions & print name of files contaning no match\n\n");
	
}

