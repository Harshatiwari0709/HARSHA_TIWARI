/*Open a file in append mode and try to write the contents multiple times in the same file and check if
the previous data is lost.*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
	
	int fd;
	char data[100];
	ssize_t wr;

	fd = open("TEST1.txt", O_APPEND | O_WRONLY , 0600);
	if(fd == -1){
		perror("File not exist");
		exit(1);
	}
	else{
		printf("Enter the data= ");
		scanf("%[^\n]s",data);
		wr = write(fd,data,strlen(data));

		if(wr == -1){
			perror("data not append here\n");
			exit(1);
		}

		else{
			printf("data append here\n");
		}
	}
	
	close(fd);
	
	return 0;
}

