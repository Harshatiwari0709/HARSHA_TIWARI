/*Using file I/O , Open a .txt file (if present already) ,create it if it is not already present. Check whether
the file has opened successfully or not. Close it. (Write necessarry observations and flags usage)*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	

	int f_d;
	char filename1[200] ="/home/diot/Desktop/Linux_Assignments/Assignment2_HARSHA-20240602T071611Z-001" ;
	char filename[100];
	printf("Enter the  filename= ");
	scanf("%s",filename);
	strcat(filename1,filename);
	printf("%s\n",filename1);
	f_d = open(filename1, O_WRONLY,0600);

	if(f_d < 0){
		perror("File is not present\n");
		f_d = open(filename1, O_CREAT | O_WRONLY,0600);
		if(f_d < 0)
		{
			perror("can't create\n");
			exit(1);
		}
		else{
			printf("Create successfully file\n");
		}


	}
	else {

		printf("present\n");
		exit(1);
	}
	
	
		close(f_d);

	return 0;
}
