/*aaary and find the invalid flags combinations for Open() system call.*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	int file_d;

	file_d = open("TEST.txt",O_RDWR | O_TRUNC , 0600 );

	if(file_d == -1){
		perror("file not exist here\n");
		exit(1);
	}

	else{
		printf("file present\n");
	
	}

	close(file_d);
	return 0;
}

