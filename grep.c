#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#include <sys/types.h> 
#include <sys/stat.h> 
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>

#include <dirent.h>
     
#include "header.h"

int main(int argc, char *argv[]) {
	int f[10];
	int size[10];
	int i = 0;
	char *a;	
	char nl[2] = "\n"; //Terminating character for tokenisation 
   	char *token;
	if(argc == 1) {
		printf("Use ./mygrep -h command for usage\n");
		exit(1);
	}
	else if(strcmp(argv[1],"-h") == 0 && argv[2] == NULL) {
		usage();
		exit(1);
	}
	if(argc < 3 && strcmp(argv[0], "./mygrep") != 0) {
		errno = EINVAL;
		perror("Bad arguments");
		return errno; 
	}
	
	//1) -r command	+ extra options : -ri and -rv
	
	if(strcmp(argv[1],"-r") == 0 || strcmp(argv[1], "-ri") == 0 || strcmp(argv[1], "-rv") == 0) {
		DIR *dir;
		char dir_name[50];
   		dir = opendir(argv[3]);
  		struct dirent *dirn;
  		if(dir!= NULL) {
  		
       			while((dirn = readdir(dir))) {
       			
				if(dirn->d_type == DT_DIR) {
				
					if(strcmp(dirn->d_name, ".") == 0 || strcmp(dirn->d_name, "..") == 0);
					
					else  {
					
						strcpy(dir_name, argv[3]);//copy directory name
						//concatenate dir_name to the path
						strcat(dir_name, "/");
						strcat(dir_name, dirn->d_name);
						
						/*check for the options
						* FLAG = 0 : -r   call recall 
						* FLAG = 1 : -ri  call recall
						* FLAG = 2 : -rv  call recall
						*/
						if(strcmp(argv[1], "-r") == 0)
							recall(dir_name, argv[2], 0);
						if(strcmp(argv[1], "-ri") == 0)
							recall(dir_name, argv[2], 1);
						if(strcmp(argv[1], "-rv") == 0)
							recall(dir_name, argv[2], 2);
					}
				}
				else if(f[i] = open( dirn->d_name,  O_RDONLY)) { 
					size[i] = lseek(f[i], 0, SEEK_END);
					
					a = (char*)malloc(size[i]*sizeof(char));
					lseek(f[i], 0, 0);	
					read(f[i], a, size[i]*sizeof(char));
					
   					token = get_token(a, nl, i);
   					
 					while( token != NULL ) { 
						if((mystrstr(token, argv[2]) != NULL && strcmp(argv[1], "-r") == 0)
						 ||(mystrstrcase(token, argv[2]) != NULL && strcmp(argv[1], "-ri")==0) 
						 ||(mystrstr(token, argv[2]) == NULL && strcmp(argv[1], "-rv") == 0) ) 							{
							printf("%s%s/%s%s:%s%s\n",
							MAGENTA, argv[3], dirn->d_name, CYN, NORMAL, token);
						}
						token = get_token(NULL, nl, i);
  	 				}
				close(f[i]);
				free (a);
				}
				i++;
			}
           		closedir(dir);
			return 0;
		}
		
		
		//To handle caeses without entering directory name
		else{
			for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++)  {
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = get_token(a, nl, i);
 			while( token != NULL ) { 
				if(mystrstr( token, argv[2]) != NULL) {
					if(argc < 4)
						printf("%s\n", token);
					else
						printf("%s%s %s: %s%s\n", MAGENTA, argv[i+2], CYN,  NORMAL, token);
				}
				token = get_token(NULL, nl, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
		}
	
	}
	
	
	//2) -i command + extra options : -in or -ni
	
	else if(strcmp(argv[1],"-i") == 0 || strcmp(argv[1],"-in") == 0 || strcmp(argv[1],"-ni") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = get_token(a, nl, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstrcase( token, argv[2]) != NULL) {
					if(strcmp(argv[1],"-in") == 0 || strcmp(argv[1],"-ni") == 0) {
						if(argc < 5){
							printf("%s%d%s:%s%s\n", GREEN, line_num, CYN, NORMAL, token);
						}	
						else{
							printf("%s%s %s: %s%d %s: %s%s\n", MAGENTA, argv[i+2], CYN, GREEN, line_num, CYN, NORMAL, token);
							}
					}
					else {
						if(argc < 5)
							printf("%s\n", token);
						else
							printf("%s%s %s: %s%s\n", MAGENTA, argv[i+2], CYN, NORMAL, token);
					}
				}
				token = get_token(NULL, nl, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	
	//3) -v command + extra options : -vn or -nv
	
	else if(strcmp(argv[1],"-v") == 0 || strcmp(argv[1],"-vn") == 0 || strcmp(argv[1],"-nv") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = get_token(a, nl, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstr( token, argv[2]) == NULL) {
					if(strcmp(argv[1],"-vn") == 0 || strcmp(argv[1],"-nv") == 0) {
						if(argc < 5)
							printf("%s%d%s:%s%s\n", GREEN, line_num, CYN, NORMAL, token);
						else
							printf("%s%s %s: %s%d %s: %s%s\n", MAGENTA, argv[i+2], CYN, GREEN, line_num, CYN, NORMAL, token);
					}
					else {
						if(argc < 5)
							printf("%s\n", token);
						else
							printf("%s%s %s: %s%s\n", MAGENTA, argv[i+2], CYN, NORMAL, token);
					}
				}
				token = get_token(NULL, nl, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	//4) -f command
	
	//5) -w command
	
	else if(strcmp(argv[1], "-w") == 0) {
                char *p;
                for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        token = get_token(a, nl, i);
                        while( token != NULL ) {
                                if(p = mystrstr(token, argv[2])) {
                                        if(isalpha(*(p - 1)) == 0 && isalpha(*(p + strlen(argv[2]))) == 0) {
                                                if(argc < 5)
                                                        printf("%s\n", token);
                                                else
                                                        printf("%s%s %s: %s%s\n", MAGENTA, argv[i+2], CYN, NORMAL, token);
                                        }
                                }
                                token = get_token(NULL, nl, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;

        }
	
	//6) -c command + extra options  : -cv or -vc
	
	else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-cv") == 0 || strcmp(argv[1], "-vc") == 0) {
		int count[10];
		for(i = 0; i < 10; i++)
			count[i] = 0;
			
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		
		for(i = 1; i <= 10; i++) {
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = get_token(a, nl, i);
   			
 			while( token != NULL ) { 
				if(strcmp(argv[1], "-c") == 0) {
					if(mystrstr( token, argv[2]) != NULL) {
						count[i-1]++;
					}
				}
				else {
					if(mystrstr( token, argv[2]) == NULL) {
						count[i-1]++;
					}
				}
				token = get_token(NULL, nl, i);
  	 		}
  	 		
			if(f[i] != -1) {
				if(argc < 5)
					printf("%d\n", count[i-1]);
				else
					printf("%s%s %s: %s%d\n", MAGENTA, argv[i+2], CYN, NORMAL, count[i-1]);
			}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	
	//7) -m command(color)
	
	else if(strncmp(argv[1], "-m", 2) == 0) {
		int count[10];
		int num = atoi(&argv[1][2]);
				
		if(num != 0){
			for(i = 0; i < 10; i++)
                        	count[i] = 0;
             		for(i = 1; i <= 10; i++) {
                        	f[i] = open(argv[i+2], O_RDONLY);
                        	size[i] = lseek(f[i], 0, SEEK_END);
                	}
                	for(i = 1; i <= 10; i++) {
                        	a = (char*)malloc(size[i]*sizeof(char));
                        	lseek(f[i], 0, 0);
                        	read(f[i], a, size[i]*sizeof(char));
                        	token = get_token(a, nl, i);
                        	while( token != NULL ) {
                        	        if(mystrstr( token, argv[2]) != NULL) {
						if(argc < 5)
                        	                        printf("%s\n", token);
                        	                else
                        	                        printf("%s%s %s: %s%s\n", MAGENTA, argv[i+2], CYN, NORMAL, token);

                        	                count[i-1]++;
						if(count[i-1] == num)
							break;
                        	        }
	                                token = get_token(NULL, nl, i);
        	                }
        	                close(f[i]);
        	                free (a);
        	        }
		}
		else
			printf("grep :invalid max count\n");
                
                
                return 0;

	}
	
	//8) -b command
	
	else if(strcmp(argv[1], "-b") == 0) {
                for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                
                for(i = 1; i <= 10; i++) {
                        int bytes = 0;
                        
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        
                        token = get_token(a, nl, i);
                        while( token != NULL ) {
                                if(mystrstr( token, argv[2]) != NULL) {
                                        if(argc < 5)
                                                printf("%s%d%s:%s%s\n", GREEN, bytes, CYN, NORMAL, token);
                                        else
                                                printf("%s%s %s: %s%d %s: %s%s\n",
                                                MAGENTA, argv[i+2], CYN, GREEN, bytes, CYN, NORMAL, token);
                                }
				bytes = bytes + strlen(token) + 1;
                                token = get_token(NULL, nl, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;
        }
	
	//9) -q command
	
	else if(strcmp(argv[1], "-q") == 0){
		exit(0);
	}
	
	//10) -H command & -h command
	
	else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-H") == 0 ) {
		for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                
                for(i = 1; i <= 10; i++) {
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);      
                        read(f[i], a, size[i]*sizeof(char));
                        
                        token = get_token(a, nl, i);
                        while( token != NULL ) { 
                                if(mystrstr(token, argv[2]) != NULL) {
                                        if(strcmp(argv[1], "-h") == 0)
                                                printf("%s\n", token);
                                        else
                                                printf("%s%s %s: %s%s\n", MAGENTA, argv[i+2],CYN , NORMAL, token);
                                }
                                token = get_token(NULL, nl, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;

	}
	
	//11) -n command
	
	else if(strcmp(argv[1], "-n") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
			
   			token = get_token(a, nl, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstr( token, argv[2]) != NULL) {
					if(argc < 5)
						printf("%s%d%s:%s%s\n", GREEN, line_num, CYN, NORMAL, token);
					else
						printf("%s%s %s: %s%d %s: %s%s\n", MAGENTA, argv[i+2], CYN, GREEN, line_num, CYN, NORMAL, token);
				}
				token = get_token(NULL, nl, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	
	//12) -l & -L command + extra options : -il or -li  & -iL or -Li
	
	else if(strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "-L") == 0
	 	|| strcmp(argv[1], "-il") == 0 || strcmp(argv[1], "-li") == 0
	 	|| strcmp(argv[1], "-iL") == 0 || strcmp(argv[1], "-Li") == 0) 
		{
		for(i = 1; i <= 10; i++) {
        	        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                
                for(i = 1; i <= 10; i++) {
			int FLAG = 0;
                
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                
                        token = get_token(a, nl, i);
                        
			if(strcmp(argv[1], "-Li") == 0 
			 || strcmp(argv[1], "-iL") == 0 
			 || strcmp(argv[1], "-li") == 0
			 || strcmp(argv[1], "-il") == 0) 
			 {
                        	while( token != NULL ) {
					//Assigning FLAG values to all the lines                        	
                                	if(mystrstrcase( token, argv[2]) != NULL) {
						FLAG = 1;
						break;
                                	}
                                	token = get_token(NULL, nl, i);
				}
				
				//combination of -l & -i command
				if(FLAG == 1 && (strcmp(argv[1], "-li") == 0 || strcmp(argv[1], "-il") == 0)) { 
                                	printf("%s%s\n", CYN, argv[i+2]);
				}
				//combination of -L & -i command
                                if(FLAG == 0 && (strcmp(argv[1], "-Li") == 0 || strcmp(argv[1], "-iL") == 0)) {
					if(argv[i+2] == NULL)
						break;
                                        printf("%s%s\n", CYN, argv[i+2]);
				}
			}
			
			else {
				while( token != NULL ) {
                                        if(mystrstr( token, argv[2]) != NULL) {
						FLAG = 1;
                                                break;
                                        }
                                        token = get_token(NULL, nl, i);
				}
                                if(strcmp(argv[1], "-l") == 0 && FLAG == 1) {
                                        printf("%s%s\n", CYN, argv[i+2]);
				}
                                if(strcmp(argv[1], "-L") == 0 && FLAG == 0) {
					if(argv[i+2] == NULL)
						break;
                                        printf("%s%s\n", CYN, argv[i+2]);
				}
			}
                        close(f[i]);
                        free (a);
                }
                return 0;

	}
	
	// normal pattern search
	else {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+1], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++)  {
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = get_token(a, nl, i);
 			while( token != NULL ) { 
				if(mystrstr( token, argv[1]) != NULL) {
					if(argc < 4)
						printf("%s\n", token);
					else
						printf("%s%s %s: %s%s\n", MAGENTA, argv[i+1], CYN,  NORMAL, token);
				}
				token = get_token(NULL, nl, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	return 0;
}
