#define NORMAL 	 "\x1B[0m"
#define RED  	 "\x1B[31m"
#define GREEN    "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE     "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYN      "\x1B[36m"
#define WHITE    "\x1B[37m"


void usage();

void recall(char *, char *, int);

char *mystrstr (char *, char *);
char *mystrstrcase (char *, char *);

char *get_token (char *, char *, int);
