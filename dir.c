#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include "header.h"
#include <string.h>
void recall(char *dir_name, char *search, int FLAG) {
	int f[10] ;    //array of file descriptors to open maximum 10 files in the directory
	int size[10]; //to store the size of whole file into bytes using lseek
	int  i = 0;
	char *a;	
	char nl[2] = "\n";
	
   	char *token;
   	//open the directory again
		DIR *dir;
   		dir = opendir(dir_name);
  		struct dirent *dirn;
  		if(dir!=NULL) {
       			while((dirn = readdir(dir))) {
				if(dirn->d_type == DT_DIR) {
					if(strcmp(dirn->d_name, ".") == 0 || strcmp(dirn->d_name, "..") == 0); 
					else  {
                                        	strcat(dir_name, "/");
                                                strcat(dir_name, dirn->d_name);
						if(FLAG == 0)
                                                	recall(dir_name, search, 0);
						else if(FLAG == 1)
                                                	recall(dir_name, search, 1);
						else if(FLAG == 2)
                                                	recall(dir_name, search, 2);
                                        }
				}
				else if(f[i] = open(dirn->d_name, O_RDONLY)) { 
					size[i] = lseek(f[i], 0, SEEK_END);
					
					a = (char*)malloc(size[i]*sizeof(char));
					lseek(f[i], 0, 0);	
					read(f[i], a, size[i]*sizeof(char));
   					
   					token = strtok(a, nl);
 					while( token != NULL ) { 
						if((mystrstr( token, search) != NULL && FLAG == 0) 
						|| (mystrstrcase(token, search) != NULL && FLAG == 1) 
						|| (mystrstr(token, search) == NULL && FLAG == 2))
						{
							printf("%s%s/%s%s:%s%s\n",
							CYN, dir_name, dirn->d_name,MAGENTA, NORMAL, token);
						}
						token = strtok(NULL, nl);
   					}
				close(f[i]);
				free (a);
				}
			i++;
			}
           		closedir(dir);
		}	
}
