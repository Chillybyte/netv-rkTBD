/* Comments - On the logger up here
 * Malthe, David, Morten og Emil
 * 
 * Program is compiled and working on a linux mint with gcc compiler
 * Must run the program as super user with sudo, for root access to access devices.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

// Variables
char toWrite[256];


// Methods
void writeToLog();
void clearLog();
int open_port();

// Program - Emil, Malthe
int main(int argc, char *argv[])
{
	/* 	//Test to write to file 
	strncpy(toWrite, "bob\n", 256);
	writeToLog();
		// clear log removes input
	clearLog();
	*/

	while(1==1) {
		int n = read(open_port(), toWrite, sizeof toWrite);
		writeToLog();
	}

	return 0;
}


// Methods Deklaration
// Emil
void writeToLog(){
	// Appends to the file with string toWrite.
	FILE *f = fopen("log.txt", "a");
	if (f == NULL)
	{
    	printf("Vi kunne ikke aabne slut filen log.txt\n");
    	exit(1);
	}
	printf("Vi skrev til log.txt wup wup\n");
	fprintf(f, "Input from USB-port: %s\n", toWrite);
}

// Emil
void clearLog(){
	// Clears the log by creating a empty file
	FILE *f = fopen("log.txt", "w");
	if (f == NULL)
	{
    	printf("Vi fejlede i at clear log.txt\n");
    	exit(1);
	}
}

// Malthe, Emil
// Source: http://www.cmrr.umn.edu/~strupp/serial.html
int open_port()
{
	int fd; /* File descriptor for the port */

	fd = open("/dev/tty0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		// Could not open the port.
		perror("open_port: Unable to open /dev/ttyf1 - ");
	}
	else fcntl(fd, F_SETFL, 0);

	return (fd);
}