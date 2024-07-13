/*Create 5 processes from a common parent and ensure that the parent
terminates after cleaning all the terminated children using waitpid().
The waitpid() must be called after all the children are created
and the parent has completed its work real work,if any; in addition, you must
compile 5 different program files to in children processes to generate their
respective object files ; the parent process must use waitpid() to collect the
termination status of children processes – based on the exit code information
generated by children processes, link all the object files to
generate the final, linked program/application. In addition, the generated
binary executable must be loaded in a new process, if the linking is
successful !!! Hint – refer to assgn1_4.c*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>

int main(){

int ret, flag_unsuccessful = 0, flag_abnormal = 0;
int i = 0,status;

//create 5 child using fork system call
// for(i=0; i<5; i++)
while(i<5){

ret = fork(); // create child for the parent by using fork system call

if(ret < 0){
printf("No process exceuted\n");
printf("The final value of i is %d\n",i);
exit(1);
}

if(ret > 0){
printf("\nI am in parent process: \n");
printf("My parent ppid is %d  and pid is %d\n",getppid(),getpid());
// continue;
// exit(1);
}

if(ret == 0)
{
printf("\nI am in child process: \n");
printf("The child %d ppid  is %d and pid is %d \n",i,getppid(),getpid());
if(i == 0){
//printf("i = %d\n",i);
//execl is used to launch any process and remove the current proces
//Launch the pdf reader
printf("************ Add *******************\n");
//execl("/usr/bin/evince","evince","MasteringSTM32-1.pdf",NULL);
execl("/usr/bin/gcc","gcc","-c","add.c","-o","add.o",NULL);



}

else if(i == 1){
//printf("i = %d\n",i);
//Launch ques1.c file
printf("************ Sub  *******************\n");
execl("/usr/bin/gcc","gcc","-c","sub.c","-o","sub.o",NULL);



}

else if(i == 2){
//Launch ques2.c file
printf("************ Mult *******************\n");
execl("/usr/bin/gcc","gcc","-c","mult.c","-o","mult.o",NULL);



}

else if(i == 3) {
//Launch hello.txt file
printf("************ Div *******************\n");
//execl("/usr/bin/vim","vim","hello.txt",NULL);
execl("/usr/bin/gcc","gcc","-c","div.c","-o","div.o",NULL);



}

else if(i == 4){
printf("************ ls *******************\n");
//execl("/usr/bin/ls","ls","-a",NULL);
execl("/usr/bin/gcc","gcc","-c","main.c","-o","main.o",NULL);



}

else
{
break;
}

//break;
}


i++;
}

//wait for the termination of child
if(ret > 0){
for(i = 0; i < 5; i++){
ret = waitpid(-1,&status,0);

//child process terminated
if(ret > 0){
if(WIFEXITED(status)) //check if the process terminated normally
{

if(WIFEXITED(status) == 0)
{
printf("normal and successful termination of %d\n", ret);
}
else{
flag_unsuccessful = 1;
printf("Normal and unsuccessful of pid %d\n",ret);
}
}

else{
flag_abnormal = 1;
printf("Abnormal and unsuccessful pid %d\n", ret);
}
}

if(ret < 0){

if(flag_unsuccessful || flag_abnormal){
printf("Error compiling an files\n");
exit(1);
}
else{
break;
}
}
}
}

ret = fork();

if(ret < 0){
perror("error in fork");
printf("The final value of i is %d\n", i);
exit(1);
}

if(ret > 0){
printf("I am in parent process context\n");
printf("In parent .. ppid is %d...and child is %d\n\n", getppid(),getpid());

}

if(ret == 0){
printf("I am in combine child process context\n");
printf("In child .. ppid is %d ...and pid is %d\n",getppid(),getpid());

ret = execl("/usr/bin/gcc","gcc","add.o","sub.o","mult.o","div.o","main.o","-o","final",NULL);

if (ret < 0) {
    perror("Error in execl");
    exit(1);
}



}


flag_unsuccessful = 0;
flag_abnormal = 0;

if(ret>0){
while(1){
ret = waitpid(-1,&status,0);

if(ret > 0){
printf("child with id %d terminated\n",ret);
if(WIFEXITED(status)){
printf("wifiexited\n");
}
else{
flag_unsuccessful = 1;
printf("unsuccessful\n");
}
}
else{
if(flag_unsuccessful || flag_abnormal){
printf("error in compling an object file \n");
exit(1);
flag_abnormal = 1;
}


}


if(ret < 0){
break;
}
}
}



printf("All child process terminated successfully and exit from child process\n");
// while(1);



return 0;

}
