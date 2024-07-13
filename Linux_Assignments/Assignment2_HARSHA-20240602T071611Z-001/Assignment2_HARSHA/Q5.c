/*Write a C program to Open a file in appropriate mode and write the user entered contents into it.*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

	int filed;
	char data[100];
	ssize_t w_r;

	filed = open("harsha.txt",O_WRONLY,0600);

	if(filed == -1){
		perror("file not present");
		exit(1);
	}

	else{
		printf("Enter data into the file= ");
		scanf("%[^\n]s",data);
		w_r = write(filed,data,strlen(data));

		if(w_r == -1){
			perror("data has not been writtren\n");
			exit(1);
		}
		else{
			printf("data has written\n");
		}
	}
	
	close(filed);
	
	return 0;
}
