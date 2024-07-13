/*Create 5 children processes from a common parent and ensure that the
parent terminates after cleaning all the terminated children using waitpid().
The waitpid() must be called after all the children are created
and the parent has completed its work real work,if any. You must interpret
the exit code of the cleaned­up processes, using waitpid(), in parent process
– you must cover all the possible scenarios !!!
Hints : a) refer to fork2n.c and related samples
b) as per fork2n.c, you can modify certain children processes
to execute, in a while loop and others can normally terminate
c) you can use kill ­SIGKILL <pid> to terminate children
processes forcibly/abnormally
d) as always, use ps and top commands to check the status of
processes*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int ret;
	int i =0 ,status;

	//create 5 child using fork system call
	while(i++<5){
	 ret = fork();
		if(ret < 0){
			printf("No process excecuted\n");
			printf("The final value of i is %d\n",i);
			exit(1);
		       }
		if(ret == 0){
			printf("\n I am  in child process:\n");
			printf("The child %d ppid is %d and pid is %d \n",i,getppid(),getpid());
			break;
		}
		if(ret > 0){
			printf("\n I am in parent process:\n");
			printf("My parent ppid is %d and pid is %d\n",getppid(),getpid());
			continue;
		}

               }
	if(ret>0){
		while(1){
			ret = waitpid(-1,&status,0);

			if(ret > 0){
				if(WIFEXITED(status))
			        	{
						if(WEXITSTATUS(status) == 1)
						{
							printf("normal and successful termination of %d\n",ret);
						}
						else
						{
							printf("Normal and unsuccessful of pid %d\n",ret);
						}
					}
				        else{
						printf("Abnormal and unsuccessful pid %d\n",ret);
					    }

		                         }
			                if(ret < 0){
						exit(0);
				         	}
	                        	}
		                  }
	                  printf("All child process terminated successfully and exit from child process\n");
			  return 0;
		}








